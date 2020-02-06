/*
 * DIO.c
 *
 * Created: 1/22/2020 3:40:02 AM
 *  Author: Abdelaziz
 */ 

#include "DIO.h"

void DIO_PinConfigure(IO *Dio, Pin_Number Pin, Pin_Mode Mode)
{
	switch(Mode)
	{
		case INPUT:
					CLEAR_BIT(Dio->DDR.All_Register,Pin);
					break;
		case OUTPUT:
					SET_BIT(Dio->DDR.All_Register,Pin);
					break;
		default:
					break;
	}
}
void DIO_PinWrite(IO *Dio, Pin_Number Pin, Digital_Level state)
{
	switch(state)
	{
		case HIGH:
					SET_BIT(Dio->PORT.All_Register,Pin);
					break;
		case LOW:
					CLEAR_BIT(Dio->PORT.All_Register,Pin);
					break;
		default:
					break;
	}
	
}

Digital_Level DIO_PinRead(IO *Dio, Pin_Number Pin)
{
	Digital_Level Read_Value = 0;
	switch(READ_BIT(Dio->PIN.All_Register,Pin))
	{
		case LOW:
					Read_Value = LOW;
					break;
		case HIGH:
					Read_Value= HIGH;	
					break;
		default:
					break;
	}
	return Read_Value;
}