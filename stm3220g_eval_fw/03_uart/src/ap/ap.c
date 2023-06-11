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
}

void apMain(void)
{
  uint32_t pre_time;
  uint8_t rx_buf[128];
  uint8_t rx_len;

  pre_time = millis();
  //초기에 설정된 baud 값을 저장한다.

  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    if(uartGetBaud(_DEF_UART1) != uartGetBaud(_DEF_UART2))
    {
      //usb 터미널에서 통신속도 변경하여 uart와 통신속도가 다르면
      //uart 통신혹도를 usb에서 설정한 통신속도로 설정한다.
      uartOpen(_DEF_UART2, uartGetBaud(_DEF_UART1));
    }

    //usb수신 데이터 -> uart write 코드
    rx_len = uartAvailable(_DEF_UART1); //usb로 수신한 데이터 갯수 확인

    if(rx_len > 128)  //128을 넘지 않도록 한다.
    {
      rx_len = 128;
    }

    if(rx_len > 0)  //usb로 수신한 데이터가 있다면
    {
      for(int i=0;i<rx_len;i++)
      {
        rx_buf[i] = uartRead(_DEF_UART1); //usb로 수신한 데이터를 버퍼에 저장하고.
      }
      uartWrite(_DEF_UART2, &rx_buf[0], rx_len);  //usb로 수신한 데이터를 uart로 write한다.
    }

    //uart수신 데이터 -> usb write 코드
    rx_len = uartAvailable(_DEF_UART2); //uart로 수신한 데이터 갯수 확인

    if(rx_len > 128)  //128을 넘지 않도록 한다.
    {
      rx_len = 128;
    }

    if(rx_len > 0)  //uart로 수신한 데이터가 있다면
    {
      for(int i=0;i<rx_len;i++)
      {
        rx_buf[i] = uartRead(_DEF_UART2); //uart로 수신한 데이터를 버퍼에 저장하고.
      }
      uartWrite(_DEF_UART1, &rx_buf[0], rx_len);  //uart로 수신한 데이터를 usb로 write한다.
    }
  }
}
