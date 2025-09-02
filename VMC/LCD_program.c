/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 20/8/2023     *****************/
/*****************    SWC  : LCD           *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/

/*LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*Delay*/
#define F_CPU 8000000UL
#include <util/delay.h>

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_configer.h"

//////////////////////////////////////////////////////////////////////////////////////////////
void LCD_voidInit(void)
{
	/*Function set Cmnd RS=0   RW=0 ..... DB4 = DL = 1 -->(8 BITS MODE)   N = 1 -->(2 LINES)  F = 0 -->(5*7 DOTS)  */
	/*                                    DB4 = DL = 0 -->(4 BITS MODE)   N = 0 -->(1 LINES)  F = 1 -->(5*10 DOTS) */                                                  
	_delay_ms(35);
	LCD_voidSendCmnd(0b00111000);
	_delay_ms(40);
	/* RS=0   RW=0 ..... D = 1 -->(Display on)   C = 1 -->(CURSER DISPLAY ONLY IN 5*7)  B = 0 -->(dont blink)  */
	/*                   D = 0 -->(Display off)  C = 0 -->(NOT DISPLAY )                B = 1 -->(Blink curser)*/ 
    /*CURSER IS LOOK LIKE THIS _ _	*/
	LCD_voidSendCmnd(0b00001111);
	_delay_ms(40);
	/*Display clear*/  
	LCD_voidSendCmnd(0x01);
	_delay_ms(2);
	/* RS=0   RW=0 ..... ID = 1 -->( MOVE TO RIGHT)  SH = 0 -->(SHIFTING LEFY)  */
	/*                   ID = 0 -->( MOVE TO LEFT)   SH = 1 -->(DONT SHEFT)     */   
	LCD_voidSendCmnd(0b00000110);

}
//////////////////////////////////////////////////////////////////////////////////////////////
void LCD_voidSendCmnd(u8 Copy_u8Cmnd)
{
	/*  RS = 0  */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_LOW);
	
	/*  RW = 0  */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_LOW);
	
	/*WRITE CMND*/
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd);

	/*  E = 1   */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_HIGH);
	_delay_us(1);
	/*  E = 0   */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_LOW) ;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void LCD_voidSendChar(u8 Copy_u8Char)
{
	/*  RS = 1  */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_HIGH);
	
	/*  RW = 0  */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_LOW);
	
	/*WRITE DATA*/
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char);

	/*  E = 1   */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_HIGH);
	_delay_us(1);
	/*  E = 0   */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_LOW) ;	
}
//////////////////////////////////////////////////////////////////////////////////////////////
void LCD_voidSendString(u8 *Copy_u8ArrOfString, u8 Copy_u8SizeOfString)
{
	for(u8 i = 0; i < Copy_u8SizeOfString-1; i++)
	{
		LCD_voidSendChar(Copy_u8ArrOfString[i]);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void LCD_voidWriteNum(int Copy_u32Num)
{
	if(Copy_u32Num == 0)
	{
		LCD_voidSendChar('0');
	}else if( (Copy_u32Num >= 10) && (Copy_u32Num < 100) )
	{
		int Local_u32Hshrat = (Copy_u32Num / 10) ;
		int Local_u32Ahad   = Copy_u32Num -(Local_u32Hshrat*10);
		char h = (u8)Local_u32Hshrat + 48;
		char a = (u8)Local_u32Ahad   + 48;
		LCD_voidSendChar(h);
		LCD_voidSendChar(a);
	}
	else if( (Copy_u32Num >= 100) && (Copy_u32Num < 1000) )
	{
		int Local_u32Meaat     = (Copy_u32Num / 100) ;
		int Local_u32Hashrat   = (Copy_u32Num -(Local_u32Meaat*100)) / 10;
		int Local_u32Ahad      = (Copy_u32Num -(Local_u32Meaat*100)) - (Local_u32Hashrat*10);

		char m = (char)Local_u32Meaat + 48;
		char h = (char)Local_u32Hashrat + 48;
		char a = (char)Local_u32Ahad   + 48;
		LCD_voidSendChar(m);
		LCD_voidSendChar(h);
		LCD_voidSendChar(a);

	}
	else if( (Copy_u32Num >= 1000) && (Copy_u32Num < 10000) )
	{
		int Local_u32Alafat    = (Copy_u32Num / 1000) ;
		int Local_u32Meaat     = (Copy_u32Num -(Local_u32Alafat*1000)) / 100 ;
		int Local_u32Hashrat   = (Copy_u32Num -(Local_u32Meaat*100 + Local_u32Alafat*1000)) / 10;
		int Local_u32Ahad      = (Copy_u32Num -(Local_u32Meaat*100 + Local_u32Alafat*1000 + Local_u32Hashrat*10));

		char alf = (char)Local_u32Alafat + 48;
		char   m = (char)Local_u32Meaat + 48;
		char   h = (char)Local_u32Hashrat + 48;
		char   a = (char)Local_u32Ahad   + 48;
	    LCD_voidSendChar(alf);
		LCD_voidSendChar(m);
		LCD_voidSendChar(h);
		LCD_voidSendChar(a);
	}
	else if( (Copy_u32Num >= 10000) && (Copy_u32Num < 100000) )
	{
		int Local_u32HashrTalaf= (Copy_u32Num / 10000) ;
		int Local_u32Alafat    = (Copy_u32Num -(Local_u32HashrTalaf*10000)) / 1000 ;
		int Local_u32Meaat     = (Copy_u32Num -(Local_u32Alafat*1000 + Local_u32HashrTalaf*10000)) / 100;
		int Local_u32Hashrat   = (Copy_u32Num -(Local_u32Meaat*100 + Local_u32Alafat*1000 + Local_u32HashrTalaf*10000)) / 10;
		int Local_u32Ahad      = (Copy_u32Num -(Local_u32Meaat*100 + Local_u32Alafat*1000 + Local_u32Hashrat*10 + Local_u32HashrTalaf*10000));
		char hashralf = (char)Local_u32HashrTalaf + 48;
		char alf = (char)Local_u32Alafat + 48;
		char   m = (char)Local_u32Meaat + 48;
		char   h = (char)Local_u32Hashrat + 48;
		char   a = (char)Local_u32Ahad   + 48;
		LCD_voidSendChar(hashralf);
	    LCD_voidSendChar(alf);
		LCD_voidSendChar(m);
		LCD_voidSendChar(h);
		LCD_voidSendChar(a);
	}
	else if( (Copy_u32Num > 0) && (Copy_u32Num < 10) )
		{
		int Local_u32Hshrat = (Copy_u32Num / 10) ;
		int Local_u32Ahad   = Copy_u32Num -(Local_u32Hshrat*10);
			//u8 h = (u8)Local_u32Hshrat + 48;
		char a = (char)Local_u32Ahad   + 48;
			LCD_voidSendChar(a);
		}
		
}
//////////////////////////////////////////////////////////////////////////////////////////////
u8 LCD_u8GoToxy(u8 Copy_u8NumOfLine, u8 Copy_u8Location)
{
	u8 Local_Error = STD_TYPES_OK;
	if( (Copy_u8Location <= 39) && ( (Copy_u8NumOfLine == LCD_u8_LINE1)||(Copy_u8NumOfLine == LCD_u8_LINE2) )   )
	{
		switch(Copy_u8NumOfLine)
		{
			case LCD_u8_LINE1: LCD_voidSendCmnd(0x80+Copy_u8Location); break;
			case LCD_u8_LINE2: LCD_voidSendCmnd(0xc0+Copy_u8Location); break;
		}
	}else
	{
	 Local_Error = STD_TYPES_NOK;
	}
	return Local_Error;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void LCD_voidWriteSpecialChar(u8 Copy_u8CharNumInBinary, u8 Copy_u8CharNumInDismal , u8 *ptr, u8 Copy_u8NumLine , u8 Copy_u8Locationn)
{
	 LCD_voidSendCmnd(Copy_u8CharNumInBinary);
		 LCD_voidSendChar(ptr[0]);
		 LCD_voidSendChar(ptr[1]);
		 LCD_voidSendChar(ptr[2]);
		 LCD_voidSendChar(ptr[3]);
		 LCD_voidSendChar(ptr[4]);
		 LCD_voidSendChar(ptr[5]);
		 LCD_voidSendChar(ptr[6]);
		 LCD_voidSendChar(ptr[7]);
		 LCD_u8GoToxy(Copy_u8NumLine, Copy_u8Locationn);
		LCD_voidSendChar(Copy_u8CharNumInDismal);
}

 //////////////////////////////////////////////////////////////////////////////////////////////
 
 void LCD_voidClearScreen(void)
 {
 	LCD_voidSendCmnd(0x01);
 	 _delay_ms(2);
 }
 
 //////////////////////////////////////////////////////////////////////////////////////////////
 
 void LCD_voidMoveToLeft			(void)
 {
	  LCD_voidSendCmnd(0b00011000);
	 _delay_ms(100);
 }

 //////////////////////////////////////////////////////////////////////////////////////////////
 
 void LCD_voidMoveToRight		(void)
 {
	 LCD_voidSendCmnd(0b00011100);
	 _delay_ms(100);
 }
 
 //////////////////////////////////////////////////////////////////////////////////////////////




 //////////////////////////////////////////////////////////////////////////////////////////////
