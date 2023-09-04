#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include<util/delay.h>
#include"DIO_Interface.h"
#include"DCMOTOR_Interface.h"



void DCMOTOR_voidInit(void)
{
	DIO_voidSetPinDirection(DCMOTOR_PORT,DCMOTOR_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(DCMOTOR_PORT,DCMOTOR_PIN2,DIO_OUTPUT);
}
void DCMOTOR_voidRotateCW(void)
{
	DIO_voidSetPinValue(DCMOTOR_PORT,DCMOTOR_PIN1,DIO_HIGH);   //A
	DIO_voidSetPinValue(DCMOTOR_PORT,DCMOTOR_PIN2,DIO_LOW);    //B
}
void DCMOTOR_voidRotateCCW(void)
{
	DIO_voidSetPinValue(DCMOTOR_PORT,DCMOTOR_PIN1,DIO_LOW);   //A
	DIO_voidSetPinValue(DCMOTOR_PORT,DCMOTOR_PIN2,DIO_HIGH);  //B
}
void DCMOTOR_voidStop(void)
{
	DIO_voidSetPinValue(DCMOTOR_PORT,DCMOTOR_PIN1,DIO_LOW);  //A
	DIO_voidSetPinValue(DCMOTOR_PORT,DCMOTOR_PIN2,DIO_LOW);  //B
}
