/*
 * cmd.c
 *
 *  Created on: 2023. 7. 17.
 *      Author: kjkim
 */

#include "cmd.h"
#include "hw.h"

#define CMD_STX                             0x02
#define CMD_ETX                             0x03

#define CMD_STATE_WAIT_STX                  0
#define CMD_STATE_WAIT_CMD                  1
#define CMD_STATE_WAIT_OPTION_ERROR         2
#define CMD_STATE_WAIT_ERROR                3
#define CMD_STATE_WAIT_LENGTH_L             4
#define CMD_STATE_WAIT_LENGTH_H             5
#define CMD_STATE_WAIT_DATA                 6
#define CMD_STATE_WAIT_CHECKSUM             7
#define CMD_STATE_WAIT_ETX                  8

/*
 *
 */
static void cmdPutch(uint8_t ch, uint8_t data);

/*
 * cmd 초기화
 */
void  cmdInit(cmd_t *p_cmd)
{
  p_cmd->init   = false;                //cmd 통신 open 후에 true 처리
  p_cmd->state  = CMD_STATE_WAIT_STX;   //초기상태는 시작 문자를 기다리는 상태

  p_cmd->tx_packet.error  = 0;          //tx 패킷 에러상태변수 초기화
  p_cmd->rx_packetr.error = 0;          //rx 패킷 에러상태변수 초기화
}
/*
 * cmd 통신시작
 */
void  cmdBegin(cmd_t *p_cmd, uint8_t ch, uint32_t baud)
{
  p_cmd->ch     = ch;                   //cmd 사용할 통신 채널 입력 받아서 구조체 멤버변수에 저장
  p_cmd->baud   = baud;                 //baud(통신속도) 입력 받아서 구조체 멤버번수에 저장
  p_cmd->init   = true;
  p_cmd->state  = CMD_STATE_WAIT_STX;   //초기상태는 시작 문자를 기다리는 상태

  p_cmd->save_time[0] = millis();       //cmdBegin 수행 후 경과된 시간정보 저장
  p_cmd->save_time[1] = millis();       //cmdBegin 수행 후 경과된 시간정보 저장

  return uartOpen(ch, baud);            //입력받은 통신채널과 속도로 통신포트를 연다.
}

/*
 * 한바이트 데이터를 전송한다.
 */
void cmdPutch(uint8_t ch, uint8_t data)
{
  //입력한 채널로 한바이트 데이터 data값을 전송한다.
  uartPutch(ch, data);
}

/*
 * 패킷 수신 함수
 */
