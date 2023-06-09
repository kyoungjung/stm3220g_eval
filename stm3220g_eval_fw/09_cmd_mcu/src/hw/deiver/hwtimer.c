/*
 * hwtimer.c
 *
 *  Created on: 2023. 5. 16.
 *      Author: kjkim
 */


#include "hwtimer.h"

#define HWTIMER_MAX_CH          1

#define HWTIMER_TIMER1          0
#define HWTIMER_TIMER2          1
#define HWTIMER_TIMER3          2
#define HWTIMER_TIMER4          3

#define HWTIMER_CH1             0
#define HWTIMER_CH2             1
#define HWTIMER_CH3             2
#define HWTIMER_CH4             3


TIM_MasterConfigTypeDef sMasterConfig = {0};
TIM_OC_InitTypeDef sConfigOC = {0};

typedef struct
{
  TIM_HandleTypeDef       hTIM;
  TIM_OC_InitTypeDef      sConfig[TIMER_MAX_CH];
  uint32_t freq;
  void (*p_func[4])(void);
}hwtimer_tbl_t;

typedef struct
{
  uint8_t   number;
  uint8_t   index;
  uint32_t  active_channel;
}hwtimer_index_t;

static hwtimer_index_t      hwtimer_index[HW_TIMER_MAX_CH] =
    {
        {HWTIMER_TIMER1, HWTIMER_CH1, HAL_TIM_ACTIVE_CHANNEL_1},
        {HWTIMER_TIMER1, HWTIMER_CH2, HAL_TIM_ACTIVE_CHANNEL_2},
        {HWTIMER_TIMER1, HWTIMER_CH3, HAL_TIM_ACTIVE_CHANNEL_3},
        {HWTIMER_TIMER1, HWTIMER_CH4, HAL_TIM_ACTIVE_CHANNEL_4}
    };

static hwtimer_tbl_t          hwtimer_tbl[HWTIMER_MAX_CH];

bool timerInit(void)
{
  bool ret = true;

  hwtimer_tbl[HWTIMER_TIMER1].freq                      = 1000;
  hwtimer_tbl[HWTIMER_TIMER1].hTIM.Instance             = TIM4;
  hwtimer_tbl[HWTIMER_TIMER1].hTIM.Init.Prescaler       =  ((uint32_t)(SystemCoreClock / 2) / hwtimer_tbl[HWTIMER_TIMER1].freq) - 1;
  hwtimer_tbl[HWTIMER_TIMER1].hTIM.Init.ClockDivision      = TIM_CLOCKDIVISION_DIV1;
  hwtimer_tbl[HWTIMER_TIMER1].hTIM.Init.CounterMode        = TIM_COUNTERMODE_UP;
  hwtimer_tbl[HWTIMER_TIMER1].hTIM.Init.RepetitionCounter  = 0;
  hwtimer_tbl[HWTIMER_TIMER1].hTIM.Init.AutoReloadPreload  = TIM_AUTORELOAD_PRELOAD_DISABLE;
  hwtimer_tbl[HWTIMER_TIMER1].p_func[0]       = NULL;
  hwtimer_tbl[HWTIMER_TIMER1].p_func[1]       = NULL;
  hwtimer_tbl[HWTIMER_TIMER1].p_func[2]       = NULL;
  hwtimer_tbl[HWTIMER_TIMER1].p_func[3]       = NULL;

  return ret;
}

bool timerStop(uint8_t ch)
{
  bool ret = true;
  hwtimer_tbl_t *p_timer;
  HAL_StatusTypeDef status;

  if(ch >= TIMER_MAX_CH)  return false;

  p_timer = &hwtimer_tbl[hwtimer_index[ch].number];

  status = HAL_TIM_Base_DeInit(&p_timer->hTIM);

  if(status != HAL_OK)
  {
    ret = false;
  }
  return ret;
}

bool timerSetPeriod(uint8_t ch, uint32_t period_data)
{
  bool ret = true;

  hwtimer_tbl_t   *p_timer;
  uint32_t period;

  if(ch >= TIMER_MAX_CH)    return false;

  p_timer = &hwtimer_tbl[hwtimer_index[ch].number];

  if(p_timer->freq == 1000)
  {
    period = period_data / 1000;

    if(period == 0)
    {
      period = 1;
    }
  }

  p_timer->hTIM.Init.Period = period - 1;

  return ret;
}

