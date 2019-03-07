/*
    __flash_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __flash_driver.h
@brief    Flash Driver
@mainpage Flash Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   FLASH
@brief      Flash Click Driver
@{

| Global Library Prefix | **FLASH** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **jan 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _FLASH_H_
#define _FLASH_H_

/** 
 * @macro T_FLASH_P
 * @brief Driver Abstract type 
 */
#define T_FLASH_P    const uint8_t*

/** @defgroup FLASH_COMPILE Compilation Config */              /** @{ */

   #define   __FLASH_DRV_SPI__                            /**<     @macro __FLASH_DRV_SPI__  @brief SPI driver selector */
//  #define   __FLASH_DRV_I2C__                            /**<     @macro __FLASH_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __FLASH_DRV_UART__                           /**<     @macro __FLASH_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup FLASH_VAR Variables */                           /** @{ */

extern const uint8_t _FLASH_CMD_RDID  ;    // 25P80
extern const uint8_t _FLASH_CMD_READ  ;
extern const uint8_t _FLASH_CMD_WRITE ;
extern const uint8_t _FLASH_CMD_WREN  ;
extern const uint8_t _FLASH_CMD_RDSR  ;
extern const uint8_t _FLASH_CMD_ERASE ;    // 25P80
extern const uint8_t _FLASH_CMD_EWSR  ;    // 25P80
extern const uint8_t _FLASH_CMD_WRSR  ;
extern const uint8_t _FLASH_CMD_SER   ;    //25P80
extern const uint8_t _FLASH_CMD_WDIS  ;

                                                                       /** @} */
/** @defgroup FLASH_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup FLASH_INIT Driver Initialization */              /** @{ */

#ifdef   __FLASH_DRV_SPI__
void flash_spiDriverInit(T_FLASH_P gpioObj, T_FLASH_P spiObj);
#endif
#ifdef   __FLASH_DRV_I2C__
void flash_i2cDriverInit(T_FLASH_P gpioObj, T_FLASH_P i2cObj, uint8_t slave);
#endif
#ifdef   __FLASH_DRV_UART__
void flash_uartDriverInit(T_FLASH_P gpioObj, T_FLASH_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void flash_gpioDriverInit(T_FLASH_P gpioObj);
                                                                       /** @} */
/** @defgroup FLASH_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Flash click init
 *
 * Function that initializes Flash click by setting Chip select
 *
 */
void flash_init();
/**
 * @brief Flash click Write Enable
 *
 * Function that sends write enable command to the chip
 *
 */

void flash_WriteEnable();
/**
 * @brief Checks if the click is busy
 *
 * @retruns  1 - if still busy, 0 - if write completed
 * 
 * Function that checks whether chip finished write operation
 */
uint8_t flash_isWriteBusy();
/**
 * @brief Flash write byte
 *
 * 
 * @param value               8 bit value to be written
 * @param address             24 bit address
 *
 * Function that writes a single byte.  
 */
void flash_WriteByte(uint8_t value, uint32_t address);
/**
 * @brief Flash write word
 *
 * 
 * @param value               16 bit value to be written
 * @param address             24 bit address
 *
 *  Function that writes 2 succesive bytes of a word variable.  
 */
void flash_WriteWord(uint16_t value, uint32_t address);
/**
 * @brief Flash click Read ID
 *
 *
 * Function that reads the CHIP ID
 *
 */
uint8_t flash_ReadID();
/**
 * @brief Flash read byte
 * 
 * @param address             24 bit address
 *
 *  Function that reads the byte from the address  
 */
uint8_t flash_ReadByte(uint32_t address);
/**
 * @brief Flash read word
 *
 * @param address             24 bit address
 *
 *  Function that reads the word from the address  
 */
uint16_t flash_ReadWord(uint32_t address);
/**
 * @brief Flash write array
 *
 * @param address             24 bit address
 * @param pData               data to be written
 * @param nCount              number of bytes
 *
 * @returns 1 - if write succeeded, 0 - if write failed
 *  Function that writes data to successive addresses
 */

uint8_t flash_WriteArray(uint32_t address, uint8_t* pData, uint16_t nCount);
/**
 * @brief Flash read array
 *
 * @param address             24 bit address
 * @param pData               data to be read
 * @param nCount              number of bytes
 *
 *  Function that reads data from successive addresses
 */


void flash_ReadArray(uint32_t address, uint8_t* pData, uint16_t nCount);
/**
 * @brief Flash Chip erase
 *
 *
 *  Function that sends Chip Erase command 
 */
void flash_ChipErase();
/**
 * @brief Flash reset write protection
 *
 *
 *  Function that sends Reset Write Protection command
 */
void flash_ResetWriteProtection();
/**
 * @brief Flash sector erase
 *
 * @param address             24 bit address
 * Function that sends Sector Erase command
 */
void flash_SectorErase(uint32_t address);








                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Flash_STM.c
    @example Click_Flash_TIVA.c
    @example Click_Flash_CEC.c
    @example Click_Flash_KINETIS.c
    @example Click_Flash_MSP.c
    @example Click_Flash_PIC.c
    @example Click_Flash_PIC32.c
    @example Click_Flash_DSPIC.c
    @example Click_Flash_AVR.c
    @example Click_Flash_FT90x.c
    @example Click_Flash_STM.mbas
    @example Click_Flash_TIVA.mbas
    @example Click_Flash_CEC.mbas
    @example Click_Flash_KINETIS.mbas
    @example Click_Flash_MSP.mbas
    @example Click_Flash_PIC.mbas
    @example Click_Flash_PIC32.mbas
    @example Click_Flash_DSPIC.mbas
    @example Click_Flash_AVR.mbas
    @example Click_Flash_FT90x.mbas
    @example Click_Flash_STM.mpas
    @example Click_Flash_TIVA.mpas
    @example Click_Flash_CEC.mpas
    @example Click_Flash_KINETIS.mpas
    @example Click_Flash_MSP.mpas
    @example Click_Flash_PIC.mpas
    @example Click_Flash_PIC32.mpas
    @example Click_Flash_DSPIC.mpas
    @example Click_Flash_AVR.mpas
    @example Click_Flash_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __flash_driver.h

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