bool  cmdReceivePacket(cmd_t *p_cmd)
{
  bool ret = false;
  uint8_t   ch;
  uint32_t  index;
  uint16_t  temp_length;

  //cmd를 수신한다.
  if(uartAvailable(p_cmd->ch))  //입력 패킷데이터가 존재한다면
  {
    ch = uartRead(p_cmd->ch);   //해당 채널로 수신된 패킷데이터 읽어서 ch변수에 저장
  }
  else  //입력 패킷이 없다면
  {
    return false;
  }

  //입력되는 바이트간 타이마웃 설정(500ms)
  if((millis() - p_cmd->save_time[0]) > 500)
  {
    //500ms 이내에 패킷 바이트 데이터 수신이 안되서
    p_cmd->state  = CMD_STATE_WAIT_STX;   //시작 문자를 기다리는 상태로 변경한다.
  }
  p_cmd->save_time[0] = millis();

  //명령어 상태머신 처리...
  switch(p_cmd->state)
  {
    //시작 문자를 기다리는 상태
    case CMD_STATE_WAIT_STX :
      if(ch == CMD_STX)
      {
        p_cmd->state = CMD_STATE_WAIT_CMD;  //cmd 기다리는 상태로 변경
        p_cmd->rx_packetr.check_sum = 0;    //rx packet 체크섬 변수 0으로 초기화
        p_cmd->rx_packetr.length    = 0;    //rx packet 길이변수 초기화
        temp_length = 0;

      }
      break;

    //명령을 기다리는 상태
    case CMD_STATE_WAIT_CMD :
      p_cmd->rx_packetr.cmd = ch;                   //cmd 패킷 받아서 저장
      p_cmd->rx_packetr.check_sum ^= ch;            //cmd 체크섬 계산
      p_cmd->state = CMD_STATE_WAIT_OPTION_ERROR;   //option error 기다리는 상태로 변경
      break;

    //option error 상태를 기다리는 상태
    case CMD_STATE_WAIT_OPTION_ERROR :
      p_cmd->rx_packetr.option = ch;
      p_cmd->rx_packetr.error  = ch;
      p_cmd->rx_packetr.check_sum ^= ch;            //option error 체크섬 계산
      p_cmd->state = CMD_STATE_WAIT_LENGTH_L;       //length low 수신대기 상태로 변경
      break;

    //length_l를 기다리는 상태
    case CMD_STATE_WAIT_LENGTH_L :
      p_cmd->rx_packetr.length = ch;
      p_cmd->rx_packetr.check_sum ^= ch;
      p_cmd->state = CMD_STATE_WAIT_LENGTH_H;
      break;

    //length_h를 기다리는 상태
    case CMD_STATE_WAIT_LENGTH_H :
      temp_length = ch;
      p_cmd->rx_packetr.length |= (temp_length << 8) & 0xFF00;
      p_cmd->rx_packetr.check_sum ^= ch;
      p_cmd->state = CMD_STATE_WAIT_LENGTH_H;

      if(p_cmd->rx_packetr.length <= CMD_MAX_DATA_LENGTH) //rx packet 길이가 데이터 최대길이 이하이면
      {
        if(p_cmd->rx_packetr.length > 0)  //rx packet이 존재한다면(rx packet가 정상)
        {
          p_cmd->rx_packetr.index = 0;          //data 대기하는 상태에서 사용할 index 변수 초기화
          p_cmd->state = CMD_STATE_WAIT_DATA;   //data 수신대기 상태로 변경
        }
        else
        {
          //rx packet에 데이터 길이가 없다면(data가 없는 패킷)
          //data가 없으므로 체크섬을 기다리는 상태로 가면 된다.
          p_cmd->state = CMD_STATE_WAIT_CHECKSUM;
        }
      }
      else
      {
        //패킷데이터가 최대길이를 초과했다면
        //다시 stx기다리는 상태로 돌아간다.
        p_cmd->state = CMD_STATE_WAIT_STX;
      }
      break;

    //data를 기다리는 상태
    case CMD_STATE_WAIT_DATA :
      index = p_cmd->rx_packetr.index;    //위 상태에서 초기화환 index 변수를 지역변수 index에 저장
      p_cmd->rx_packetr.check_sum ^= ch;  //입력된 data를 체크섬 계산 처리한다.
      p_cmd->rx_packetr.data[index] = ch; //입력된 data를 rx packet 수신버퍼에 저장한다.

      p_cmd->rx_packetr.index++;          //index 1 증가 시킨다.
                                          //rx packet length(길이) 만큼 data를 계속 수신하여 수신버퍼에 입력한다.
                                          //위 과정을 데이터를 모두 받을때까지 반복동작한다.

      if(p_cmd->rx_packetr.index >= p_cmd->rx_packetr.length) //데이터를 모두 받았다면
      {
        //data 수신이 완료됬으므로, 체크섬 수신 대기상태로 넘어간다.
        p_cmd->state = CMD_STATE_WAIT_CHECKSUM;
      }

      break;

    //check sum을 기다리는 상태
    case CMD_STATE_WAIT_CHECKSUM :
      p_cmd->rx_packetr.check_sum_recv = ch;    //check_sum_recv변수에 상대방에서 보낸 체크섬값을 저장한다.
      p_cmd->state = CMD_STATE_WAIT_ETX;        //etx 수신대기 상태로 넘어간다.
      break;

    //etx를 기다리는 상태
    case CMD_STATE_WAIT_ETX :
      if(ch == CMD_ETX)
      {
        if(p_cmd->rx_packetr.check_sum_recv == p_cmd->rx_packetr.check_sum)
        {
          //상대방에서 계산해서 보낸 체크섬값(check_sum_recv)과 이곳에서 계산한 체크섬값(check_sum)이 같으므로
          //true를 반환한다.
          ret = true;
        }
      }
      p_cmd->state = CMD_STATE_WAIT_STX;  //stx 수신대기상태로 넘어간다.
      break;
  }


  return ret;
}

/*
 * 응답 packet 전송함수
 */
