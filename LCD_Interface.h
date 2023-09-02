#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LCD_DATA_PORT		DIO_PORTC
#define LCD_CONTROL_PORT	DIO_PORTD
#define RS					DIO_PIN0
#define RW					DIO_PIN1
#define EN					DIO_PIN2

#define	LCD_FUNC_SET	0b00111000
#define	LCD_ONOFF		0b00001111
#define	LCD_CLEAR		0b00000001

#define LCD_LINE1	1
#define LCD_LINE2	2

void pulse(void);
void LCD_voidInit();
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendChar(u8 Copy_u8Data);
void LCD_voidSendString(u8 *Copy_u8String);
void LCD_voidSetLocation(u8 Copy_u8LineNum, u8 Copy_u8CharNum);
void LCD_voidSendNumber(u32 Copy_u32Number);

#endif
