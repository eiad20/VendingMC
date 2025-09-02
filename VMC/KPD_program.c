/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 25/8/2023     *****************/
/*****************    SWC  : KPD           *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/
/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_configer.h"

const u8 KPD_Au8Keys[4][4]= KPD_KEYS;

const u8 KPD_Au8RowsPins[4]={KPD_u8_R1_PIN,KPD_u8_R2_PIN,KPD_u8_R3_PIN,KPD_u8_R4_PIN};
const u8 KPD_Au8ColsPins[4]={KPD_u8_C1_PIN,KPD_u8_C2_PIN,KPD_u8_C3_PIN,KPD_u8_C4_PIN};


u8 KPD_u8GetKeyState(u8 * Copy_pu8ReturnedKey)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8RowsCounter, Local_u8ColsCounter ,Local_u8PinValue, Local_u8Flag = 0;
	if(Copy_pu8ReturnedKey != 0)
	{
		*Copy_pu8ReturnedKey = KPD_u8_KEY_NOT_PRESSED;
		/* Activate Each Row => For loop on the pins of the rows */
		for(Local_u8RowsCounter = 0; Local_u8RowsCounter <= 3 ; Local_u8RowsCounter++)
		{
			DIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8RowsCounter],DIO_LOW);
			/* Check Which Input Pin Has Zero */
			for(Local_u8ColsCounter = 0; Local_u8ColsCounter <= 3 ; Local_u8ColsCounter++)
			{
				DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8PinValue);
				if(Local_u8PinValue == DIO_LOW)/* Switch is Pressed */
				{
					/* Debouncing */
					_delay_ms(20);
					DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8PinValue);
					/* Check if the Pin is still equal LOW */
					while(Local_u8PinValue == DIO_LOW)
					{
						DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8PinValue);
					}
					*Copy_pu8ReturnedKey = KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					Local_u8Flag = 1;
					break;						
				}
			}
			/* Deactivate Row */
			DIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8RowsCounter],DIO_HIGH);
			if(Local_u8Flag == 1)
			{	
				break;	
			}
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int eval_expression(u8 *str)
{
	int num1 = 0;
   int num2 = 0;
   u8 operator ;
   int result = 0;
   int i = 0;

   while (str[i] != 0xff)
   {
       if (str[i] >= '0' && str[i] <= '9')
       {
           // Accumulate digits to form a number
           num2 = (num2 * 10) + (str[i] - '0');
       }
       else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
       {
       	result = num2;
           // Evaluate the previous operator and operand
           switch (operator)
           {
           case '+':
               result += num1;
               break;
           case '-':
               result -= num1;
               break;
           case '*':
               result *= num1;
               break;
           case '/':
        	   if( num1 == 0 )
        	   {
        		   result = KPD_u8_DIVIDED_BY_ZERO;
        	   }
        	   else
        	   {
        		   result /= num1;
        	   }

               break;
           }

           // Store the new operator and operand
           operator = str[i];
           num1 = num2;
           num2 = 0;
       }

       i++;
   }

   // Evaluate the final operator and operand
   switch (operator)
   {
   case '+':
       result += num2;
       break;
   case '-':
       result -= num2;
       break;
   case '*':
       result *= num2;
       break;
   case '/':
	   if( num2 == 0 )
	          	   {
		   	   	   	   result = KPD_u8_DIVIDED_BY_ZERO;
	          	   }
	          	   else
	          	   {
	          		   result /= num2;
	          	   }

       break;
   }

   return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Pass_intPassword (u8 *str)
{

     int num2 = 0;
     int i = 0;

   while (str[i] != KPD_u8_KEY_NOT_PRESSED)
   {
       if (str[i] >= '0' && str[i] <= '9')
       {
           num2 = (num2 * 10) + (str[i] - '0');
       }


        i++;
   }

   return num2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
