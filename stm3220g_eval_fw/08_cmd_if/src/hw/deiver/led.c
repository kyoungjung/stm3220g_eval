/*
 * led.c
 *
 *  Created on: 2023. 4. 13.
 *      Author: kjkim
 */


#include "led.h"
#include "cli.h"

typedef struct
{
  GPIO_TypeDef      *port;
  uint16_t          pin;
  GPIO_PinState     on_state;
  GPIO_PinState     off_state;
}led_tbl_t;

led_tbl_t     led_tbl[LED_MAX_CH] =
    {
        {GPIOG, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOG, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOI, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOC, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET}
    };

#ifdef _USE_HW_CLI
static void cliLed(cli_args_t *args);
#endif

bool ledInit(void)
{
  bool ret = true;
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //LED사용 Port Clock Enable
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  //LED 사용 핀 출력 설정
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  for(int i=0;i<LED_MAX_CH;i++)
  {
    GPIO_InitStruct.Pin = led_tbl[i].pin;
    HAL_GPIO_Init(led_tbl[i].port, &GPIO_InitStruct);

    ledOff(i);
  }

#ifdef _USE_HW_CLI
  cliAdd("led", cliLed);
#endif

  return ret;
}

void ledOn(uint8_t ch)
{
  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].on_state);
}

void ledOff(uint8_t ch)
{
  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].off_state);
}

void ledToggle(uint8_t ch)
{
  HAL_GPIO_TogglePin(led_tbl[ch].port, led_tbl[ch].pin);
}


#ifdef _USE_HW_CLI
void cliLed(cli_args_t *args)
{
  bool ret = false;

  if(args->argc == 3 && args->isStr(0, "toggle") == true)
  {
    uint8_t led_ch;
    uint32_t toogle_time;
    uint32_t pre_time;

    led_ch = args->getData(1);
    toogle_time = args->getData(2);

    if(led_ch > 0)
    {
      led_ch--;
    }

    cliPrintf("cliLed OK \r\n");

    pre_time = millis();  //현재 카운터값 저장

    while(cliKeepLoop())  //입력이 없으면 무한루프
    {
      //설정한 토글시간 이상 경과했다면
      if(millis() - pre_time >= toogle_time)
      {
        pre_time = millis();  // 다시 현재 카운터값 저장
        ledToggle(led_ch);
      }
    }
    ret = true;
  }

  if(ret != true)
  {
    cliPrintf("led toggle CH[1 ~ %d] time(ms) \r\n", LED_MAX_CH);
  }
}
#endif


