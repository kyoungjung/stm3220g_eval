/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @version        : v1.0_Cube
  * @brief          : Usb device for Virtual Com Port.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */

/*
 @ USBD_CDC_LineCodingTypeDef;
  uint32_t bitrate;
  uint8_t  format;
  uint8_t  paritytype;
  uint8_t  datatype;
 */
USBD_CDC_LineCodingTypeDef          LineCoding =
    {
        115200,
        0x00,
        0x00,
        0x00

    };

uint32_t  rx_in = 0;
uint32_t  rx_out = 0;
uint32_t  rx_len = 512;
uint8_t   rx_buf[512];
bool      rx_full = false;



uint32_t cdcAvailable(void)
{
  uint32_t ret = 0;

  //버퍼 ?��?�� ?��?��
  //?��?��중이 버퍼 �??��
  ret = (rx_in - rx_out) % rx_len;

  return ret;
}
uint8_t USBD_CDC_SOF(struct _USBD_HandleTypeDef *pdev)
{

  //버퍼가 받을 수 없는 상황에서
  //다시 계산하여 버퍼가 받을 수 있는 상황이면
  //PC쪽에 다음 데이터를 보내라고 한다.
  if(rx_full == true)
  {
    //남아 있는 공간을 확인
    uint32_t buf_len;
    //수신 버퍼에 비어있는 데이터량
    buf_len = (rx_len - cdcAvailable()) - 1;

    if(buf_len >= USB_FS_MAX_PACKET_SIZE)
    {
      //데이터를 받을 공간이 있다라고 PC쪽에 알려준다.
      //PC는 아래 함수를 통해 신호를 받아야 다음 데이터를 보낸다.
      //USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]); //처음에 한번만 설정하면 되므로
                                                      //사용 안해도 됨
      USBD_CDC_ReceivePacket(pdev);   //입력 파라미터는 pdev
      rx_full = false;
    }
  }

  return 0;
}


uint8_t cdcRead(void)
{
  uint8_t ret;

  ret = rx_buf[rx_out];

  if(rx_in != rx_out)
  {
    //?��?��?���? 같으�? ?��?��?���? ?��?��
    rx_out = (rx_out + 1) % rx_len;
  }

  return ret;
}




void cdcDataIn(uint8_t rx_data)
{
  uint32_t next_rx_in;

  //?��?�� ?��?��?�� 버퍼?�� ???��
  rx_buf[rx_in] = rx_data;

  //rx_in ?��?��?�� 1 증�? ?��?�� ?�� �? ?��?��?�� 값을 next_rx_in?�� ???��?��?��.
  next_rx_in = (rx_in + 1) % rx_len;

  //rx_in + 1 ?��?��?�� �? next_rx_in?�� rx_out ?��?��?��?? 같�? ?��?���?
    //--> ?���? 버퍼�? full?�� ?��?��?���?.....
  if(next_rx_in != rx_out)
  {
    rx_in = next_rx_in;
  }
}

/*
 * usb�? write ?��?�� ?��?��
 */

uint32_t cdcWrite(uint8_t *p_data, uint32_t length)
{
  uint32_t pre_time;
  uint8_t ret;
  pre_time = millis();

  while(1)
  {
    ret = CDC_Transmit_FS(p_data, length);

    if(ret == USBD_OK)
    {
      return length;
    }
    else if(ret == USBD_FAIL)
    {
      return 0;
    }

    if(millis() - pre_time >= 100)  //time out
    {
      break;
    }
  }

  return 0;
}

uint32_t cdcGetBaud(void)
{
  return LineCoding.bitrate;
}

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
  /* USER CODE BEGIN 3 */
  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
  /* USER CODE BEGIN 5 */
  switch(cmd)
  {
    case CDC_SEND_ENCAPSULATED_COMMAND:

    break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

    break;

    case CDC_SET_COMM_FEATURE:

    break;

    case CDC_GET_COMM_FEATURE:

    break;

    case CDC_CLEAR_COMM_FEATURE:

    break;

  /*******************************************************************************/
  /* Line Coding Structure                                                       */
  /*-----------------------------------------------------------------------------*/
  /* Offset | Field       | Size | Value  | Description                          */
  /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
  /* 4      | bCharFormat |   1  | Number | Stop bits                            */
  /*                                        0 - 1 Stop bit                       */
  /*                                        1 - 1.5 Stop bits                    */
  /*                                        2 - 2 Stop bits                      */
  /* 5      | bParityType |  1   | Number | Parity                               */
  /*                                        0 - None                             */
  /*                                        1 - Odd                              */
  /*                                        2 - Even                             */
  /*                                        3 - Mark                             */
  /*                                        4 - Space                            */
  /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
  /*******************************************************************************/
    case CDC_SET_LINE_CODING:
      LineCoding.bitrate       = (uint32_t)(pbuf[0]);
      LineCoding.bitrate      |= (uint32_t)(pbuf[1] << 8);
      LineCoding.bitrate      |= (uint32_t)(pbuf[2] << 16);
      LineCoding.bitrate      |= (uint32_t)(pbuf[3] << 24);
      LineCoding.format        = (uint8_t)pbuf[4];
      LineCoding.datatype      = (uint8_t)pbuf[5];
      LineCoding.paritytype    = (uint8_t)pbuf[6];
    break;

    case CDC_GET_LINE_CODING:
      pbuf[0] = (uint8_t)(LineCoding.bitrate);
      pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8);
      pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16);
      pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24);
      pbuf[4] = (uint8_t)LineCoding.format;
      pbuf[5] = (uint8_t)LineCoding.datatype;
      pbuf[6] = (uint8_t)LineCoding.paritytype;
    break;

    case CDC_SET_CONTROL_LINE_STATE:

    break;

    case CDC_SEND_BREAK:

    break;

  default:
    break;
  }

  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint until exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  /* USER CODE BEGIN 6 */

  //먼저 usb로 받은 데이트를 버퍼에 write
  for(int i=0;i<*Len;i++)
  {
    cdcDataIn(Buf[i]);
  }

  //남아 있는 공간을 확인
  uint32_t buf_len;
  //수신 버퍼에 비어있는 데이터량
  buf_len = (rx_len - cdcAvailable()) - 1;

  if(buf_len >= USB_FS_MAX_PACKET_SIZE)
  {
    //데이터를 받을 공간이 있다라고 PC쪽에 알려준다.
    //PC는 아래 함수를 통해 신호를 받아야 다음 데이터를 보낸다.
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
    USBD_CDC_ReceivePacket(&hUsbDeviceFS);
  }
  else
  {
    //buffer 용량 부족
    //PC에서는 다음 데이터 보내지 않고 대기한다.
    rx_full = true;
  }
  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  CDC_Transmit_FS
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 7 */
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc->TxState != 0){
    return USBD_BUSY;
  }
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 7 */
  return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */