/*
 * cdc.h
 *
 *  Created on: 2023. 4. 26.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INC_CDC_H_
#define SRC_COMMON_INC_CDC_H_

#include "hw_def.h"

#ifdef _USE_HW_USE

bool cdcInit(void);
uint32_t cdcAvailable(void);
uint8_t cdcRead(void);
void cdcDataIn(uint8_t rx_data);
uint32_t cdcWrite(uint8_t *p_data, uint32_t length);
uint32_t cdcGetBaud(void);

#endif//_USE_HW_USE

#endif /* SRC_COMMON_INC_CDC_H_ */