void cmdSendResp(cmd_t *p_cmd, uint8_t err_code, uint8_t *p_data, uint32_t length)
{
  uint32_t i;
  uint8_t ch;
  uint8_t check_sum = 0;
  uint8_t data;

  ch = p_cmd->ch;


  //수신된 cmd를 다시 응답으로 송신해야 하므로
  //tx packet 의 cmd 변수에 수신된 cmd를 저장한다.
  p_cmd->tx_packet.cmd = p_cmd->rx_packetr.cmd;

  //수신패킷에 따라 처리된 결과(에러코드)를 tx packet의 에러 변수에 저장한다.
  p_cmd->tx_packet.error = err_code;

  if(p_data != NULL)
  {
    //수신된 패킷 데이터 길이만큼 데이터를 tx packet의 data버퍼에 저장한다.
    for(i=i;i<length;i++)
    {
      p_cmd->tx_packet.data[i] = p_data[i];
    }
  }
  p_cmd->tx_packet.length = length;

  //시리얼 프로토콜 규약에 맞게 바이트 단위로 응답한다.
  cmdPutch(ch, CMD_STX);                          //stx 패킷 송신
  cmdPutch(ch, p_cmd->tx_packet.cmd);             //cmd 패킷 송신
  check_sum ^= p_cmd->tx_packet.cmd;              //cmd 패킷 부터 체크섬 계산 시작

  cmdPutch(ch, p_cmd->tx_packet.error);           //error code 패킷 송신
  check_sum ^= p_cmd->tx_packet.error;            //error code 체크섬 계산

  data = p_cmd->tx_packet.length & 0xFF;          //tx packet low length값을 변수에 저장
  cmdPutch(ch, data);                             //low length 값 전송
  check_sum ^= data;                              //low length 체크섬 계산

  data = (p_cmd->tx_packet.length >> 8) & 0xFF;   //high length값을 변수에 저장
  cmdPutch(ch, data);                             //high length값 전송
  check_sum ^= data;                              //high length값 체크섬 계산

  //data length 식별됬다면 data를 전송한다.
  for(i=0;i<p_cmd->tx_packet.length && i<CMD_MAX_DATA_LENGTH;i++)
  {
    cmdPutch(ch, p_cmd->tx_packet.data[i]);   //tx packet의 data를 바이트 단위로 전송
    check_sum ^= p_cmd->tx_packet.data[i];   //tx packet의 data를 체크섬 계산
  }

  //data 전소을 모두 수행했다면
  //check sum.값을 전송한다.
  cmdPutch(ch, check_sum);

  //etx packet 데이터를 전송한다.
  cmdPutch(ch, CMD_ETX);
}

/*
 * cmd packet 전송 함수
 */
void  cmdSendCmd(cmd_t *p_cmd, uint8_t cmd, uint8_t *p_data, uint32_t length)
{
  uint8_t i;
  uint8_t ch;
  uint8_t check_sum = 0;
  uint8_t data;

  p_cmd->ch = ch;

  p_cmd->tx_packet.cmd = cmd;                       //tx packe cmd에 입력받은 cmd저자ㅣㅇ
  p_cmd->tx_packet.option = 0;                      //tx packet의 option 초기화

  if(p_data != NULL)                                //송신할 data 포인터가 NULL이 아니라면
  {
    for(i=0;i<length;i++)                           //송신할 데이터 길이만큼
    {
      p_cmd->tx_packet.data[i] = p_data[i];         //tx packet data를 전송한다.
    }
  }

  p_cmd->tx_packet.length = length;                 //송신할 data의 길이를 tx packet의 length에 저장한다.


  cmdPutch(ch, CMD_STX);                            //stx 전송
  cmdPutch(ch, p_cmd->tx_packet.cmd);               //tx packet cmd 전송
  check_sum ^= p_cmd->tx_packet.cmd;                //check sum 계산 시작

  cmdPutch(ch, p_cmd->tx_packet.option);            //option 바이트 전송
  check_sum ^= p_cmd->tx_packet.option;             //option 바이트 체크섬 계산

  data = p_cmd->tx_packet.length && 0xFF;           //length low byte를 data변수에 저장
  cmdPutch(ch, data);                               //length low byte 전송
  check_sum ^= data;                                //length low byte값 체크섬 계산
  data = (p_cmd->tx_packet.length >> 8) & 0xFF;      //length high byte data변수에 저장
  cmdPutch(ch, data);                               //length high byte 전송
  check_sum ^= data;                                //length high byte 체크섬 계산

  //길이만큰 data 송신한다.
  for(i=0;i<p_cmd->tx_packet.length && i<CMD_MAX_DATA_LENGTH; i++)
  {
    cmdPutch(ch, p_cmd->tx_packet.data[i]);         //length만큼 data 송신
    check_sum ^= p_cmd->tx_packet.data[i];          //바이트 단위로 전송되는 data 체크섬 계산
  }

  cmdPutch(ch, check_sum);                          //체크섬 값을 송신한다.
  cmdPutch(ch, CMD_ETX);                            //etx 패킷을 송신한다. //패킷의 종료

}

/*
 * cmd 수신 후 응답전송 함수
 */
bool cmdSendCmdRxResp(cmd_t *p_cmd, uint8_t cmd, uint8_t *p_data, uint32_t length, uint32_t time_out)
{
  bool ret          = true;
  uint8_t err_code  = 0;
  uint32_t time_pre;


  cmdSendCmd(p_cmd, cmd, p_data, length);

  time_pre = millis();            //경과시간을 알기위한 목적의 변수

  while(1)
  {
    if(cmdReceivePacket(p_cmd) == true)           //수신패킷을 이상없이 수신했음
    {
      err_code = p_cmd->rx_packetr.error;         //수신패킷에서 error값을 로컬 변수에 저장
      break;
    }

    if(millis()-time_pre < time_out)            //타임아웃 시간이 경과했다면
    {
      p_cmd->rx_packetr.error = ERR_TIMEOUT;    //rx packet error값에 에러코드 저장한다.(ERR_TIMEOUT)
      err_code = ERR_TIMEOUT;
      break;
    }
  }

  if(err_code != 0)
  {
    ret = false;
  }



  return ret;
}
