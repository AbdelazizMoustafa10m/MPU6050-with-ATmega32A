/*
 * MPU6050.c
 *
 * Created: 1/26/2020 9:22:09 PM
 *  Author: Abdelaziz
 */ 

#include "MPU6050.h"

void MPU6050_Init(MPU6050_Freq Freq, MPU6050_CLKSource clk, Gyro_sampleRate S_Rate)
{
	_delay_ms(150);							/* Power up time >100ms */
	I2C_Start_Wait(MPU6050_WRITE_ADDRESS);	/* Start with device write address */
	I2C_Write(SMPLRT_DIV);					/* Write to sample rate register */
	I2C_Write(S_Rate);						/* 1KHz sample rate */
	I2C_Stop();

	I2C_Start_Wait(MPU6050_WRITE_ADDRESS);
	I2C_Write(PWR_MGMT_1);					/* Write to power management register */
	I2C_Write(clk);					    	/* X axis gyroscope reference frequency */
	I2C_Stop();

	I2C_Start_Wait(MPU6050_WRITE_ADDRESS);
	I2C_Write(CONFIG);						/* Write to Configuration register */
	I2C_Write(Freq);						/* Fs = 8KHz */
	I2C_Stop();

	I2C_Start_Wait(MPU6050_WRITE_ADDRESS);
	I2C_Write(GYRO_CONFIG);					/* Write to Gyro configuration register */
	I2C_Write(FULL_SCALE_FACTOR);			/* Full scale range +/- 2000 degree/C */
	I2C_Stop();

	I2C_Start_Wait(MPU6050_WRITE_ADDRESS);
	I2C_Write(INT_ENABLE);					/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();	
}
void MPU6050_READ(volatile MPU6050_Data *Data_Ptr)
{
	float32 Acc_x_Read;
	float32 Acc_y_Read;
	float32 Acc_z_Read;
	float32 Gyro_x_Read;
	float32 Gyro_y_Read;
	float32 Gyro_z_Read;
	float32 Temp;
	I2C_Start_Wait(MPU6050_WRITE_ADDRESS);		/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);					/* Write start location address from where to read */
	I2C_Repeated_Start(MPU6050_READ_ADDRESS);	/* I2C start with device read address */
	Acc_x_Read = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_y_Read = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_z_Read = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Temp = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_x_Read = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_y_Read = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_z_Read = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();
	/* Divide raw value by sensitivity scale factor to get real values */
	Data_Ptr->Acc_x = (Acc_x_Read/ACCEL_SENSTIVITY_FACTOR);
	Data_Ptr->Acc_y = (Acc_y_Read/ACCEL_SENSTIVITY_FACTOR);
	Data_Ptr->Acc_z = (Acc_z_Read/ACCEL_SENSTIVITY_FACTOR);
	Data_Ptr->Gyro_x = (Gyro_x_Read/GYRO_SENSTIVITY_FACTOR);
	Data_Ptr->Gyro_y = (Gyro_y_Read/GYRO_SENSTIVITY_FACTOR);
	Data_Ptr->Gyro_z = (Gyro_z_Read/GYRO_SENSTIVITY_FACTOR);
	/* Convert temperature in °/c using formula */
	Data_Ptr->Temperature = (Temp/340.00)+36.53;
}