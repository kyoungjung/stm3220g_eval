/*
 * button.c
 *
 *  Created on: 2023. 5. 15.
 *      Author: kjkim
 */


#include "button.h"
#include "cmdif.h"

void buttonCmdif(void);

//GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
typedef struct
{
  GPIO_TypeDef    *port;
  uint16_t         pin;
  GPIO_PinState   on_state;
  GPIO_PinState   off_state;
}button_tbl_t;

button_tbl_t    button_tbl[BUTTON_MAX_CH] =
    {
        {GPIOG, GPIO_PIN_15, GPIO_PIN_RESET, GPIO_PIN_SET}, //user
        {GPIOC, GPIO_PIN_13, GPIO_PIN_RESET, GPIO_PIN_SET}, //tamper
        {GPIOA, GPIO_PIN_0, GPIO_PIN_SET, GPIO_PIN_RESET}   //wakeup
    };

bool buttonInit(void)
{
  bool ret = true;
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  for(int i=0;i<BUTTON_MAX_CH;i++)
  {
    GPIO_InitStruct.Pin = button_tbl[BUTTON_MAX_CH].pin;
    HAL_GPIO_Init(button_tbl[BUTTON_MAX_CH].port, &GPIO_InitStruct);
  }

  //cmdifAdd("button", buttonCmdif);
  cmdifAdd("button", buttonCmdif);

  return ret;
}

/**
 * @ button 명령 입력되면 실행되는 함수
 */
void buttonCmdif(void)
{
  uint8_t number;
  bool ret = true;

  if(cmdifHasString("read", 0) == true)   //0번째 인덱스가 read 문자열인지??
  {
    number = (uint8_t)cmdifGetParam(1);

    while(cmdifRxAvailable() == 0)
    {
      /*
      cmdifPrintf("button pressed ch %d : %d, event : %d, time %d\r\n",
                  number,
                  buttonGetPressed(number),
                  button))*/
      cmdifPrintf("button pressed ch %d : %d\r\n",
                        number,
                        buttonGetPressed(number)
                        );

      delay(50);
    }
  }
  else
  {
    ret = false;
  }

  if(ret != true)
  {
    cmdifPrintf("button read <0~9>\n");
  }
}

bool buttonGetPressed(uint8_t ch)
{
  bool ret = false;

  if(ch > BUTTON_MAX_CH)
  {
    return false;
  }

  if(HAL_GPIO_ReadPin(button_tbl[ch].port, button_tbl[ch].pin) == button_tbl[ch].on_state)
  {
    //버튼이 눌렸으면 true 반환
    ret = true;
  }
  else
  {
    //버튼이 눌리지 않았다면 flase  반환
    ret = false;
  }

  return ret;
}


