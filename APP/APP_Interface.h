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
#define MOTOR		2
#define HOME		3







#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

//MCAL
#include "../MCAL/DIO/DIO_interface.h"
//HAL
#include "../HAL/KEYPAD/HKP_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/SERVO/SERVOMOTOR_Interface.h"

void APP_voidAppInit();

void APP_voidAppLocked(void);

void APP_voidTakePassword(void);



#endif /* APP_APP_INTERFACE_H_ */
