#include "MCP23017.h"

/*@brief initialize i2c 
  @param sda and scl pin number
*/
MCP23017::MCP23017(uint8_t sda,uint8_t scl){
  Wire.begin(sda, scl);     
}

/*@brief  read the register value 
  @param  register address to read,and i2c address of the device
  @retval current register data
*/
uint8_t MCP23017::read(uint16_t reg, uint8_t address)
{
  uint8_t c;
  Wire.beginTransmission(address);    //send start bit
  Wire.write(reg);                    //send write bit with i2c slave address
  Wire.endTransmission();             //send stop bit 

  Wire.requestFrom(address, 1);       

  while (Wire.available()) { // slave may send less than requested
    c = Wire.read();         // receive a byte as character
    Serial.print(c);         // print the character
  }

  return c;

}

/*@brief  write data to register 
  @param  register address to write to,data to be written
          and i2c address of the device
  @retval None
*/
void MCP23017::write(uint16_t reg, uint8_t data, uint8_t address)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

/*@brief  set direction of I/O pins 
  @param  port number, i/o direction data and i2c address of the device
  @retval None
*/
void MCP23017::iodir(uint8_t port, uint8_t iodir, uint8_t address)
{
  Wire.beginTransmission(address);
  Wire.write(REGISTER_IODIRA | port);  //selects i/o direction register to write based on port chosen
  Wire.write(iodir);                   //writes direction data
  Wire.endTransmission();
}

/*@brief  configure the polarity of I/O pins
  @param  port number, i/o polarity data and i2c address of the device
  @retval None
  @note 1 = GPIO register bit reflects the opposite logic state of the input pin.
        0 = GPIO register bit reflects the same logic state of the input pin.
*/
void MCP23017::ipol(uint8_t port, uint8_t ipol, uint8_t address)
{
  Wire.beginTransmission(address);
  Wire.write(REGISTER_IPOLA | port);
  Wire.write(ipol);
  Wire.endTransmission();
}

/*@brief  set input pullup 
  @param  port number, pullup data and i2c address of the device
  @retval None
*/
void MCP23017::gppu(uint8_t port, uint8_t pu, uint8_t address)
{
  Wire.beginTransmission(address);
  Wire.write(REGISTER_GPPUA | port);
  Wire.write(pu);
  Wire.endTransmission();
}

/*@brief  read selected gpio port
  @param  port number, and i2c address of the device
  @retval current gpio port state
*/
uint8_t  MCP23017::read_gpio(uint8_t port, uint8_t address)
{
  uint8_t c;
  Wire.beginTransmission(address);
  Wire.write(REGISTER_GPIOA | port);
  Wire.endTransmission();

  Wire.requestFrom(address, 1);    

  while (Wire.available()) { // slave may send less than requested
    c = Wire.read();         // receive a byte as character
    Serial.print(c);         // print the character
  }

  return c;
}

/*@brief  write selected gpio port
  @param  port number, data to be written and i2c address of the device
  @retval None
*/
void MCP23017::write_gpio(uint8_t port, uint32_t data, uint8_t address)
{
  Wire.beginTransmission(address);
  Wire.write(REGISTER_GPIOA | port);
  Wire.write(data);
  Wire.endTransmission();
}

/*@brief  read selected gpio port bit
  @param  port number, i/o pin to be read and i2c address of the device
  @retval current gpio pin state
*/
uint8_t  MCP23017::read_gpio_bit(uint8_t port, uint8_t pin, uint8_t address)
{
  uint8_t c;
  Wire.beginTransmission(address);
  Wire.write(REGISTER_GPIOA | port);
  Wire.endTransmission();

  Wire.requestFrom(address, 1);    

  while (Wire.available()) { // slave may send less than requested
    c = Wire.read();         // receive a byte as character
    Serial.print(c);         // print the character
  }

  c = c & (1<<pin);
  return c;
}

/*@brief  set selected gpio port bit
  @param  port number, i/o pin to set and i2c address of the device
  @retval None
*/
void MCP23017::set_gpio_bit(uint8_t port, uint8_t pin, uint8_t address)
{
  /*read existing port data*/
  uint8_t reg_data = read_gpio(port,address);

  Wire.beginTransmission(address);
  Wire.write(REGISTER_GPIOA | port);
  Wire.write(reg_data | (1<<pin));
  Wire.endTransmission();
}

/*@brief  clear selected gpio port bit
  @param  port number, i/o pin to clear and i2c address of the device
  @retval None
*/
void MCP23017::clear_gpio_bit(uint8_t port, uint8_t pin, uint8_t address)
{
  /*read existing port data*/
  uint8_t reg_data = read_gpio(port,address);
  
  pin = (1<<pin);
  pin ^= 0xFF;

  Wire.beginTransmission(address);
  Wire.write(REGISTER_GPIOA | port);
  Wire.write(reg_data & pin);
  Wire.endTransmission();
}
