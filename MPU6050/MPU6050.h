/*
 * MPU6050.h
 *
 * Created: 1/26/2020 8:02:24 PM
 *  Author: Abdelaziz
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

#include "Micro_Config.h"
#include "Std_Types.h"
#include "Macroos.h"
#include "MPU6050_Registers.h"
#include "I2C_Master_H_file.h"

#define MPU6050_WRITE_ADDRESS   (0xD0)
#define MPU6050_READ_ADDRESS    (0xD1)
#define FULL_SCALE_FACTOR	    (0x18)
#define ACCEL_SENSTIVITY_FACTOR (16384)
#define GYRO_SENSTIVITY_FACTOR  (16.4)

typedef struct
{
	float32 Acc_x;
	float32 Acc_y;
	float32 Acc_z;
	float32 Gyro_x;
	float32 Gyro_y;
	float32 Gyro_z;
	float32 Temperature;
}MPU6050_Data;

typedef enum
{
	_1KHz_Fs = 0x01,
	_8KHz_Fs = 0x00		
}MPU6050_Freq;

typedef enum
{
	_1KHz_SampleRate = 0x07,	
	_2KHz_SampleRate = 0x03,
	_4KHz_SampleRate = 0x01
}Gyro_sampleRate;

typedef enum
{
	Internal_8KHz       = 0x00,
	Gyro_Xaxsis_Ref     = 0x01,   //Recommended by Datasheet for improved stability
	Gyro_Yaxsis_Ref     = 0x02,
	Gyro_Zaxsis_Ref     = 0x03,
	External_32_768KHz  = 0x02,
	External_19_2MHz    = 0x02,
}MPU6050_CLKSource;

void MPU6050_Init(MPU6050_Freq Freq, MPU6050_CLKSource clk, Gyro_sampleRate S_Rate);
void MPU6050_READ(volatile MPU6050_Data *Data_Ptr);

#endif /* MPU6050_H_ */