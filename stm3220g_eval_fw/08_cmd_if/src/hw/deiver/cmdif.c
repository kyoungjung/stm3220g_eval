/*
 * cmdif.c
 *
 *  Created on: 2023. 6. 14.
 *      Author: kjkim
 */


#include "cmdif.h"


bool cmdifInit(void)
{

}

bool cmdifIsInit(void)
{

}

void cmdifOpen(uint8_t ch, uint32_t baud)
{

}

void cmdifAdd(const char *cmd_str, void (*(p_func)(void)))
{

}

void cmdifMain(void)
{

}

void cmdifLoop(void)
{

}

void cmdifPrintf(const char *fmt, ...)
{

}

void cmdifPrint(char *str)
{

}

void cmdifPutCh(char data)
{

}

uit8_t cmdifGetCh(void)
{

}

uint32_t cmdifRxAvailable(void)
{

}

bool cmdifHasString(char *p_str, uint8_t index)
{

}

unsigned long cmdifGetParam(uint8_t index)
{

}

uint32_t cmdifGetParamCnt(void)
{

}