/*
 * @ 타이머 인터럽트에 동작할 함수 등록
 * */
bool timerAttachInterrupt(uint8_t ch, void(*func)(void))
{
  bool ret = true;
  hwtimer_tbl_t   *p_timer;   //타이머 설정 구조체 포인터 변수

  //입력된 채널번호가 타이머 최대채널 번호보다 크면 리턴
  if(ch >= TIMER_MAX_CH)    return false;

  //해당 타이머 채널 인덱스 번호에 해당하는 구조체 배열의 주소 포인터에 저장
  p_timer = &hwtimer_tbl[hwtimer_index[ch].number];

  //함수 등록전에 타이머 정지
  timerStop(ch);

  //사용할 타이머 채널에서 동작할 함수 등록(포인터로)
  p_timer->p_func[hwtimer_index[ch].index] = func;

  return ret;
}

/*
 * @ 타이머 인터럽트에서 동작하는 이미 등록된 함수를 해제한다.
 */
bool timerDetachInterrupt(uint8_t ch)
{
  bool ret = true;
  hwtimer_tbl_t   *p_timer;   //타이머 설정 구조체 포인터 변수

  //입력된 채널번호가 타이머 최대채널 번호보다 크면 리턴
  if(ch >= TIMER_MAX_CH)    return false;

  //해당 타이머 채널 인덱스 번호에 해당하는 구조체 배열의 주소 포인터에 저장
  p_timer = &hwtimer_tbl[hwtimer_index[ch].number];

  //함수등록 해제전에 타이머 정지
  timerStop(ch);

  //사용할 타이머 채널에서 동작하는 함수 등록해제(null 처리)
  p_timer->p_func[hwtimer_index[ch].index] = NULL;

  return ret;
}

bool timerStart(uint8_t ch)
{
  bool ret = true;
  hwtimer_tbl_t   *p_timer;
  uint32_t timer_sub_ch = 0;

  if(ch >= TIMER_MAX_CH)    return false;

  p_timer = &hwtimer_tbl[hwtimer_index[ch].number];

  switch(hwtimer_index[ch].index)
  {
    case HWTIMER_CH1 :
      timer_sub_ch = TIM_CHANNEL_1;
      break;

    case HWTIMER_CH2 :
      timer_sub_ch = TIM_CHANNEL_2;
      break;

    case HWTIMER_CH3 :
      timer_sub_ch = TIM_CHANNEL_3;
      break;

    case HWTIMER_CH4 :
      timer_sub_ch = TIM_CHANNEL_4;
      break;
    default : break;
  }

  if(HAL_TIM_OC_Init(&p_timer->hTIM) != HAL_OK)
  {
    ret = false;
  }

  if(HAL_TIM_OC_ConfigChannel(&p_timer->hTIM, &p_timer->sConfig[hwtimer_index[ch].index], timer_sub_ch) != HAL_OK)
  {
    ret = false;
  }

  if(HAL_TIM_Base_Start_IT(&p_timer->hTIM) != HAL_OK)
  {
    ret = false;
  }

  if(HAL_TIM_OC_Start_IT(&p_timer->hTIM, timer_sub_ch) != HAL_OK)
  {
    ret = false;
  }

  return ret;
}

void timerCallback(TIM_HandleTypeDef *htim)
{
  uint32_t i;
  uint32_t index;
  hwtimer_tbl_t   *p_timer;

  for(i=0;i<TIMER_MAX_CH;i++)
  {
    p_timer = &hwtimer_tbl[hwtimer_index[i].number];
    index = hwtimer_index[i].index;

    if(htim->Channel == hwtimer_index[i].active_channel)
    {
      if(p_timer->p_func != NULL)
      {
        (*p_timer->p_func[index])();
      }
    }
  }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerCallback(htim);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == hwtimer_tbl[HWTIMER_TIMER1].hTIM.Instance )
  {
    __HAL_RCC_TIM4_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM4_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == hwtimer_tbl[HWTIMER_TIMER1].hTIM.Instance)
  {
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
  }
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef* tim_ocHandle)
{

  if(tim_ocHandle->Instance==TIM4)
  {
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* TIM4 interrupt Init */
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }
}

void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef* tim_ocHandle)
{

  if(tim_ocHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /* TIM4 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
  }
}

void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&hwtimer_tbl[HWTIMER_TIMER1].hTIM);
}



