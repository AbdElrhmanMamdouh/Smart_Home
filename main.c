#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include "avr/delay.h"
#include "DIO_Interface.h"
#include "DCMOTOR_Interface.h"
#include "LCD_Interface.h"

int main(){
	LCD_voidInit();
	DCMOTOR_voidInit();
	u8 Copy_U8StringCW[]= {"CW"};
	u8 Copy_U8StringCCW[]= {"CCW"};
	u8 Copy_u8PrintOnce = 0;
	DIO_voidSetPortDirection(DIO_PORTA, 0x00);
	while(1){
		while(DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)&&(!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1))){
			DCMOTOR_voidRotateCW();
			if(Copy_u8PrintOnce==0){
				LCD_voidSendString(Copy_U8StringCW);
				Copy_u8PrintOnce++;
			}
		}
		Copy_u8PrintOnce = 0;
		LCD_voidSendCommand(0b00000001);
		DCMOTOR_voidStop();
		while(DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)&&(!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0))){
			DCMOTOR_voidRotateCCW();
			if(Copy_u8PrintOnce==0){
				LCD_voidSendString(Copy_U8StringCCW);
				Copy_u8PrintOnce++;
			}
		}
		Copy_u8PrintOnce = 0;
		LCD_voidSendCommand(0b00000001);
		DCMOTOR_voidStop();
	}
	return 0;
}
