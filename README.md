![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Flash Click

---

- **CIC Prefix**  : FLASH
- **Author**      : MikroE Team
- **Verison**     : 1.0.0
- **Date**        : jan 2018.

---

### Software Support

We provide a library for the Flash Click on our [LibStock](http://libstock.mikroe.com/projects/view/384/flash-click-example}) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**


Key functions :

- ``` uint8_t flash_WriteArray(uint32_t address, uint8_t* pData, uint16_t nCount); ``` - Function that writes data to successive addresses
- ``` void flash_ReadArray(uint32_t address, uint8_t* pData, uint16_t nCount) ``` -  Function that reads data to successive addresses


**Examples Description**

- System Initialization -  CS GPIO and SPI module initialization 
- Application Initialization - Flash click driver and click initialization
- Application Task - Writing data to click memory and displaying the read data via UART. 


```.c

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

```



The full application code, and ready to use projects can be found on our 
[LibStock](http://libstock.mikroe.com/projects/view/384/flash-click-example) page.

Other mikroE Libraries used in the example:

- SPI
- UART


**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
