/*
 * flash.c
 *
 *  Created on: 2023. 5. 5.
 *      Author: kjkim
 */


#include "flash.h"
#include "cli.h"

#ifdef _USE_HW_FLASH

#define FLASH_SECTOR_MAX          12

typedef struct
{
  uint32_t addr;
  uint32_t length;
}flash_tbl_t;

static flash_tbl_t   flash_tbl[FLASH_SECTOR_MAX] =
    {
        {0x08000000, 16 *  1024},
        {0x08004000, 16 *  1024},
        {0x08008000, 16 *  1024},
        {0x0800C000, 16 *  1024},
        {0x08010000, 64 *  1024},
        {0x08020000, 128 * 1024},
        {0x08040000, 128 * 1024},
        {0x08060000, 128 * 1024},
        {0x08080000, 128 * 1024},
        {0x080A0000, 128 * 1024},
        {0x080C0000, 128 * 1024},
        {0x080E0000, 128 * 1024}
    };


static bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length);

#ifdef _USE_HW_CLI
static void cliFlash(cli_args_t *args);
#endif

bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length)
{
  bool ret = false;

  uint32_t sector_start;
  uint32_t sector_end;
  uint32_t flash_start;
  uint32_t flash_end;

  sector_start  = flash_tbl[sector_num].addr;
  sector_end    = flash_tbl[sector_num].addr + flash_tbl[sector_num].length - 1;
  flash_start   = addr;
  flash_end     = flash_start + length - 1;

  if(sector_start >= flash_start && sector_start <= flash_end)
  {
    ret = true;
  }
  if(sector_end >= flash_start && sector_end <= flash_end)
  {
    ret = true;
  }
  if(flash_start >= sector_start && flash_start <= sector_end)
  {
    ret = true;
  }
  if(flash_end >= sector_start && flash_end <= sector_end)
  {
    ret = true;
  }

  return ret;
}

bool flashInit(void)
{
  bool ret = true;

#ifdef _USE_HW_CLI
  cliAdd("Flash", cliFlash);
#endif

  return ret;
}

bool flashErase(uint32_t addr, uint32_t length)
{
  bool ret = false;
  HAL_StatusTypeDef       status;
  FLASH_EraseInitTypeDef  init;
  uint32_t SectorError;

  int16_t start_sector_num = -1;
  uint32_t sector_count = 0;

  for(int i=0;i<FLASH_SECTOR_MAX;i++)
  {
    //지우고자 하는 플래시 영역에 섹터가 포함되는지?
    if(flashInSector(i, addr, length) == true)
    {
      //지우고자 하는 플래시 영역에 포함되는 첫번째 섹터 번호만 식별한다.
      if(start_sector_num < 0)
      {
        start_sector_num = i;
      }
      //지우고자 하는 플래시 영역에 포함되는 섹터 갯수를 카운팅 한다.
      sector_count++;
    }
  }

  //지우고자 하는 플래시 영역에 포함되는 섹터가 존재한다면?
  if(sector_count > 0)
  {
    //flash unlock 을 한다.
    HAL_FLASH_Unlock();

    init.TypeErase    = FLASH_TYPEERASE_SECTORS;
    init.Banks        = FLASH_BANK_1;
    init.Sector       = start_sector_num;
    init.NbSectors    = sector_count;
    init.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    status = HAL_FLASHEx_Erase(&init, &SectorError);

    if(status == HAL_OK)
    {
      ret = true;
    }

    //flash lock 을 한다.
    HAL_FLASH_Lock();
  }
  return ret;
}

bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  HAL_StatusTypeDef status;

  //flash unlock 을 한다.
  HAL_FLASH_Unlock();

  for(int i=0;i<length;i+=1)
  {
    uint16_t data;
    //data = p_data[i+0] << 0;
    data = p_data[0] << 0;
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr + i, (uint64_t)data);

    if(status != HAL_OK)
    {
      ret = false;
      break;
    }
  }
  //flash lock 을 한다.
  HAL_FLASH_Lock();

  return ret;
}

bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  //읽고싶은 플래시 메모리 시작주소를 넘겨받는다.
  uint8_t *p_byte = (uint8_t*)addr;

  for(int i=0;i<length;i++)
  {
    //읽고 싶은 플래시 영역의 시작주소에 있는 값부터 읽어와서 저장
    p_data[i] = p_byte[i];
  }

  return ret;
}


#ifdef _USE_HW_CLI
void cliFlash(cli_args_t *args)
{
  bool ret = false;

  if(args->argc == 1 && args->isStr(0, "info") == true)
  {
    for(int i=0;i<FLASH_SECTOR_MAX;i++)
    {
      cliPrintf("0x%X : %dKB\r\n", flash_tbl[i].addr, flash_tbl[i].length/1024);
    }

    ret = true;
  }

  if(args->argc == 3 && args->isStr(0, "read") == true)
  {
    uint32_t addr;
    uint32_t length;

    addr    = (uint32_t)args->getData(1);
    length  = (uint32_t)args->getData(2);

    for(int i=0;i<length;i++)
    {
      cliPrintf("0x%X : 0x%X\r\n", addr+i, *((uint8_t *)addr + i));
    }

    ret = true;
  }

  if(args->argc == 3 && args->isStr(0, "write") == true)
  {
    uint32_t addr;
    uint32_t data;

    addr    = (uint32_t)args->getData(1);
    data    = (uint32_t)args->getData(2);

    if(flashWrite(addr, (uint8_t *)&data, (uint32_t)16) == true)
    {
      cliPrintf("Flash Write Success\r\n");
    }
    else
    {
      cliPrintf("Flash Write Fail\r\n");
    }

    ret = true;
  }

  if(args->argc == 3 && args->isStr(0, "erase") == true)
  {
    uint32_t addr;
    uint32_t length;

    addr    = args->getData(1);
    length  = args->getData(2);

    if(flashErase(addr, length) == true)
    {
      cliPrintf("Flash Erase Success");
    }
    else
    {
      cliPrintf("Flash Erase Fail");
    }

    ret = true;
  }


  if(ret != true)
  {
    cliPrintf("flash info\r\n");
    cliPrintf("flash read addr length\r\n");
    cliPrintf("flash write addr data\r\n");
    cliPrintf("flash erase addr length\r\n");
  }
}
#endif //_USE_HW_CLI


#endif //_USE_HW_FLASH
