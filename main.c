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

u8 G_u8LCDCursor, G_u8HKPReturn, G_u8Positioner, G_u8Counter, G_u8MotorState;
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
    			G_u8Positioner = PASSWORD;
    			LCD_voidSendCommand(LCD_CLEAR);
    			_delay_ms(2);
    			LCD_voidSendString("Press = to Enter");
    			while (G_u8Positioner != LOCKED)
    			{
//    				if (G_u8Positioner == UNLOCKED)
//    				{
//    					if ( (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)) && (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)) )
//    					{
//    						G_u8MotorState = MOTOR_ERROR;
//    						DCMOTOR_voidStop();
//    					}
//
//    					else if (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0) && (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)) )
//    					{
//							G_u8MotorState = MOTOR_CW;
//    						DCMOTOR_voidRotateCW();
//    					}
//
//    					else if (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1) && (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)) )
//						{
//							G_u8MotorState = MOTOR_CCW;
//							DCMOTOR_voidRotateCCW();
//						}
//
//    					else if ( (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)) && (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)) )
//						{
//							G_u8MotorState = MOTOR_STOP;
//							DCMOTOR_voidStop();
//						}
//    				}
    				APP_ControlMotor();

    				G_u8HKPReturn = HKP_u8GetKeyValue();

    				if (G_u8HKPReturn !=HKP_KEY_NOT_PRESSED)
    				{
    					if (G_u8HKPReturn == '=')
    					{
    						if (G_u16PasswordSave ==  PASS) /*The Password Is Enterred Correctly*/
    						{
//    							LCD_voidSendCommand(LCD_CLEAR);
//    							_delay_ms(2);
//    							LCD_voidSetLocation(LCD_U8_LINE1,0);
//    							LCD_voidSendString("Door Opened");
//
//    							SERVO_voidSetAngle(90);
//    							G_u16PasswordSave = 0 ;
//    							G_u8LCDCursor = 0;
//    							G_u8Counter = 0;
//    							G_u8Positioner = UNLOCKED;
//
//    							LCD_voidSetLocation(LCD_U8_LINE2,0);
//    							LCD_voidSendString("Press * to exit");
//    							LCD_voidSendNumber(G_u8Positioner);
//    							_delay_ms(1000);
//    							LCD_voidSetLocation(LCD_U8_LINE1,0);
//    							LCD_voidSendString("Welcome, Sir.");
    							APP_voidAppUnlocked();
    						}
    						else	/*The Password is Enterred Wrong*/
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
    					else if (G_u8HKPReturn == 'C') //Retruning to LOCKED Mode
    					{
    						APP_voidAppLocked();
    					}
    					else if (G_u8HKPReturn >= 0 && G_u8HKPReturn <= 9) //Taking Numbers for password
    					{
//    						LCD_voidSetLocation(LCD_U8_LINE2, G_u8LCDCursor);
//    						LCD_voidSendChar(48 + G_u8HKPReturn);
//    						G_u16PasswordSave = (G_u16PasswordSave*10) + G_u8HKPReturn;
//    						G_u8LCDCursor ++;
//
    						APP_voidTakePassword();

    					}

    					else if ( G_u8HKPReturn == '+') /*Show/Hide Motor State*/
    					{
							if (G_u8MotorState == MOTOR_CW)
							{
								LCD_voidSendCommand(LCD_CLEAR);
								LCD_voidSendString("ClockWise");
							}
							else if (G_u8MotorState == MOTOR_CCW)
							{
								LCD_voidSendCommand(LCD_CLEAR);
								LCD_voidSendString("CounterClockWise");
							}
							if (G_u8MotorState == MOTOR_ERROR)
							{
								LCD_voidSendCommand(LCD_CLEAR);
								LCD_voidSendString("Error");
							}
							if (G_u8MotorState == MOTOR_STOP)
							{
								LCD_voidSendCommand(LCD_CLEAR);
								LCD_voidSendString("Stop");
							}
    					}
    				}
    			}
    			G_u8HKPReturn = HKP_KEY_NOT_PRESSED ;
    		}
    	}
    	return 0;
    }
