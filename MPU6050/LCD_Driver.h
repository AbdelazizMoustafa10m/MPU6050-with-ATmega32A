/*
 * LCD_Driver.h
 *
 * Created: 9/11/2018 3:47:47 AM
 *  Author: Abdelaziz
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

	#include <avr/io.h>
	#include "Micro_Config.h"
	#include "Macroos.h"
	#include "Std_Types.h"
	
 /** 
 *  @file  <LCD_Driver.h>
 *  @brief <Header File of any Alphanumeric LCD <(16x1),(16x2),(20x2),(20x4)> library.>
 *         <It contains The Prototypes of all function available in
 *          the library,definitions of all Macros, and Enumerations> 
 *
 *  @author<Eng/Abdelaziz Moustafa Abdelazem> 
 *  @date  <11-Sept-18>
 *
 */
   
   
   /* Hardware Connections */
   #define  RS   PD5
   #define  RW   PD6
   #define  E    PD7

   #define LCD_Control_reg_DIR DDRD
   #define LCD_Control_reg_OP  PORTD
   #define LCD_Control_reg_IP	PIND
   
   #define LCD_Data_Reg_DIR DDRA
   #define LCD_Data_Reg_OP	PORTA
   #define LCD_Data_Reg_IP	PINA
   
   /* Define Upper Data to Use The Higher 4 Pins PD4 --> PD7 */
   #define Upper_Data_port 1
   /* uncomment This line to Use The Lower Port */
   #if 0
   #undef Upper_Data_port
   #endif
   
   /* Initiation Settings */
   #define CURSOR              (0)		                    /* 1 to Enable , 0 to Disable */
   #define Blink	           (0)	                       /* 1 to Enable , 0 to Disable */
   #define eight_bitdata       (0)                        /* 1 to Enable , 0 for 4 bit */
   #define _5x10_Dot	       (0)	                     /* 1 to Enable , 0 for 5 x 8 Dot */
   #define Two_Four_lines	   (1)                      /* 1 to Enable 2 or 4 lines , 0 for 1 or 2 Line */

   /* Making an error if the user selected to work with two/four line and 5x10 dot.*/
   #if ( _5x10_Dot && Two_lines )
                 #pragma GCC error "You cannot Have Two Lines LCD with 5 * 10"
   #endif
   
   /* List Of Command Codes */
   #define Clear_display 0x01
   #define Return_Home	  0x02
   #define Display_off   0x08
   #define Display_on   (0x0C | (CURSOR<<1) | (Blink))
   #define CURSOR_Shift_Right	 0x14
   #define CURSOR_Shift_left	 0x10
   #define Display_shift_left    0x18
   #define Display_shift_Right	  0x1C
   #define Data_Set (0x20 |(_5x10_Dot<<2)|(Two_Four_lines<<3)| (eight_bitdata<<4))
   #define DDRAM_CONST 0x80
   
   /* For Making Custom Graphics */
   #define CUSTOM_GRAPHICS_COMMAND      (0x40)
   #define MAX_NUM_OF_CUSTOM_GRAPHICS   (8)
   
   /* Address of each Row.*/ 
   #define LCD_1ST_BASE 0x00
   #define LCD_2ND_BASE 0x40
   #define LCD_3RD_BASE 0x14
   #define LCD_4TH_BASE 0x54
   
   #define LCD_LEFT 1
   #define LCD_RIGHT 0
   
   #define LCD_Shift(DIR)	((DIR == LCD_LEFT)? Send_instruction(Display_shift_left) : Send_instruction(Display_shift_Right))
   #define LCD_CURSOR_Shift(DIR) ((DIR == LCD_LEFT)? Send_instruction(CURSOR_Shift_left) : Send_instruction(CURSOR_Shift_Right))
   
    /** 
	 *  @brief <void Send_instruction(uint8 instruction)>
	 *  <This function will be used to Send an instruction to the LCD controller.>
	 *
	 *  @param uint8 <instruction> <the command to be send to the LCD controller.>
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void Send_instruction(uint8 instruction);
   
   /** 
	 *  @brief <void LCD_init(void)>
	 *  <This function will be used to Initiate the LCD.>
	 *
	 *  @param void < >
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void LCD_init(void);
   
   /** 
	 *  @brief <void LCD_Clear(void)>
	 *  <This function will be used to clear the LCD screen.>
	 *
	 *  @param void < >
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void LCD_Clear(void);
   
   /** 
	 *  @brief <void LCD_DisplayChar(uint8 Data)>
	 *  <This function will be used to display a character on the screen.>
	 *
	 *  @param uint8 <Data> <The data to be displayed on the screen.>
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void LCD_DisplayChar(uint8 Data);
   
   /** 
	 *  @brief <void LCD_DisplayString(char * ptr)>
	 *  <This function will be used to display a string on the screen.>
	 *
	 *  @param char <* ptr> <pointer to char data.>
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void LCD_DisplayString(char * ptr);
   
   /** 
	 *  @brief <void LCD_Select_RowCol(uint8 Row , uint8 col)>
	 *  <This function will be used to slect the row and column.>
	 *
	 *  @param uint8 <Row> <the row number.>
	 *  @param uint8 <col> <the column number.>
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void LCD_Select_RowCol(uint8 Row , uint8 col);
   /** 
	 *  @brief <void LCD_DisplayInt(sint32 data)>
	 *  <This function will be used to display an interger number on the screen.>
	 *
	 *  @param sint32 <data> <the interger value to be displayed on the screen.>
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void LCD_DisplayInt(sint32 data);
   
   /** 
	 *  @brief <void LCD_Custom_Char_Build(uint8 location, uint8 *Data)>
	 *  <This function will be used to build a custom character and send to the CGRAM.>
	 *
	 *  @param uint8 <location> <the location in the CGRAM to store the Custom character.>
	 *  @param uint8 <*Data> <pointer to char array which contains the representation of the custom character.>
	 *
	 *  @return <This Function Returns Void.>
	 *
	 */
   void LCD_Custom_Char_Build (uint8 location, uint8 *Data); 

#endif /* LCD_DRIVER_H_ */