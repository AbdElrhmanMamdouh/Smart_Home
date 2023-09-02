//LIB Layer
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>

//MCAL
#include "DIO_interface.h"
//HAL
#include "LCD_interface.h"

void pulse(void){
	DIO_voidSetPinValue(LCD_CONTROL_PORT,EN,1);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT,EN,0);
}

void LCD_voidInit(){
	/* Set Direction of Data Port as Output from MC*/
	DIO_voidSetPortDirection(LCD_DATA_PORT,0xff);

	/* Set Direction of Control Pins as Output from MC*/
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,RS,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,RW,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,EN,DIO_OUTPUT);

	_delay_ms(30);
	LCD_voidSendCommand(LCD_FUNC_SET);
	_delay_ms(1);
	LCD_voidSendCommand(LCD_ONOFF);
	_delay_ms(1);
	LCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);

	/* Entry Mode Set is Missed */

}

void LCD_voidSendCommand(u8 Copy_u8Command){

	DIO_voidSetPinValue(LCD_CONTROL_PORT,RS,0);
	DIO_voidSetPinValue(LCD_CONTROL_PORT,RW,0); // Active Low

	DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Command);
	pulse();
}

void LCD_voidSendChar(u8 Copy_u8Data){
	DIO_voidSetPinValue(LCD_CONTROL_PORT,RS,1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT,RW,0); // Active Low

	DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Data);
	pulse();
}

void LCD_voidSendString(u8 *Copy_u8String){
	for(u8 Local_u8Counter=0; Copy_u8String[Local_u8Counter] != '\0'; Local_u8Counter++){
	LCD_voidSendChar(Copy_u8String[Local_u8Counter]);
	}
}

void LCD_voidSetLocation(u8 Copy_u8LineNum, u8 Copy_u8CharNum){
	switch(Copy_u8LineNum){
	case LCD_LINE1:	LCD_voidSendCommand(0x80+Copy_u8CharNum);break;
	case LCD_LINE2:	LCD_voidSendCommand(0xc0+Copy_u8CharNum);break;
	}
}

void LCD_voidSendNumber(u32 Copy_u32Number)
{
	u32 Local_u32Counter=1 , Local_u32Digit=0;

	if (Copy_u32Number == 0)
		LCD_voidSendChar('0');
	else
	{
		while (Copy_u32Number/Local_u32Counter != 0)
		{
			Local_u32Counter *= 10;
		}
		Local_u32Counter /=10;

		while (Local_u32Counter != 0)
		{
			Local_u32Digit = Copy_u32Number/Local_u32Counter;

			LCD_voidSendChar(Local_u32Digit + '0');

			Copy_u32Number = Copy_u32Number%Local_u32Counter;

			Local_u32Counter /= 10;
		}
	}
}

