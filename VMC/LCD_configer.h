/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 20/8/2023     *****************/
/*****************    SWC  : LCD           *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/

#ifndef LCD_CONFIGER_H
#define LCD_CONFIGER_H

/*Options: 1- DIO_u8_PORTA
           2- DIO_u8_PORTB
           3- DIO_u8_PORTC
		   4- DIO_u8_PORTD
           */
#define LCD_u8_CONTROL_PORT    DIO_u8_PORTB

/*Options AT PORT U CHOSE IT IN LINE 16:
            1- DIO_u8_PIN0
            2- DIO_u8_PIN1
            .
		    .
		    .
		    8- DIO_u8_PIN7
		    */
#define LCD_u8_RS_PIN          DIO_u8_PIN0
#define LCD_u8_RW_PIN          DIO_u8_PIN1
#define LCD_u8_E_PIN           DIO_u8_PIN2

/*Options: 1- DIO_u8_PORTA
           2- DIO_u8_PORTB
           3- DIO_u8_PORTC
		   4- DIO_u8_PORTD
           */
#define LCD_u8_DATA_PORT       DIO_u8_PORTA

#endif
