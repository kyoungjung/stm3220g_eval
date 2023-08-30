/*
 * qbuffer.h
 *
 *  Created on: 2023. 4. 26.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INC_QBUFFER_H_
#define SRC_COMMON_INC_QBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"

typedef struct
{
  uint32_t in;    //입력 인덱스
  uint32_t out;   //출력 인덱스
  uint32_t len;   //길이

  uint8_t *p_buf; //배열로 데이터길이를 확정해 놓지 않은 이유는
                  //외부에서 길이를 설정할 수 있도록 하기 위해 포인터로 선언해 놓는다.
}qbuffer_t;

void     qbufferInit(void);
bool     qbufferCreate(qbuffer_t *p_node, uint8_t *p_buf, uint32_t length);
bool     qbufferWrite(qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
bool     qbufferRead(qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
uint32_t qbufferAvailable(qbuffer_t *p_node);
void     qbufferFlush(qbuffer_t *p_node);


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_INC_QBUFFER_H_ */
