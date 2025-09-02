/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 27/8/2023     *****************/
/*****************    SWC  : DC_MOTOR      *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/

/*LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "DC_MOTOR_interface.h"
#include "DC_MOTOR_configer.h"

///////////////////////////////////////////////////////////////
void MOTOR_voidCWMotion(void)
{
	DIO_u8SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_LOW);
	DIO_u8SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_HIGH);
}
///////////////////////////////////////////////////////////////
void MOTOR_voidCCWMotion(void)
{
	DIO_u8SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_LOW);
	DIO_u8SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_HIGH);
}
///////////////////////////////////////////////////////////////
void MOTOR_voidStopMotion(void)
{
	DIO_u8SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_LOW);
	DIO_u8SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_LOW);
}
///////////////////////////////////////////////////////////////