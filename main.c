/*
 * main.c
 *
 *  Created on: Aug 15, 2023
 *      Author: AbdElrhman Mamdouh
 */

//LIB Layer
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

//MCAL
#include "DIO_interface.h"
//HAL
#include "HKP_interface.h"
#include "LCD_interface.h"
#include "SERVOMOTOR_Interface.h"

#define PASS 1234


int main (){
    u16 local_u16PasswordSave = 0;
    u8  Local_u8HKPReturn = HKP_KEY_NOT_PRESSED , flag1=0 ;

	HKP_voidInit();
	LCD_voidInit();
	TIMER1_voidFPWM();

	while(1){

		LCD_voidSendCommand(LCD_CLEAR);
		_delay_ms(2);
		LCD_voidSetLocation(LCD_U8_LINE1,0);
		LCD_voidSendString("Enter Anything");
		LCD_voidSetLocation(LCD_U8_LINE2,0);
		LCD_voidSendString("to Enter Pass");

		while (Local_u8HKPReturn == HKP_KEY_NOT_PRESSED){
			Local_u8HKPReturn = HKP_u8GetKeyValue();
		}

		if (Local_u8HKPReturn !=HKP_KEY_NOT_PRESSED){
			flag1=1;
			LCD_voidSendCommand(LCD_CLEAR);
			_delay_ms(2);
			LCD_voidSendString("Press = to Enter");
			while (flag1){
				Local_u8HKPReturn = HKP_u8GetKeyValue();
				if (Local_u8HKPReturn !=HKP_KEY_NOT_PRESSED){

					if (Local_u8HKPReturn == '#'){
						if (local_u16PasswordSave ==  PASS){
							LCD_voidSendCommand(LCD_CLEAR);
							_delay_ms(2);
							LCD_voidSetLocation(LCD_U8_LINE1,0);
							LCD_voidSendString("Door Opened");
							SERVO_voidSetAngle(90);
							local_u16PasswordSave = 0 ;
							LCD_voidSetLocation(LCD_U8_LINE2,0);
							LCD_voidSendString("Press * to exit");
						}

						else{
							LCD_voidSendCommand(LCD_CLEAR);
							_delay_ms(2);
							LCD_voidSetLocation(LCD_U8_LINE1,0);
							LCD_voidSendString("Wrong Password");
							LCD_voidSetLocation(LCD_U8_LINE2,0);
							// LCD_voidSendNumber(local_u16PasswordSave);
							LCD_voidSendString("Try Again!");
							local_u16PasswordSave = 0 ;
						}

					}
					else if (Local_u8HKPReturn == '*'){
						flag1=0;
						SERVO_voidSetAngle(0);

					}
					else{

						local_u16PasswordSave = (local_u16PasswordSave*10)+Local_u8HKPReturn;
					}

				}
			}
			Local_u8HKPReturn =HKP_KEY_NOT_PRESSED ;
		}

	}
	return 0;
}
