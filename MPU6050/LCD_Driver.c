/*
 * LCD_Driver.c
 *
 * Created: 9/11/2018 4:21:13 AM
 *  Author: Abdelaziz
 */ 
 
 #include "LCD_Driver.h"
 #include<stdlib.h>
 
 /** 
 *  @file  <LCD_Driver.c>
 *  @brief <Implements the functions defined in the header file.>
 *
 *  @author<Eng/Abdelaziz Moustafa Abdelazem> 
 *  @date  <11-Sept-18>
 *
 */
 
 void LCD_init(void)
 {
	 /* Set The Control Pins Direction to OUtput */
	 LCD_Control_reg_DIR |=(1<<E) | (1<<RW) | (1<<RS);
	 
	 #if eight_bitdata
	 /* Set the Direction of the 8 Data pins to Output */
	 LCD_Data_Reg_DIR =0xFF;
	 #else
	 
	 #ifdef Upper_Data_port
	 /* Set The Direction of The Upper Pins to OP*/
	 LCD_Data_Reg_DIR |=(0xF0);
	 #else
	 /* Set The Direction of The LOWER Pins to OP*/
	 LCD_Data_Reg_DIR|=(0x0F);
	 #endif
	 Send_instruction(Return_Home);
	 #endif
	 
	 Send_instruction(Data_Set);
	 Send_instruction(Display_on);
	 Send_instruction(Clear_display);
 }
 
 void Send_instruction(uint8 instruction)
 {
	 /* RW, RS Should be 0 when Writing instructions to LCD */
	 CLEAR_BIT(LCD_Control_reg_OP,RS);
	 CLEAR_BIT(LCD_Control_reg_OP,RW);
	 /* Delay of Address Set 60ns minimum */
	 _delay_ms(1);
	 
	 /* Enable LCD E=1 */
	 SET_BIT(LCD_Control_reg_OP,E);
	 /* delay for processing PW min 450ns */
	 _delay_ms(1);
	 
	 #if eight_bitdata
	 
	 LCD_Data_Reg_OP = instruction;
	 /* Data set-up time delay  Tdsw = 195 ns */
	 _delay_ms(1);
	 /* disable LCD E=0 */
	 CLEAR_BIT(LCD_Control_reg_OP,E);
	 /* Data Hold delay Th = 10ns */
	 _delay_ms(1);
	 #else
	 
	 #ifdef Upper_Data_port
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0x0F;
	 LCD_Data_Reg_OP |= (instruction & 0xF0);
	 
	 #else	/* Lower Port */
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0xF0;
	 LCD_Data_Reg_OP |= ((instruction >> 4) & 0x0f);
	 #endif
	 /* Data set-up time delay  Tdsw = 195 ns */
	 _delay_ms(1);
	 
	 /* disable LCD E=0 */
	 CLEAR_BIT(LCD_Control_reg_OP,E);
	 /* Data Hold delay Th = 10ns */
	 _delay_ms(1);
	 
	 /* Enable LCD E=1 */
	 SET_BIT(LCD_Control_reg_OP,E);
	 /* delay for processing PW min 450ns */
	 _delay_ms(1);
	 #ifdef Upper_Data_port
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0x0F;
	 LCD_Data_Reg_OP |= ((instruction <<4) & 0xF0);
	 
	 #else	/* Lower Port */
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0xF0;
	 LCD_Data_Reg_OP |= ((instruction) & 0x0f);
	 #endif
	 /* Data set-up time delay  Tdsw = 195 ns */
	 _delay_ms(1);
	 /* disable LCD E=0 */
	 CLEAR_BIT(LCD_Control_reg_OP,E);
	 /* Data Hold delay Th = 10ns */
	 _delay_ms(1);
	 #endif
 }
 
 
 void LCD_DisplayChar(uint8 Data)
 {
	 /* RW  Should be 0  and RS should be 1 when Writing Data to LCD */
	 SET_BIT(LCD_Control_reg_OP,RS);
	 CLEAR_BIT(LCD_Control_reg_OP,RW);
	 /* Delay of Address Set 60ns minimum */
	 _delay_ms(1);
	 /* Enable LCD E=1 */
	 SET_BIT(LCD_Control_reg_OP,E);
	 /* delay for processing PW min 450ns */
	 _delay_ms(1);
	 #if eight_bitdata
	 LCD_Data_Reg_OP=Data;
	 #else
	 #ifdef Upper_Data_port
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0x0F;
	 /* Send MSB (4-bits )*/
	 LCD_Data_Reg_OP |= (Data & 0xF0);
	 
	 #else /* Lower Port */
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0xF0;
	 /* Send MSB (4-bits )*/
	 LCD_Data_Reg_OP |= ((Data >> 4) & 0x0f);
	 #endif
	 
	 /* Data set-up time delay  Tdsw = 195 ns */
	 _delay_ms(1);
	 /* disable LCD E=0 */
	 CLEAR_BIT(LCD_Control_reg_OP,E);
	 /* Data Hold delay Th = 10ns */
	 _delay_ms(1);
	 /* Enable LCD E=1 */
	 SET_BIT(LCD_Control_reg_OP,E);
	 
	 #ifdef Upper_Data_port
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0x0F;
	 LCD_Data_Reg_OP |= ((Data <<4) & 0xF0);
	 /* delay for processing PW min 450ns */
	 _delay_ms(1);
	 #else	/* Lower Port */
	 /* clear the Prev Data */
	 LCD_Data_Reg_OP &=0xF0;
	 LCD_Data_Reg_OP |= ((Data) & 0x0f);
	 #endif
	 
	 #endif
	 /* Data set-up time delay  Tdsw = 195 ns */
	 _delay_ms(1);
	 /* disable LCD E=0 */
	 CLEAR_BIT(LCD_Control_reg_OP,E);
	 /* Data Hold delay Th = 10ns */
	 _delay_ms(1);
	 
 }
 
 void LCD_Clear(void)
 {
	 /* Clear Screen */
	 Send_instruction(Clear_display);
 }
 
 
 void LCD_DisplayString(char * ptr)
 {
	 while(*ptr != '\0')
	 {
		 LCD_DisplayChar(*ptr);
		 ptr++;
	 }
 }
 
 void LCD_Select_RowCol(uint8 Row , uint8 col)
 {
	 uint8 Address=0;
	 
	 switch(Row)
	 {
		 case 0:
		 /* When Writing To LCD 1st Col The Base Address is 0x00 */
		 Address=col + LCD_1ST_BASE;
		 break;
		 case 1:
		 /* When Writing To LCD 2nd Col The Base Address is 0x40 */
		 Address=col + LCD_2ND_BASE;
		 break;
		 case 2:
		 /* When Writing To LCD 1st Col The Base Address is 0x10 */
		 Address = col + LCD_3RD_BASE;
		 break;
		 case 3:
		 /* When Writing To LCD 1st Col The Base Address is 0x50 */
		 Address=col + LCD_4TH_BASE;
		 break;
	 }
	 
	 Send_instruction(DDRAM_CONST|Address);
 }
 
 
 void LCD_DisplayInt(sint32 data)
 {
	 /* String to hold the Ascii result */
	 char Result[17];
	 /* 10 for decimal */
	 itoa(data,Result,10);
	 /* Display The Result */
	 LCD_DisplayString(Result);
 }
 
 void LCD_Custom_Char_Build (uint8 location, uint8 *Data)
 {
	 uint8 counter = 0;
	 if(location<MAX_NUM_OF_CUSTOM_GRAPHICS)
	 {
		 /* Command 0x40 and onwards forces the device to point CGRAM address */
		 Send_instruction (CUSTOM_GRAPHICS_COMMAND + (location*8));
		 /* Write 8 byte for generation of 1 character */
		 for(counter=0; counter<MAX_NUM_OF_CUSTOM_GRAPHICS; counter++)
		 LCD_DisplayChar(Data[counter]);
	 }
 }
 