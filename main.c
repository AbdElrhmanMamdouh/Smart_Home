/*
 * main.c
 *
 *  Created on: Aug 15, 2023
 *      Author: AbdElrhman Mamdouh
 */

////LIB Layer
//#include "LIB/STD_TYPES.h"
//#include "LIB/BIT_MATH.h"
//#include <avr/io.h>
//#include <avr/delay.h>
//#include <avr/interrupt.h>
//
////MCAL
//#include "MCAL/DIO/DIO_interface.h"
////HAL
//#include "HAL/KEYPAD/HKP_Interface.h"
//#include "HAL/LCD/LCD_Interface.h"
//#include "HAL/SERVO/SERVOMOTOR_Interface.h"

#include "APP/APP_Interface.h"

u8 G_u8LCDCursor, G_u8HKPReturn, G_u8Positioner;
u16 G_u16PasswordSave;


int main ()
{
    G_u16PasswordSave = 0;
    G_u8HKPReturn = HKP_KEY_NOT_PRESSED , G_u8Positioner =  LOCKED ;
    G_u8LCDCursor = 0;
    APP_voidAppInit();

    while(1)
    {
//			SERVO_voidSetAngle(0);
//			G_u8Positioner =  LOCKED;
//    		LCD_voidSendCommand(LCD_CLEAR);
//    		_delay_ms(2);
//    		LCD_voidSetLocation(LCD_U8_LINE1,0);
//    		LCD_voidSendString("Enter Anything");
//    		LCD_voidSetLocation(LCD_U8_LINE2,0);
//    		LCD_voidSendString("to Enter Pass");
//
//    		while (G_u8HKPReturn == HKP_KEY_NOT_PRESSED)
//    		{
//    			G_u8HKPReturn = HKP_u8GetKeyValue();
//    		}
    		APP_voidAppLocked();

    		if (G_u8HKPReturn !=HKP_KEY_NOT_PRESSED)
    		{
//    			G_u8Positioner = UNLOCKED;
    			LCD_voidSendCommand(LCD_CLEAR);
    			_delay_ms(2);
    			LCD_voidSendString("Press = to Enter");
    			while (G_u8Positioner != LOCKED)
    			{
    				G_u8HKPReturn = HKP_u8GetKeyValue();
    				if (G_u8HKPReturn !=HKP_KEY_NOT_PRESSED)
    				{
    					if (G_u8HKPReturn == '=')
    					{
    						if (G_u16PasswordSave ==  PASS)
    						{
    							LCD_voidSendCommand(LCD_CLEAR);
    							_delay_ms(2);
    							LCD_voidSetLocation(LCD_U8_LINE1,0);
    							LCD_voidSendString("Door Opened");
    							SERVO_voidSetAngle(90);
    							G_u16PasswordSave = 0 ;
    							LCD_voidSetLocation(LCD_U8_LINE2,0);
    							LCD_voidSendString("Press * to exit");
    						    G_u8LCDCursor = 0;
    						}

    						else
    						{
    							LCD_voidSendCommand(LCD_CLEAR);
    							_delay_ms(2);
    							LCD_voidSetLocation(LCD_U8_LINE1,0);
    							LCD_voidSendString("Wrong Password");
    							_delay_ms(1000);
    							LCD_voidSendCommand(LCD_CLEAR);
    							LCD_voidSetLocation(LCD_U8_LINE1,0);
    							LCD_voidSendString("Try Again!");
    							G_u16PasswordSave = 0 ;
    						    G_u8LCDCursor = 0;
    						}
    					}
    					else if (G_u8HKPReturn == '*')
    					{
    						G_u8Positioner = LOCKED;
    						SERVO_voidSetAngle(0);
    					}
    					else
    					{

    						LCD_voidSetLocation(LCD_U8_LINE2, G_u8LCDCursor);
    						LCD_voidSendChar(48 + G_u8HKPReturn);
    						G_u16PasswordSave = (G_u16PasswordSave*10) + G_u8HKPReturn;
    						G_u8LCDCursor ++;
    					}

    				}
    			}
    			G_u8HKPReturn =HKP_KEY_NOT_PRESSED ;
    		}
    	}
    	return 0;
    }
