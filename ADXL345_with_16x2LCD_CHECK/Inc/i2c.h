void I2CStart(void);
void I2CStop(void);
void I2CWrite(uint8_t addr, uint8_t data);   // You MUST give 2 parameters
uint8_t I2CReadNack(void);                    // Available
