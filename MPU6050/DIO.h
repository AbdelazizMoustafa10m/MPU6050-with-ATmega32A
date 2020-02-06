/*
 * DIO.h
 *
 * Created: 1/22/2020 3:11:23 AM
 *  Author: Abdelaziz
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "Micro_Config.h"
#include "Macroos.h"
#include "Std_Types.h"

#define DIOA		((IO*)(0x19+IO_OFFSET))
#define DIOB		((IO*)(0x16+IO_OFFSET))
#define DIOC		((IO*)(0x13+IO_OFFSET))
#define DIOD		((IO*)(0x10+IO_OFFSET))

/* The Following structure defines the three registers that control the Digital IO Pins*/
typedef struct
{
	Reg8 PIN;
	Reg8 DDR;
	Reg8 PORT;	
}IO;

/* The Following Enumeration defines the state of any DIO Pin*/
typedef enum 
{
	INPUT,OUTPUT
}Pin_Mode;

/* The Following Enumeration defines the digital level of any DIO Pin*/
typedef enum
{
	LOW,HIGH
}Digital_Level;

/* The Following Enumeration defines the pin number of any DIO Port*/
typedef enum
{
	PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7
}Pin_Number;

/* The following function configures any DIO pin.*/
void DIO_PinConfigure(IO *Dio, Pin_Number Pin, Pin_Mode Mode);

/* The following function Writes a digital value to any DIO pin.*/
void DIO_PinWrite(IO *Dio, Pin_Number Pin, Digital_Level state);

/* The following function Reads a digital value from any DIO pin.*/
Digital_Level DIO_PinRead(IO *Dio, Pin_Number Pin);

#endif /* DIO_H_ */