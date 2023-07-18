/*
 * cmd.h
 *
 *  Created on: 2023. 7. 17.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INC_CMD_H_
#define SRC_COMMON_INC_CMD_H_

#include "def.h"

#define CMD_MAX_DATA_LENGTH         2048

typedef struct
{
  /*
   * cmd 패킷에 사용할 변수롤 구조체 멤버로 선언
   */
  uint32_t  index;
  uint8_t   cmd;
  uint8_t   option;
  uint8_t   error;
  uint16_t  length;
  uint8_t   check_sum;
  uint8_t   check_sum_recv;
  uint8_t   data[CMD_MAX_DATA_LENGTH];
}cmd_packet_t;

typedef struct
{
  /*
   * cmd 패킷을 사용할 통신채널, 속도, 상태등 변수 구조체 멤버로 선언
   */
  uint8_t   ch;             //채널
  uint8_t   init;           //초기화 상태
  uint8_t   state;          //현재 상태
  uint32_t  baud;           //전송속도
  uint32_t  save_time[2];

  /*
   *  rx, tx 패킷 구조체 변수 선언
   */
  cmd_packet_t  tx_packet;  //tx패킷 구조체 변수 선언
  cmd_packet_t  rx_packetr; //rx패킷 구조체 변수 선언
}cmd_t;


/*
 * cmd 초기화
 */
void  cmdInit(cmd_t *p_cmd);
/*
 * cmd 통신시작
 */
void  cmdBegin(cmd_t *p_cmd, uint8_t ch, uint32_t baud);
/*
 * 패킷 수신 함수
 */
bool  cmdReceivePacket(cmd_t *p_cmd);
/*
 * cmd packet 전송 함수
 */
void  cmdSendCmd(cmd_t *p_cmd, uint8_t cmd, uint8_t *p_data, uint32_t length);
/*
 * 응답 packet 전송함수
 */
void cmdSendResp(cmd_t *p_cmd, uint8_t err_code, uint8_t *p_data, uint32_t length);
/*
 * cmd 수신 후 응답전송 함수
 */
bool cmdSendCmdRxResp(cmd_t *p_cmd, uint8_t cmd, uint8_t *p_data, uint32_t length, uint32_t time_out);

#endif /* SRC_COMMON_INC_CMD_H_ */
