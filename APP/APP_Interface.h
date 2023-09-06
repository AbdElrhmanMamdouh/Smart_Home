/*
 * APP_Interface.h
 *
 *  Created on: Sep 5, 2023
 *      Author: User
 */

#ifndef APP_APP_INTERFACE_H_
#define APP_APP_INTERFACE_H_

#define PASS 1234

#define LOCKED 		0
#define UNLOCKED	1
#define PASSWORD	2
#define MOTOR_STATE	3

#define MOTOR_CW		3
#define MOTOR_CCW		4
#define MOTOR_STOP		5
#define MOTOR_ERROR		6




#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//MCAL
#include "../MCAL/DIO/DIO_interface.h"
//HAL
#include "../HAL/KEYPAD/HKP_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/SERVO/SERVOMOTOR_Interface.h"
#include "../HAL/DC_MOTOR/DCMOTOR_Interface.h"

void APP_voidAppInit();

void APP_voidAppLocked(void);

void APP_voidAppUnlocked(void);

void APP_voidTakePassword(void);

void APP_ControlMotor(void);


#endif /* APP_APP_INTERFACE_H_ */
