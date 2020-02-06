/*
 * Micro_Config.h
 *
 * Created: 1/12/2020 9:38:09 PM
 *  Author: Abdelaziz
 */ 


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_


#define F_CPU 1000000U
#define IO_OFFSET (0x20)
#include <util/delay.h>
#include "Std_Types.h"


/* The following union defines the 8-bit Register in the ATmega32A*/ 
typedef union
{
	volatile uint8 All_Register;
	struct
	{
		volatile uint8 b0:1;
		volatile uint8 b1:1;
		volatile uint8 b2:1;
		volatile uint8 b3:1;
		volatile uint8 b4:1;
		volatile uint8 b5:1;
		volatile uint8 b6:1;
		volatile uint8 b7:1;
	}Bits;
}Reg8;
	
								



#endif /* MICRO_CONFIG_H_ */