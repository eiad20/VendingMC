#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include <avr/io.h>
#include <util/delay.h>

// Run selected motor
void Motor_Run(u8 motorPin)
 {
	if( motorPin == 0)
	   {
	      DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN0, DIO_HIGH);
	   }
	else if (motorPin == 1)
	{
		DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN2, DIO_HIGH);
	}
 }


// Stop selected motor
void Motor_Stop(u8 motorPin)
{
	if( motorPin == 0)
		   {
		      DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN0, DIO_LOW);
		   }
		else if (motorPin == 1)
		{
			DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN2, DIO_LOW);
		}
}
// Blinking
void Blink (u8 port , u8 pin)
{    for (u8 i = 0; i < 6; i++)
     {
	 DIO_u8SetPinValue( port, pin, DIO_HIGH);
	 _delay_ms(100);
	 DIO_u8SetPinValue( port, pin, DIO_LOW);
	 _delay_ms(100);
     }
}

int main(void)
{

    u8 smiley[8] =
       {0b00000,
        0b01010,
        0b01010,
        0b00000,
        0b10001,
        0b01110,
        0b00000,
        0b00000};


    u8 key;
    u16 soldCount[2] = {0};
    u16 balance = 0;
    u16 users = 0;
    u16 cash = 0;
    u8 item = 0;
    u16 remaining = 0;
    u8 prices[2] = {10 , 15};

    DIO_voidInit();
    LCD_voidInit();
    while (1)
    {
    	restart:
        balance = 0; // Reset for new customer
        LCD_voidClearScreen();
        LCD_voidSendString("Enter Balance", 14);
        LCD_u8GoToxy(2, 0);

        // Balance entry
        while (1)
        {
            KPD_u8GetKeyState(&key);
            if (key != KPD_u8_KEY_NOT_PRESSED)
            {
                 if (key >= '0' && key <= '9')
                {
                    balance = balance * 10 + (key - '0');
                    LCD_voidSendChar(key);
                }

                 else if (key == 'c')
                 {
                	 goto restart;
                 }

                 else if (key == '=')
                {
                    break;
                }
            }
        }
        if (balance == 9047)
         {
          	LCD_voidClearScreen();
          	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN4,DIO_HIGH);
           	LCD_voidSendString("Admin Access", 13);
            _delay_ms(1000);
           	LCD_voidClearScreen();
            LCD_voidSendString("Users = ", 9);
            LCD_voidWriteNum(users);
            LCD_u8GoToxy(2,0);
            LCD_voidSendString("Cash = ", 8);
            LCD_voidWriteNum(cash);
            _delay_ms(3000);
            LCD_voidClearScreen();

                // First item at row 1, col 0
                LCD_u8GoToxy(1, 0);
                LCD_voidSendString("Chips ", 6);
                //LCD_voidWriteNum(1);
                LCD_voidSendString(" x", 3);
                LCD_voidWriteNum(soldCount[0]);

                // Second item at row 2, col 0
                LCD_u8GoToxy(2, 0);
                LCD_voidSendString("Cola", 5);
                //LCD_voidWriteNum(2);
                LCD_voidSendString(" x", 3);
                LCD_voidWriteNum(soldCount[1]);
                _delay_ms(2000);
                DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN4,DIO_LOW);
              goto restart;
         }
        // Item selection
        LCD_voidClearScreen();
        LCD_voidSendString("Select Item", 12);
        while (1)
        {
            KPD_u8GetKeyState(&key);
            if (key != KPD_u8_KEY_NOT_PRESSED)
            {
                if ( key == 'c')
                {
                	goto restart;
                }
            	else if (key >= '1' && key <= '8')
                {
                    item = key - '1';
                    LCD_voidClearScreen();

                    if (balance >= prices[item])
                    {
                        remaining = balance - prices[item];

                        Motor_Run(item);
                        _delay_ms(500);
                        Motor_Stop(item);
                        LCD_voidClearScreen();
                        LCD_voidSendString("Come Again", 11);
                        LCD_voidWriteSpecialChar(LCD_u8_SPECIAL_CHAR0, 0, smiley, 1, 11);
                        LCD_u8GoToxy(2, 0);
                        LCD_voidSendString("Change= ", 8);
                        LCD_voidWriteNum(remaining);
                        Blink(DIO_u8_PORTB,DIO_u8_PIN3);
                        cash = cash + prices[item];
                        users++;
                        soldCount[item]++;
                    }
                    else
                    {
                        LCD_voidSendString("Insufficient", 13);
                        LCD_u8GoToxy(2, 0);
                        LCD_voidSendString("Balance", 8);
                        Blink(DIO_u8_PORTB ,DIO_u8_PIN5);

                    }
                    _delay_ms(3000);
                    break;
                }
            }
        }
    }
}



