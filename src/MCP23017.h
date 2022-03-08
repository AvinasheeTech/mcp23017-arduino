/*@brief  library for interacting with  MCP23017 I/O expander 
          over i2c communication
  @pinout

         .---------.
  GPB0<->|1  \_/ 28|<->GPA7
  GPB1<->|         |<->GPA6
  GPB2<->|    M    |<->GPA5
  GPB3<->|    C    |<->GPA4
  GPB4<->|    P    |<->GPA3
  GPB5<->|    2    |<->GPA2
  GPB6<->|    3    |<->GPA1
  GPB7<->|    0    |<->GPA0
   VDD-->|    1    |-->INTA
   VSS-->|    7    |-->INTB
   NC x--|         |-->~RESET
   SCL-->|         |<--A2
   SDA<->|         |<--A1
   NC x--|14     15|<--A0
         '---------'
*/


#ifndef _MCP23017_H_
#define _MCP23017_H_

#include <Wire.h> 
#include "Arduino.h"
#include <stdint.h> 

/*flag to select register bank addressing format*/
#define iocon_bank   0    

/*Port Definitions*/ 
#define MCP23017_PORTA      0x00
#define MCP23017_PORTB      0x01

/* Hardware Address Pins(A0-A2) 
       A2    A1    A0        7-bit slave address
      GND   GND   GND              0x20
      GND   GND   VCC              0x21
      GND   VCC   GND              0x22
      GND   VCC   VCC              0x23
      VCC   GND   GND              0x24
      VCC   GND   VCC              0x25
      VCC   VCC   GND              0x26
      VCC   VCC   VCC              0x27
*/
#define MCP23017_ADDRESS_20   0x20
#define MCP23017_ADDRESS_21   0x21
#define MCP23017_ADDRESS_22   0x22
#define MCP23017_ADDRESS_23   0x23
#define MCP23017_ADDRESS_24   0x24
#define MCP23017_ADDRESS_25   0x25
#define MCP23017_ADDRESS_26   0x26
#define MCP23017_ADDRESS_27   0x27

/* I/O Direction
 Default state: MCP23017_IODIR_ALL_INPUT
 */
#define MCP23017_IODIR_ALL_OUTPUT 0x00
#define MCP23017_IODIR_ALL_INPUT  0xFF
#define MCP23017_IODIR_IO0_INPUT  0x01
#define MCP23017_IODIR_IO1_INPUT  0x02
#define MCP23017_IODIR_IO2_INPUT  0x04
#define MCP23017_IODIR_IO3_INPUT  0x08
#define MCP23017_IODIR_IO4_INPUT  0x10
#define MCP23017_IODIR_IO5_INPUT  0x20
#define MCP23017_IODIR_IO6_INPUT  0x40
#define MCP23017_IODIR_IO7_INPUT  0x80

/*Input Polarity
  Default state: MCP23017_IPOL_ALL_NORMAL
*/
#define MCP23017_IPOL_ALL_NORMAL    0x00
#define MCP23017_IPOL_ALL_INVERTED  0xFF
#define MCP23017_IPOL_IO0_INVERTED  0x01
#define MCP23017_IPOL_IO1_INVERTED  0x02
#define MCP23017_IPOL_IO2_INVERTED  0x04
#define MCP23017_IPOL_IO3_INVERTED  0x08
#define MCP23017_IPOL_IO4_INVERTED  0x10
#define MCP23017_IPOL_IO5_INVERTED  0x20
#define MCP23017_IPOL_IO6_INVERTED  0x40
#define MCP23017_IPOL_IO7_INVERTED  0x80

/*Input Pull-Up Resistor
  Default state: MCP23017_GPPU_ALL_DISABLED
*/
#define MCP23017_GPPU_ALL_DISABLED  0x00
#define MCP23017_GPPU_ALL_ENABLED   0xFF
#define MCP23017_GPPU_IO0_ENABLED   0x01
#define MCP23017_GPPU_IO1_ENABLED   0x02
#define MCP23017_GPPU_IO2_ENABLED   0x04
#define MCP23017_GPPU_IO3_ENABLED   0x08
#define MCP23017_GPPU_IO4_ENABLED   0x10
#define MCP23017_GPPU_IO5_ENABLED   0x20
#define MCP23017_GPPU_IO6_ENABLED   0x40
#define MCP23017_GPPU_IO7_ENABLED   0x80

