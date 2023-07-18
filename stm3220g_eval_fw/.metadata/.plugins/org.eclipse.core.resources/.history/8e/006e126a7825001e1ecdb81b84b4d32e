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
 * cmd packet 전송 함수
 */
void  cmdSendCmd(cmd_t *p_cmd, uint8_t *p_data, uint32_t length);
/*
 * 응답 packet 전송함수
 */
void cmdSendResp(cmd_t *p_cmd, uint8_t err_code, uint8_t *p_data, uint32_t length);
/*
 * cmd 수신 후 응답전송 함수
 */
bool cmdSendCmdRxResp(cmd_t *p_cmd, uint8_t cmd, uint8_t *p_data, uint32_t length, uint32_t time_out);
