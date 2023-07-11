/*
 * cmdif.c
 *
 *  Created on: 2023. 6. 14.
 *      Author: kjkim
 */

/**
 * @ 명령어 처리 함수 구현
 */

#include "cmdif.h"


//명령어와 명령어에 따른 실행함수(함수포인터)가 정의된 구조체를 배열로 선언
cmdif_cmd_node_t    cmdif_cmd_node[CMDIF_LIST_MAX];

//명령행 문자열 관련 입력, 설정, 처리 관련 구조체 변수 선언
cmdif_cmd_t   cmdif_cmd;

static const chsr *delim = " \f\n\r\t\v";


//지역 함수원형 선언
void    cmdifResetBuffer(void);
int     cmdifGetCmdString(char *s, int *count);
uint8_t cmdifReadByte(char *p_data);

int     parseCommandArgs(char *cmdline, char **argv);
void    upperStr(char *Str);

void    cmdifCmdExit(void);
void    cmdifCmdShowList(void);
void    cmdifCmdMemoryDump(void);
void    cmdifCmdMemoryWrite32(void);



/**
 * @
 */
bool cmdifInit(void)
{
  bool ret = true;
  uint32_t i;

  cmdif_cmd.index       = 0;    //명령어 인덱스 초기화
  cmdif_cmd.err_code    = 0;    //에러코드 초기화
  cmdif_cmd.init        = true; //초기화 완료 플래그 셋
  cmdif_cmd.node        = &cmdif_cmd_node[0]; //명령어와 명령어에 따른 실행함수(함수포인터)가 정의된 구조체의 포인터 초기화

  for(i=0;i<CMDIF_LIST_MAX;i++)
  {
    cmdif_cmd.node[i].cmd_str[0]  = 0;      //
    cmdif_cmd.node[i].cmd_func    = NULL;   //명령어(16개)에 따라 실행되는 함수포인터 null로 초기화
  }

  cmdifResetBuffer();

  cmdifAdd("help", cmdifCmdShowList);         //help 입력하면 cmdifCmdShowList 함수 실행
  cmdifAdd("exit", cmdifCmdExit);             //exti 입력하면 cmdifCmdExit 함수 실행

  cmdifAdd("md", cmdifCmdMemoryDump);         //md 입력하면 cmdifCmdMemoryDump 함수실행
  cmdifAdd("mw32", cmdifCmdMemoryWrite32);    //mw32 입력하면 cmdifCmdMemoryWrite32 함수실행

  return ret;
}

bool cmdifIsInit(void)
{
  bool ret = false;

  ret = cmdif_cmd.init;     //cmdif 가 초기화 됬었는는 상태 전달

  return ret;
}

void cmdifOpen(uint8_t ch, uint32_t baud)
{
  cmdif_cmd.ch    = ch;
  cmdif_cmd.baud  = baud;

  uartOpen(ch, baud);   //입력된 uart 채널과 속도로 uartopen 함수 호출한다.
}

void cmdifLoop(void)
{
  cmdif_cmd.exit    = false;    //cmd명령 기반 모드에서 빠져나갔는지???

  while(1)
  {
    cmdifMain();    //명령행 기반으로 동작하는 중.....

    if(cmdif_cmd.exit == true)    //사용자에 의해 exit 문자열이 입력되면
    {
      break;                      //명령행 기반에서 빠져나간다...
    }
  }
}

void cmdifMain(void)
{
  int cmdlp;
  int argc;
  int ret;
  int count;

  uint32_t cmdchk = 0;

  char *argv[128];

  //??????????????????????????????????????????????
  count = (int)cmdif_cmd.p_read_bufffer - (int)cmdif_cmd.read_buffer;

  ret = cmdifGetCmdString(cmdif_cmd.p_read_bufffer, &count);

  if(count != ((int)cmdif_cmd.p_read_bufffer - (int)cmdif_cmd.read_buffer))
  {
    cmdif_cmd.p_read_bufffer = cmdif_cmd.read_buffer+count;
  }

  if(ret == 0)
  {
    cmdifPrint("\n");
    argc = parseCommandArgs(cmdif_cmd.read_buffer, &argv[0]);

    if(argc)    //명령행 기반으로 문자열 입력이 있으면
    {

    }
  }
}

void cmdifAdd(const char *cmd_str, void (*(p_func)(void)))
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
