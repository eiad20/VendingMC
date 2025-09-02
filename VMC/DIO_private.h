/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 16/8/2023     *****************/
/*****************    SWC  : DIO           *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/
  
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

               /* A */
#define DIO_u8_PORTA_REG *((volatile u8 *)0x3B)
#define DIO_u8_DDRA_REG  *((volatile u8 *)0x3A)
#define DIO_u8_PINA_REG  *((volatile u8 *)0x39)

		       /* B */
#define DIO_u8_PORTB_REG *((volatile u8 *)0x38)
#define DIO_u8_DDRB_REG  *((volatile u8 *)0x37)
#define DIO_u8_PINB_REG  *((volatile u8 *)0x36)

		       /* C */
#define DIO_u8_PORTC_REG *((volatile u8 *)0x35)
#define DIO_u8_DDRC_REG  *((volatile u8 *)0x34)
#define DIO_u8_PINC_REG  *((u8 *)0x33)

		       /* D */		
#define DIO_u8_PORTD_REG *((volatile u8 *)0x32)
#define DIO_u8_DDRD_REG  *((volatile u8 *)0x31)
#define DIO_u8_PIND_REG  *((volatile u8 *)0x30)

/* Pins Direction */
#define DIO_u8_INTIAL_OUTPUT                         1
#define DIO_u8_INTIAL_INPUT                          0

/* Pins Values */ 
#define DIO_u8_OUTPUT_LOW                            0
#define DIO_u8_OUTPUT_HIGH                           1
#define DIO_u8_INPUT_FLOATING                        0
#define DIO_u8_INPUT_PULLUP                          1
/* CONICAL */
#define Conc(b7,b6,b5,b4,b3,b2,b1,b0)           Conc_Help(b7,b6,b5,b4,b3,b2,b1,b0)
#define Conc_Help(b7,b6,b5,b4,b3,b2,b1,b0)      0b##b7##b6##b5##b4##b3##b2##b1##b0

																			
#endif