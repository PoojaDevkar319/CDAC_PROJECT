#ifndef __ADXL345_H
#define __ADXL345_H

#include <stdint.h>

void ADXL_Init(void);
void ADXL_Write(uint8_t reg, uint8_t data);
uint8_t ADXL_Read(uint8_t reg);
void ADXL_ReadXYZ(int16_t *x, int16_t *y, int16_t *z);

float ADXL_Angle(float x, float y, float z);

#endif
