#include "adxl.h"
#include "i2c.h"
#include <math.h>

#define ADXL_ADDR 0x53   // 7-bit address

void ADXL_Write(uint8_t reg, uint8_t data)
{
    I2CStart();
    I2CWrite((ADXL_ADDR << 1), reg);     // Send register address
    I2CWrite((ADXL_ADDR << 1), data);    // Send data
    I2CStop();
}

uint8_t ADXL_Read(uint8_t reg)
{
    uint8_t data;

    I2CStart();
    I2CWrite((ADXL_ADDR << 1), reg);     // Select register
    I2CStart();
    I2CWrite((ADXL_ADDR << 1) | 1, 0xFF); // Dummy byte → enter read mode
    data = I2CReadNack();
    I2CStop();

    return data;
}

void ADXL_ReadXYZ(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t x0 = ADXL_Read(0x32);
    uint8_t x1 = ADXL_Read(0x33);
    uint8_t y0 = ADXL_Read(0x34);
    uint8_t y1 = ADXL_Read(0x35);
    uint8_t z0 = ADXL_Read(0x36);
    uint8_t z1 = ADXL_Read(0x37);

    *x = (int16_t)((x1 << 8) | x0);
    *y = (int16_t)((y1 << 8) | y0);
    *z = (int16_t)((z1 << 8) | z0);
}

void ADXL_Init(void)
{
    ADXL_Write(0x31, 0x08); // FULL RES + ±2g
    ADXL_Write(0x2D, 0x08); // Measurement mode
}

float ADXL_Angle(float x, float y, float z)
{
    return atan2(x, sqrt(y*y + z*z)) * 57.2958;
}
