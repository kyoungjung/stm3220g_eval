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
  uartOpen(_DEF_UART2, 115200);

  cliOpen(_DEF_UART1, 115200);
  cliOpenLog(_DEF_UART2, 115200);
}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();
  //초기에 설정된 baud 값을 저장한다.

  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    if(buttonGetPressed(_DEF_BUTTON1) == true)  //user key 누르면
    {
      ledOn(_DEF_LED2); //led2 on
    }
    else
    {
      ledOff(_DEF_LED2);  //user key 안누르면 led2 off
    }
    if(buttonGetPressed(_DEF_BUTTON2) == true)  //tamper key 누르면
    {
      ledOn(_DEF_LED3); //led3 on
    }
    else  //tamper key 안누르면
    {
      ledOff(_DEF_LED3);  //led3 off
    }
    if(buttonGetPressed(_DEF_BUTTON3) == true)  //wakeup key 누르면
    {
      ledOn(_DEF_LED4); //led4 on
    }
    else  //wakeup key 안누르면
    {
      ledOff(_DEF_LED4);  //led4 off
    }


    cliMain();
  }
}
