  MCP23017 library for arduino based environment.
  example is based on ESP-32 board.
  choose mcp23017 address based on logic levels of your hardware addressable pins.
  select sda and scl pin number based on the board you choose. (Default SDA-21, SCL-22 for esp32).
  configuration register iocon consists of bank bit that determines register banks address formatting. 
  before switching register address make sure to write to bank bit accordingly.(Default bank bit = 0).
  
  functions available : 
  
  uint8_t read(uint16_t reg, uint8_t address);             //read register
  
  void write(uint16_t reg, uint8_t data, uint8_t address);      //write register
  
  void iodir(uint8_t port, uint8_t iodir, uint8_t address);     //set i/o pin direction(input or output)
  
  void ipol(uint8_t port, uint8_t ipol, uint8_t address);       //set input pin polarity for data representation 
  
  void gppu(uint8_t port, uint8_t pu, uint8_t address);         //select pullup registers for input pins 
  
  uint8_t  read_gpio(uint8_t port, uint8_t address);            //read selected gpio port 
  
  void write_gpio(uint8_t port, uint32_t data, uint8_t address);    //write selected gpio port
  
  uint8_t read_gpio_bit(uint8_t port, uint8_t pin, uint8_t address);   //read gpio pin selected
  
  void set_gpio_bit(uint8_t port, uint8_t pin, uint8_t address);       //set selected gpio pin (gpio pin logic high)
  
  void clear_gpio_bit(uint8_t port, uint8_t pin, uint8_t address);     //clear selected gpio pin (gpio pin logic low)
