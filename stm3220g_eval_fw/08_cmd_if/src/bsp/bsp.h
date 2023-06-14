/*
 * bsp.h
 *
 *  Created on: 2023. 4. 12.
 *      Author: kjkim
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "stm32f2xx_hal.h"
#include "def.h"

#define _USE_LOG_PRINT      1

#if _USE_LOG_PRINT
#define logPrintf(fmt, ...)       printf(fmt, ##__VA_ARGS__)
#else
#define logPrintf(fmt, ...)
#endif


void bspInit(void);
void delay(uint32_t ms);
uint32_t millis(void);

#endif /* SRC_BSP_BSP_H_ */
