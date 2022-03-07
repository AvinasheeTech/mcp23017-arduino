#include "MCP23017.h"

/*pin definitions 
  choose sda and scl pins based on pin mapping of
  the board selected
*/
#define I2C_SDA        21
#define I2C_SCL        22

MCP23017 mcp1(I2C_SDA,I2C_SCL);    //create mcp instance

void setup() {
  // put your setup code here, to run once:

  /*set i/o pin direction as output for both ports A and B*/
  mcp1.iodir(0, 0x00 , MCP23017_ADDRESS_21);                  //send port=0x00 for GPIOA
  mcp1.iodir(1, 0x00 , MCP23017_ADDRESS_21);                  //send port=0x01 for GPIOB

}

void loop() {
  // put your main code here, to run repeatedly:

  /*set gpio port A and B output as high*/
  mcp1.write_gpio(0,  0xFF , MCP23017_ADDRESS_21);
  mcp1.write_gpio(1,  0xFF , MCP23017_ADDRESS_21);

  delay(500);

  /*set gpio port A and B output as low*/
  mcp1.write_gpio(0,  0x00 , MCP23017_ADDRESS_21);
  mcp1.write_gpio(1,  0x00 , MCP23017_ADDRESS_21);

  delay(500);


}
