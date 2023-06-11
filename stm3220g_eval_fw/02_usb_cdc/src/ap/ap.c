/*
 * ap.c
 *
 *  Created on: 2023. 4. 12.
 *      Author: kjkim
 */


#include "ap.h"

void apInit(void)
{
  uartOpen(_DEF_UART1, 115200);
}

void apMain(void)
{
  uint32_t pre_time;
  uint32_t pre_baud;
  uint8_t rx_data;

  pre_time = millis();
  //초기에 설정된 baud 값을 저장한다.
  pre_baud = uartGetBaud(_DEF_UART1);

  while(1)
  {
    if(millis() - pre_time > 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    if(uartAvailable(_DEF_UART1) > 0)
    {
      rx_data = uartRead(_DEF_UART1);

      uartPrintf(_DEF_UART1, "rx data : %c\r\n", rx_data);
    }
    //현재 설정한 baud가 이전에 설정된 baud와 다르면
    if(uartGetBaud(_DEF_UART1) != pre_baud)
    {
      //현재 설정된 baud값을 저장
      pre_baud = uartGetBaud(_DEF_UART1);
      //변경된 baud값을 알려준다.
      uartPrintf(_DEF_UART1, "changed baud : %d\r\n", pre_baud);
    }
  }
}
