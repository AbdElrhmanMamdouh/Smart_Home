#include "APP_Interface.h"

extern u8 G_u8LCDCursor, G_u8HKPReturn, G_u8Positioner;
extern G_u8MotorState, G_u8Counter, G_u8Check;
extern G_u8Temperature, G_u16Intensity, G_u8Target;

extern u16 G_u16PasswordSave;


void APP_voidAppInit()
{
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN1, DIO_INPUT);

	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN1, DIO_HIGH);

	DIO_voidSetPinDirection(DIO_PORTA, LED_1, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA, LED_2, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA, LED_3, DIO_OUTPUT);

	DIO_voidSetPinDirection(DIO_PORTD, FAN_PIN, DIO_OUTPUT);

	TIMER1_voidFPWM();

	ADC_voidInit();

    //ADC_voidADCSetCallBack(control);

	ADC_voidADCInt();

	//EXTI_voidGIE();

	HKP_voidInit();
	LCD_voidInit();

	DCMOTOR_voidInit();
}

void APP_voidAppLocked()
{
	DCMOTOR_voidStop();
	SERVO_voidSetAngle(0);

	DIO_voidSetPinValue(DIO_PORTD, FAN_PIN, DIO_LOW);

	DIO_voidSetPinValue(DIO_PORTA, LED_1, DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, LED_2, DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, LED_3, DIO_LOW);

	G_u16PasswordSave = 0 ;
	G_u8LCDCursor = 0;
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

void APP_voidAppUnlocked(void)
{
	LCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);
	LCD_voidSetLocation(LCD_U8_LINE1,0);
	LCD_voidSendString("Door Opened");

	SERVO_voidSetAngle(90);
	G_u16PasswordSave = 0 ;
	G_u8LCDCursor = 0;
	G_u8Counter = 0;
	G_u8Positioner = UNLOCKED;

	LCD_voidSetLocation(LCD_U8_LINE2,0);
	LCD_voidSendString("Press C to exit");
	LCD_voidSendNumber(G_u8Positioner);
	_delay_ms(1000);
	LCD_voidSetLocation(LCD_U8_LINE1,0);
	LCD_voidSendString("Welcome, Sir.");
}


void APP_voidTakePassword(void)
{
	LCD_voidSetLocation(LCD_U8_LINE2, G_u8LCDCursor);
	LCD_voidSendChar(48 + G_u8HKPReturn);
	G_u16PasswordSave = (G_u16PasswordSave*10) + G_u8HKPReturn;
	G_u8LCDCursor ++;
}


void APP_ControlMotor(void)
{
	if (G_u8Positioner == UNLOCKED)
	{
		if ( (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)) && (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)) )
		{
			G_u8MotorState = MOTOR_ERROR;
			DCMOTOR_voidStop();
		}

		else if (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0) && (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)) )
		{
			G_u8MotorState = MOTOR_CW;
			DCMOTOR_voidRotateCW();
		}

		else if (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1) && (!DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)) )
		{
			G_u8MotorState = MOTOR_CCW;
			DCMOTOR_voidRotateCCW();
		}

		else if ( (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)) && (DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)) )
		{
			G_u8MotorState = MOTOR_STOP;
			DCMOTOR_voidStop();
		}
	}
}



void APP_ReadSensors(void)
{
	if (G_u8Positioner == UNLOCKED)
	{
		G_u8Temperature = LM35_TempSensor_u8ReadTemp();

		G_u16Intensity	= LDR_readint();
	}
}

void APP_Control(void)
{
	if (G_u8Positioner == UNLOCKED)
	{
		if (G_u8Temperature > 30)
		{
			DIO_voidSetPinValue(DIO_PORTD, FAN_PIN, DIO_HIGH);
		}
		else
		{
			DIO_voidSetPinValue(DIO_PORTD, FAN_PIN, DIO_LOW);
		}

		if (G_u16Intensity > 600)
		{
			DIO_voidSetPinValue(DIO_PORTA, LED_1, DIO_HIGH);
			DIO_voidSetPinValue(DIO_PORTA, LED_2, DIO_HIGH);
			DIO_voidSetPinValue(DIO_PORTA, LED_3, DIO_HIGH);

		}
		else
		{
			DIO_voidSetPinValue(DIO_PORTA, LED_1, DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTA, LED_2, DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTA, LED_3, DIO_LOW);
		}
	}
}

