/*
 * flash.h
 *
 *  Created on: 2023. 5. 5.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_FLASH_H_
#define SRC_COMMON_FLASH_H_

#include "hw_def.h"

#ifdef _USE_HW_FLASH

bool flashInit(void);
bool flashErase(uint32_t addr, uint32_t length);
bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length);
bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length);


#endif//_USE_HW_FLASH


#endif /* SRC_COMMON_FLASH_H_ */
