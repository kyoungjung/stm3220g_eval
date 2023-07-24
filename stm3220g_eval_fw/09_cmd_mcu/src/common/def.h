/*
 * def.h
 *
 *  Created on: 2023. 4. 12.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "def_err.h"





#define _DEF_LED1         0
#define _DEF_LED2         1
#define _DEF_LED3         2
#define _DEF_LED4         3

#define _DEF_UART1        0
#define _DEF_UART2        1

#define _DEF_BUTTON1      0
#define _DEF_BUTTON2      1
#define _DEF_BUTTON3      2

#define _DEF_HWTIMER1     0
#define _DEF_HWTIMER2     1
#define _DEF_HWTIMER3     2
#define _DEF_HWTIMER4     3


#define ERR_TIMEOUT       255

#endif /* SRC_COMMON_DEF_H_ */
