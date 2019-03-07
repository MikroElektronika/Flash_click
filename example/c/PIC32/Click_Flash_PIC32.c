/*
Example for Flash Click

    Date          : jan 2018.
    Author        : MikroE Team

Test configuration PIC32 :
    
    MCU                : P32MX795F512L
    Dev. Board         : EasyPIC Fusion v7
    PIC32 Compiler ver : v4.0.0.0

---
Description :

The application is composed of three sections :

- System Initialization -  CS GPIO and SPI module initialization 
- Application Initialization - Flash click driver and click initialization
- Application Task - Writing data to click memory and displaying the read data via UART. 

*/

#include "Click_Flash_types.h"
#include "Click_Flash_config.h"



char wrData [10] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
char rdData [10];

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_spiInit( _MIKROBUS1, &_FLASH_SPI_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 9600 );

    Delay_ms( 100 );
}

void applicationInit()
{
    flash_spiDriverInit( (T_FLASH_P)&_MIKROBUS1_GPIO, (T_FLASH_P)&_MIKROBUS1_SPI );
     
}

void applicationTask()
{
    flash_SectorErase(0x015015);
    mikrobus_logWrite("Writing MikroE to  Flash memory, from address 0x015015:",_LOG_LINE);
    flash_WriteArray (0x015015, &wrData[0], 9);
    mikrobus_logWrite("Reading 9 bytes of Flash memory, from address 0x015015:",_LOG_LINE);
    flash_ReadArray (0x015015,&rdData[0],9);
    mikrobus_logWrite("Data read: ",_LOG_TEXT);
    mikrobus_logWrite(rdData,_LOG_LINE);
    Delay_ms(1000);


}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
    	applicationTask();
    }
}