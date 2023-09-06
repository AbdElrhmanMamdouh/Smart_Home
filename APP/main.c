#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include <avr/io.h>
#include "util/delay.h"
#include "../MCAL/DIO_Interface.h"
#include "../HAL/LCD_Interface.h"
#include "../HAL/LM35_Interface.h"

int main(void){
//	Initialize the LCD
	LCD_voidInit();

//	that code for tempterure sensor.

	u8 temp_value=LM35_TempSensor_u8ReadTemp();
	LCD_voidSetLocation(LCD_U8_LINE1,0);
	LCD_voidSendNumber(temp_value);
	_delay_ms(300);

//	LCD_voidSendCommand(0b00000001);

	//	that code for LDR sensor.

	u16 LDR_value= LDR_readint();
	LCD_voidSetLocation(LCD_U8_LINE2,0);
	LCD_voidSendNumber(LDR_value);

	return 0;
}

