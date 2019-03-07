/*
    __flash_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__flash_driver.h"
#include "__flash_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __FLASH_DRV_I2C__
static uint8_t _slaveAddress;
#endif

const uint8_t _FLASH_CMD_RDID  = 0x9F;    // 25P80
const uint8_t _FLASH_CMD_READ  = 0x03;
const uint8_t _FLASH_CMD_WRITE = 0x02;
const uint8_t _FLASH_CMD_WREN  = 0x06;
const uint8_t _FLASH_CMD_RDSR  = 0x05;
const uint8_t _FLASH_CMD_ERASE = 0xC7;    // 25P80
const uint8_t _FLASH_CMD_EWSR  = 0x06;    // 25P80
const uint8_t _FLASH_CMD_WRSR  = 0x01;
const uint8_t _FLASH_CMD_SER   = 0xD8;    //25P80
const uint8_t _FLASH_CMD_WDIS  = 0x04;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __FLASH_DRV_SPI__

void flash_spiDriverInit(T_FLASH_P gpioObj, T_FLASH_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
    hal_gpio_csSet(1);
}
 
#endif
#ifdef   __FLASH_DRV_I2C__

void flash_i2cDriverInit(T_FLASH_P gpioObj, T_FLASH_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __FLASH_DRV_UART__

void flash_uartDriverInit(T_FLASH_P gpioObj, T_FLASH_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

// GPIO Only Drivers - remove in other cases
void flash_gpioDriverInit(T_FLASH_P gpioObj)
{
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
}

/* ----------------------------------------------------------- IMPLEMENTATION */

void flash_init()

{
 
    hal_gpio_csSet(1);

}

void flash_WriteEnable()

{
    uint8_t temp[1];
    
    temp[0] = _FLASH_CMD_WREN;
    hal_gpio_csSet(0);
    hal_spiWrite(temp,1);
    hal_gpio_csSet(1);

}

uint8_t flash_isWriteBusy()

{
    uint8_t temp[1];

    temp[0] = _FLASH_CMD_RDSR;  
    hal_gpio_csSet(0);
    hal_spiWrite(temp, 1);
    hal_spiRead(temp,1);
    hal_gpio_csSet(1);

  return (temp[0] & 0x01);
}

void flash_WriteByte(uint8_t value, uint32_t address)
{
    uint8_t temp[5];

    temp[0] = _FLASH_CMD_WRITE;      
    temp[1] = (uint8_t) ((address>>16) & 0x000000ff);                       
    temp[2] = (uint8_t) ((address>>8) & 0x000000ff);
    temp[3] = (uint8_t) (address & 0x000000ff);
    temp[4] = value; 
    
    flash_WriteEnable();
    
    hal_gpio_csSet(0);
    hal_spiWrite(temp, 5);
    hal_gpio_csSet(1);

    // Wait for write end
    while(flash_isWriteBusy());
}

void flash_WriteWord(uint16_t value, uint32_t address)
{
  
  uint8_t temp[2];

  temp[0] = (uint8_t) (value >> 8);
  temp[1] = (uint8_t) (value & 0x00FF);

  flash_WriteByte(temp[0],address);
  flash_WriteByte(temp[1],address+1);

}


uint8_t flash_ReadID()
{
    uint8_t temp[1];
    
    temp[0] = _FLASH_CMD_RDID;
    hal_gpio_csSet(0);
    hal_spiWrite(temp,1);
    hal_spiRead(temp,1);
    hal_gpio_csSet(1);
  
    return temp[0];
}

uint8_t flash_ReadByte(uint32_t address)
{

    uint8_t temp[4];

    temp[0] = _FLASH_CMD_READ;      
    temp[1] = (uint8_t) ((address>>16) & 0x000000ff);                       
    temp[2] = (uint8_t) ((address>>8) & 0x000000ff);
    temp[3] = (uint8_t) (address & 0x000000ff);
    
    hal_gpio_csSet(0);
    hal_spiWrite(temp,4);
    hal_spiRead(temp,1);
    hal_gpio_csSet(1);
    
    return temp[0];
}

uint16_t flash_ReadWord(uint32_t address)
{
    uint8_t temp[2];
    uint16_t retVal;

    temp[0] = flash_ReadByte(address);
    temp[1] = flash_ReadByte(address+1);

    retVal = temp[0] << 8 | temp[1];
    
    return retVal;
}

uint8_t flash_WriteArray(uint32_t address, uint8_t* pData, uint16_t nCount)
{
  
    uint32_t addr;
    uint8_t* pD;
    uint16_t counter;

    addr = address;
    pD   = pData;

  // WRITE

    for(counter = 0; counter < nCount; counter++)
    {
      
      flash_WriteByte(*pD++, addr++);

    }


  // VERIFY

  for (counter=0; counter < nCount; counter++)
  {
    if (*pData != flash_ReadByte(address))
        return 0;

    pData++;
    address++;

  }

  return 1;
}

 void flash_ReadArray(uint32_t address, uint8_t* pData, uint16_t nCount)
{
    uint8_t temp[4];
    uint8_t *ptr;
    
    ptr = pData;
    temp[0] = _FLASH_CMD_READ;      
    temp[1] = (uint8_t) ((address>>16) & 0x000000ff);                       
    temp[2] = (uint8_t) ((address>>8) & 0x000000ff);
    temp[3] = (uint8_t) (address & 0x000000ff);
    
    hal_gpio_csSet(0);
    hal_spiWrite(temp,4);
    hal_spiRead( ptr, nCount );
    hal_gpio_csSet(1);
}


void flash_ChipErase()
{
    uint8_t temp[1];
    temp[0] = _FLASH_CMD_ERASE;

    flash_WriteEnable();
    hal_gpio_csSet(0);
    hal_spiWrite(temp,1);
    hal_gpio_csSet(1);

  // Wait for write end
    while(flash_isWriteBusy());
}

void flash_ResetWriteProtection()
{
    uint8_t temp[2];
    temp[0] = _FLASH_CMD_EWSR;
    temp[1] = 0x00;
    hal_gpio_csSet(0);
    hal_spiWrite(temp,1);
    hal_gpio_csSet(1);

    hal_gpio_csSet(0);
    hal_spiWrite(temp,2);
    hal_gpio_csSet(1);
}

void flash_SectorErase(uint32_t address)

{
    uint8_t temp[4];

    temp[0] = _FLASH_CMD_SER;      
    temp[1] = (uint8_t) ((address>>16) & 0x000000ff);                       
    temp[2] = (uint8_t) ((address>>8) & 0x000000ff);
    temp[3] = (uint8_t) (address & 0x000000ff);

    flash_WriteEnable();

    hal_gpio_csSet(0);
    hal_spiWrite(temp,4);
    hal_gpio_csSet(1);

    // Wait for write end
    while(flash_isWriteBusy());
}
/* -------------------------------------------------------------------------- */
/*
  __flash_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */