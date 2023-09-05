#ifndef HKP_INTERFACE_H
#define HKP_INTERFACE_H

#define HKP_PORT 			DIO_PORTB

#define HKP_R1_PIN 			DIO_PIN0
#define HKP_R2_PIN 			DIO_PIN1
#define HKP_R3_PIN 			DIO_PIN2
#define HKP_R4_PIN 			DIO_PIN3

#define HKP_C1_PIN 			DIO_PIN4
#define HKP_C2_PIN 			DIO_PIN5
#define HKP_C3_PIN 			DIO_PIN6
#define HKP_C4_PIN 			DIO_PIN7

#define	HKP_KEYS		   {{ 7, 8, 9, '/' },\
							{ 4, 5, 6, '*' },\
							{ 1, 2, 3, '-' },\
							{ 'C', 0, '=','+'}\
											}


#define HKP_KEY_NOT_PRESSED	0xFF

void HKP_voidInit(void);
u8 HKP_u8GetKeyValue(void);


#endif
