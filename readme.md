/*MCP23017 library
  choose mcp23017 address based on logic levels of your hardware addressable pins
  select sda and scl pin number based on the board you choose. 
  example is based on ESP-32 board.
  configuration register iocon consists of bank bit that determines register banks
  address formatting. before switching register address make sure change bank bit 
  accordingly.
*/