/*
 * MPU6050.c
 *
 * Created: 1/26/2020 7:39:57 PM
 * Author : Abdelaziz
 */ 

#include "MPU6050.h"
#include "LCD_Driver.h"

volatile MPU6050_Data Live_Data;
int main(void)
{
    LCD_init();											  	 /* Initialize the LCD */
	I2C_Init();												 /* Initialize I2C */
	MPU6050_Init(_8KHz_Fs,Gyro_Xaxsis_Ref,_1KHz_SampleRate); /* Initialize MPU6050 */
    while (1) 
    {
		MPU6050_READ(&Live_Data);
		LCD_Clear();
		LCD_DisplayString("Ax=");
		LCD_DisplayInt((uint16) (Live_Data.Acc_x));
		LCD_DisplayString("  Ay=");
		LCD_DisplayInt((uint16) (Live_Data.Acc_y));
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("Az=");
		LCD_DisplayInt((uint16) (Live_Data.Acc_z));
		LCD_Select_RowCol(2,0);
		LCD_DisplayString("Gx=");
		LCD_DisplayInt((uint16) (Live_Data.Gyro_x));
		LCD_DisplayString("  Gy=");
		LCD_DisplayInt((uint16) (Live_Data.Gyro_y));
		LCD_Select_RowCol(3,0);
		LCD_DisplayString("Gz=");
		LCD_DisplayInt((uint16) (Live_Data.Gyro_z));
		LCD_DisplayString("  Temp=");
		LCD_DisplayInt((uint16) (Live_Data.Temperature));
		_delay_ms(500);
		LCD_Clear();
		LCD_DisplayString("Updating ..");
		_delay_ms(500);
    }
}

