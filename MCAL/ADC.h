#ifndef ADC_H
#define ADC_H

#define 	ADC_REG		*(( volatile u16*)0x24)	/*Address to two bytes "LOW & HIGH"*/

#define ADC_MAXIMUM_VALUE    1023 /*depends on the ADC resolution if 10 bit 1023*/
#define ADC_REF_VOLT_VALUE   2.56



#define channel_0		0
#define channel_1		1
#define channel_2		2
#define channel_3		3
#define channel_4		4
#define channel_5		5
#define channel_6		6
#define channel_7		7

void ADC_voidInit (void);
u16 ADC_u16GetDigitalValue (u8 Copy_u8ChannelNum);
#endif /* ADC_H_ */
