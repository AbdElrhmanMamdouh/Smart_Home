#ifndef ADC_H
#define ADC_H

#define 	ADC_REG		*(( volatile u16*)0x24)	/*Address to two bytes "LOW & HIGH"*/

#define ADC_MAXIMUM_VALUE    1023 /*depends on the ADC resolution if 10 bit 1023*/
#define ADC_REF_VOLT_VALUE   2.56


/*************INTERRUPT ENABLE**************/
#define ENABLE 	0
#define DISABLE 1
/*
 * SELECT INTERRUPT
 * ENABLE
 * DISABLE
 */
#define ADC_INT ENABLE
/***********************/
/***********************/


#define CHANNEL_0		0
#define CHANNEL_1		1
#define CHANNEL_2		2
#define CHANNEL_3		3
#define CHANNEL_4		4
#define CHANNEL_5		5
#define CHANNEL_6		6
#define CHANNEL_7		7

void ADC_voidInit (void);

void ADC_voidADCInt();

void ADC_voidADCIsDone();

void ADC_voidADCSetCallBack ( void (*copy_ADCEndConv) (void));

u16 ADC_u16GetDigitalValue (u8 Copy_u8ChannelNum);
#endif /* ADC_H_ */
