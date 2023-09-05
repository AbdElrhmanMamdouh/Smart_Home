#include "APP_Interface.h"

extern u8 G_u8LCDCursor, G_u8HKPReturn, G_u8Positioner;
extern u16 G_u16PasswordSave;


void APP_voidAppInit()
{
	HKP_voidInit();
	LCD_voidInit();
	TIMER1_voidFPWM();
}

void APP_voidAppLocked()
{
	SERVO_voidSetAngle(0);
	G_u8Positioner =  LOCKED;
	LCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);
	LCD_voidSetLocation(LCD_U8_LINE1,0);
	LCD_voidSendString("Enter Anything");
	LCD_voidSetLocation(LCD_U8_LINE2,0);
	LCD_voidSendString("to Enter Pass");

	while (G_u8HKPReturn == HKP_KEY_NOT_PRESSED)
	{
		G_u8HKPReturn = HKP_u8GetKeyValue();
	}
}


void APP_voidTakePassword(void)
{

}