/*Register IOCON is shared between the two ports
  • If BANK = 1, the registers associated with each
    port are segregated. Registers associated with
    PORTA are mapped from address 00h - 0Ah and
    registers associated with PORTB are mapped
    from 10h - 1Ah.
  • If BANK = 0, the A/B registers are paired. For
    example, IODIRA is mapped to address 00h and
    IODIRB is mapped to the next address (address 01h). 
    The mapping for all registers is from 00h-15h.
*/


#if iocon_bank

/*Registers Definitions (IOCON.BANK = 1)*/
        #define REGISTER_IODIRA   0x00
        #define REGISTER_IPOLA    0x01
        #define REGISTER_GPINTENA 0x02
        #define REGISTER_DEFVALA  0x03
        #define REGISTER_INTCONA  0x04
        #define REGISTER_IOCON    0x05
        #define REGISTER_GPPUA    0x06
        #define REGISTER_INTFA    0x07
        #define REGISTER_INTCAPA  0x08
        #define REGISTER_INTCONB  0x09
        #define REGISTER_GPIOA    0x0A
        #define REGISTER_OLATA    0x0C
        #define REGISTER_IODIRB   0x10
        #define REGISTER_IPOLB    0x11
        #define REGISTER_GPINTENB 0x12
        #define REGISTER_DEFVALB  0x13
        #define REGISTER_INTCONB  0x14
        #define REGISTER_GPPUB    0x16
        #define REGISTER_INTFB    0x17
        #define REGISTER_INTCAPB  0x18
        #define REGISTER_GPIOB    0x19
        #define REGISTER_OLATB    0x1A

#else

/*Registers Definitions (IOCON.BANK = 0)
  Default address of Registers 
*/
        #define REGISTER_IODIRA   0x00
        #define REGISTER_IODIRB   0x01
        #define REGISTER_IPOLA    0x02
        #define REGISTER_IPOLB    0x03
        #define REGISTER_GPINTENA 0x04
        #define REGISTER_GPINTENB 0x05
        #define REGISTER_DEFVALA  0x06
        #define REGISTER_DEFVALB  0x07
        #define REGISTER_INTCONA  0x08
        #define REGISTER_INTCONB  0x09
        #define REGISTER_IOCON    0x0A
        #define REGISTER_GPPUA    0x0C
        #define REGISTER_GPPUB    0x0D
        #define REGISTER_INTFA    0x0E
        #define REGISTER_INTFB    0x0F
        #define REGISTER_INTCAPA  0x10
        #define REGISTER_INTCAPB  0x11
        #define REGISTER_GPIOA    0x12
        #define REGISTER_GPIOB    0x13
        #define REGISTER_OLATA    0x14
        #define REGISTER_OLATB    0x15

#endif


class MCP23017 {
public:
  MCP23017(uint8_t sda=21,uint8_t scl=22);      //constructor with default sda and scl pins 

  /*functions for operations*/
  uint8_t read(uint16_t reg, uint8_t address);
  void write(uint16_t reg, uint8_t data, uint8_t address);
  void iodir(uint8_t port, uint8_t iodir, uint8_t address);
  void ipol(uint8_t port, uint8_t ipol, uint8_t address);
  void gppu(uint8_t port, uint8_t pu, uint8_t address);
  uint8_t  read_gpio(uint8_t port, uint8_t address);
  void write_gpio(uint8_t port, uint32_t data, uint8_t address);
  uint8_t read_gpio_bit(uint8_t port, uint8_t pin, uint8_t address);
  void set_gpio_bit(uint8_t port, uint8_t pin, uint8_t address);
  void clear_gpio_bit(uint8_t port, uint8_t pin, uint8_t address);
};



#endif
