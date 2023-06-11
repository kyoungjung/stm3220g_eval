/*
 * hwtimer.h
 *
 *  Created on: 2023. 5. 16.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INC_HWTIMER_H_
#define SRC_COMMON_INC_HWTIMER_H_

#include "hw_def.h"

#ifdef _USE_HW_TIMER
#define TIMER_MAX_CH          HW_TIMER_MAX_CH

bool timerInit(void);
bool timerStop(uint8_t ch);
bool timerSetPeriod(uint8_t ch, uint32_t period_data);
bool timerAttachInterrupt(uint8_t ch, void(*func)(void));
bool timerDetachInterrupt(uint8_t ch);
bool timerStart(uint8_t ch);

#endif //_USE_HW_TIMER
#endif /* SRC_COMMON_INC_HWTIMER_H_ */
