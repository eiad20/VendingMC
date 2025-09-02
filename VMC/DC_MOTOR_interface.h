/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 27/8/2023     *****************/
/*****************    SWC  : DC_MOTOR      *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

// configuration
#define MOTOR_PORT	DIO_PORTA
#define MOTOR_ENA	DIO_PIN0
#define MOTOR_IN1	DIO_PIN1
#define MOTOR_IN2	DIO_PIN2

void MOTOR_voidCWMotion(void);

void MOTOR_voidCCWMotion(void);

void MOTOR_voidStopMotion(void);


#endif /* DC_MOTOR_H_ */