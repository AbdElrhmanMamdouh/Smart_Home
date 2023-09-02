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


int main (){
	u8 local_u8PasswordSave = 0 , local_u8DefaultPassword = 1234 , local_u8AddedPassword = 1234;
	u8 Local_u8HKPReturn = HKP_KEY_NOT_PRESSED;
	HKP_voidInit();
	LCD_voidInit();
	TIMER1_voidFPWM();

	while(1){
		LCD_voidSendCommand(LCD_CLEAR);
		_delay_ms(2);
		LCD_voidSetLocation(LCD_LINE1,0);
		LCD_voidSendString("1 Enter Password");
		LCD_voidSetLocation(LCD_LINE2,0);
		LCD_voidSendString("2 Add Password");
		Local_u8HKPReturn = HKP_u8GetKeyValue();

		if (Local_u8HKPReturn !=HKP_KEY_NOT_PRESSED){

			switch	(Local_u8HKPReturn){
				case 1 : // To Open The Door
					LCD_voidSendCommand(LCD_CLEAR);
					_delay_ms(2);
					LCD_voidSetLocation(LCD_LINE1,0);
					LCD_voidSendString("Press = to Enter");
					if (Local_u8HKPReturn == '#'){
						if (local_u8PasswordSave ==  local_u8DefaultPassword || local_u8AddedPassword ){
							LCD_voidSendCommand(LCD_CLEAR);
							_delay_ms(2);
							LCD_voidSetLocation(LCD_LINE1,0);
							LCD_voidSendString("Door Open");
							SERVO_voidSetAngle(180);
							local_u8PasswordSave = 0 ;
						}
						else{
							LCD_voidSendCommand(LCD_CLEAR);
							_delay_ms(2);
							LCD_voidSetLocation(LCD_LINE1,0);
							LCD_voidSendString("Wrong Password");
							LCD_voidSetLocation(LCD_LINE2,0);
							LCD_voidSendString("Try Again!");
							local_u8PasswordSave = 0 ;
						}
					}
					else{
						local_u8PasswordSave = (local_u8PasswordSave*10)+Local_u8HKPReturn;
					}
					break;
				case 2 : // To Reset Password
					LCD_voidSendCommand(LCD_CLEAR);
					_delay_ms(2);
					LCD_voidSetLocation(LCD_LINE1,0);
					LCD_voidSendString("Enter Default");
					LCD_voidSetLocation(LCD_LINE2,0);
					LCD_voidSendString("Press = to Enter");
					if (Local_u8HKPReturn == '#'){
						if (local_u8PasswordSave ==  local_u8DefaultPassword ){
							LCD_voidSendCommand(LCD_CLEAR);
							_delay_ms(2);
							LCD_voidSetLocation(LCD_LINE1,0);
							LCD_voidSendString("Enter New Pass");
							LCD_voidSetLocation(LCD_LINE2,0);
							LCD_voidSendString("Press = to Enter");
							if (Local_u8HKPReturn == '#'){
								local_u8AddedPassword = local_u8PasswordSave;
							}
							else{
								local_u8PasswordSave = (local_u8PasswordSave*10)+Local_u8HKPReturn;
							}
						}
						else{
							LCD_voidSendCommand(LCD_CLEAR);
							_delay_ms(2);
							LCD_voidSetLocation(LCD_LINE1,0);
							LCD_voidSendString("Wrong Password");
							LCD_voidSetLocation(LCD_LINE2,0);
							LCD_voidSendString("Try Again!");
							local_u8PasswordSave = 0 ;
						}
					}
					else{
						local_u8PasswordSave = (local_u8PasswordSave*10)+Local_u8HKPReturn;
					}
					break;
				LCD_voidSendCommand(LCD_CLEAR);
				_delay_ms(2);
				LCD_voidSetLocation(LCD_LINE1,0);
				LCD_voidSendString("1 Enter Password");
				LCD_voidSetLocation(LCD_LINE2,0);
				LCD_voidSendString("2 Add Password");
				Local_u8HKPReturn = HKP_u8GetKeyValue();
			}
		}
	}
	return 0;
}
