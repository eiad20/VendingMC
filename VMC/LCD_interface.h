/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 20/8/2023     *****************/
/*****************    SWC  : LCD           *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H


#define LCD_u8_LINE1    1
#define LCD_u8_LINE2    2

/*Spiceal chars in CGRAM called in cmnd (64 BYTE DEVIDE INTO 8 CHAR )*/
#define LCD_u8_SPECIAL_CHAR0             0b01000000 //from 0 to 7
#define LCD_u8_SPECIAL_CHAR1             0b01001000 //from 8 to 15
#define LCD_u8_SPECIAL_CHAR2             0b01010000 //from 16 to 23
#define LCD_u8_SPECIAL_CHAR3             0b01011000 //from 24 to 31
#define LCD_u8_SPECIAL_CHAR4             0b01100000 //from 32 to 39
#define LCD_u8_SPECIAL_CHAR5             0b01101000 //from 40 to 47
#define LCD_u8_SPECIAL_CHAR6             0b01110000 //from 48 to 55
#define LCD_u8_SPECIAL_CHAR7             0b01111000 //from 56 to 63

void LCD_voidInit				(void);

void LCD_voidSendCmnd			(u8 Copy_u8Cmnd);

void LCD_voidSendChar			(u8 Copy_u8Char);

void LCD_voidSendString			(u8 *Copy_u8ArrOfString, u8 Copy_u8SizeOfString);

void LCD_voidWriteNum			(int Copy_u32Num);

u8 LCD_u8GoToxy					(u8 Copy_u8NumOfLine, u8 Copy_u8Location);

void LCD_voidWriteSpecialChar	(u8 Copy_u8CharNumInBinary, u8 Copy_u8CharNumInDismal , u8 *ptr, u8 Copy_u8NumLine , u8 Copy_u8Locationn);

void LCD_voidClearScreen		(void);

void LCD_voidMoveToLeft			(void);

void LCD_voidMoveToRight		(void);

#endif
