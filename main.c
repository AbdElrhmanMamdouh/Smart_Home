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

u8 G_u8LCDCursor, G_u8HKPReturn, G_u8Positioner, G_u8Counter;
u8 G_u8MotorState, G_u8Temperature;
u8 G_u8Target, G_u8Check;
u16 G_u16PasswordSave,  G_u16Intensity;



int main ()
{
    G_u16PasswordSave = 0;
    G_u8HKPReturn = HKP_KEY_NOT_PRESSED , G_u8Positioner =  LOCKED ;
    G_u8LCDCursor = 0;
    APP_voidAppInit();

    while(1)
    {
    		APP_voidAppLocked();

    		if (G_u8HKPReturn !=HKP_KEY_NOT_PRESSED)
    		{
    			G_u8Positioner = PASSWORD;
    			LCD_voidSendCommand(LCD_CLEAR);
    			_delay_ms(2);
    			LCD_voidSendString("Press = to Enter");
    			while (G_u8Positioner != LOCKED)
    			{
    				APP_ControlMotor();

    				APP_ReadSensors();

    				APP_Control();

    				G_u8HKPReturn = HKP_u8GetKeyValue();

    				if (G_u8HKPReturn !=HKP_KEY_NOT_PRESSED)
    				{
    					if (G_u8HKPReturn == '=')
    					{
    						if (G_u16PasswordSave ==  PASS) /*The Password Is Enterred Correctly*/
    						{
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
    					else if ( G_u8HKPReturn == '-')
    					{
    						LCD_voidSendCommand(LCD_CLEAR);
    						LCD_voidSetLocation(LCD_U8_LINE1,0);
    						LCD_voidSendString("Temp: ");
    						LCD_voidSendNumber(G_u8Temperature);

    						LCD_voidSetLocation(LCD_U8_LINE2,0);
    						LCD_voidSendString("Light: ");
    						LCD_voidSendNumber(G_u16Intensity);
    					}
    				}
    			}
    			G_u8HKPReturn = HKP_KEY_NOT_PRESSED ;
    		}
    	}
    	return 0;
    }


