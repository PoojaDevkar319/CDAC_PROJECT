#include "stm32f4xx.h"
#include "lcd.h"
#include "i2c.h"
#include <stdio.h>
#include "adxl.h"

int main(void)
{
    char line1[16], line2[16];
    int16_t x, y, z;
    float ax, ay, az;
    float angleX, angleY;

    I2CInit();
    LcdInit();
    ADXL_Init();

    LcdPuts(LCD_LINE1, "ADXL345 Ready");
    DelayMs(1000);
    LcdClear();

    while(1)
    {
        ADXL_ReadXYZ(&x, &y, &z);

        // Convert raw to g (each LSB = 3.9 mg)
        ax = x * 0.0039;
        ay = y * 0.0039;
        az = z * 0.0039;

        angleX = ADXL_Angle(ax, ay, az);
        angleY = ADXL_Angle(ay, ax, az);

        sprintf(line1, "X:%0.2f Y:%0.2f", ax, ay);
        sprintf(line2, "AngX:%2.1f Ax:%2.1f", angleX, angleY);

        LcdPuts(LCD_LINE1, line1);
        LcdPuts(LCD_LINE2, line2);

        DelayMs(200);
    }
}
