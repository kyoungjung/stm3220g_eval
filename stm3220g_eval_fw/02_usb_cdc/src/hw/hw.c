/*
 * hw.c
 *
 *  Created on: 2023. 4. 12.
 *      Author: kjkim
 */


#include "hw.h"


void hwInit(void)
{
  bspInit();
  ledInit();
  uartInit();
}
