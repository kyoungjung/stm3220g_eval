/*
 * qbuffer.c
 *
 *  Created on: 2023. 4. 26.
 *      Author: kjkim
 */


#include "qbuffer.h"


void qbufferInit(void)
{

}
bool qbufferCreate(qbuffer_t *p_node, uint8_t *p_buf, uint32_t length)
{
  bool ret = true;
  p_node->in  = 0;
  p_node->out = 0;
  p_node->len = length;
  p_node->p_buf = p_buf;

  return ret;
}

bool qbufferWrite(qbuffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  uint32_t next_in;

  for(int i=0;i<length;i++)
  {
    //in 인덱스를 1증가시킨고 next_in 변수에 저장
      next_in = (p_node->in + 1) % p_node->len;

      if(next_in != p_node->out)  //버퍼가 full이 아니면
      {
        if(p_node->p_buf != NULL)
        {
          //수신 버퍼에 수신된 데이터 저장
          p_node->p_buf[p_node->in] = p_data[i];
        }
        p_node->in = next_in;
      }
      else  //버퍼 full 이면
      {
        ret = false;  //에러
        break;  //for문 빠져나온다.
      }
  }
  return ret;
}

bool qbufferRead(qbuffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  bool ret = true;

  for(int i=0;i<length;i++)
  {
    if(p_node->p_buf != NULL)
    {
      p_data[i] = p_node->p_buf[p_node->out];
    }

    if(p_node->out != p_node->in) //버퍼에서 꺼낼 데이터가 있다면
    {
      p_node->out = (p_node->out + 1) % p_node->len;  //out 인덱스 1증가시킨다.
    }
    else  //버퍼에서 꺼낼 데이터가 없다면
    {
      ret = false;  //에러
      break;        //for문 빠져나온다.
    }
  }

  return ret;
}

uint32_t qbufferAvailable(qbuffer_t *p_node)
{
  uint32_t ret;

  ret = (p_node->in - p_node->out) % p_node->len;

  return ret;
}
void qbufferFlush(qbuffer_t *p_node)
{
  p_node->in = 0;
  p_node->out = 0;
}
