#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <avr/io.h>
#include "ADC.h"

static void (*ADC_CONV_END)(void);

extern G_u8Check;

void ADC_voidInit (void)
{
	/* Select Vref = AVCC = 2.56V */
	SET_BIT(ADMUX , REFS1);
	SET_BIT(ADMUX , REFS0);
	/* 	2- Select Right Adjust*/
	CLR_BIT(ADMUX , ADLAR);
	/* 	3- Disable AutoTrigger Enable*/
	CLR_BIT(ADCSRA , ADATE);
	/* 	4- select CLK 'From 50 KHZ to 200 KHZ'---> Input CLK = 8 MHZ
	====> So We will select CLK / 64 */
	SET_BIT(ADCSRA , ADPS2);
	SET_BIT(ADCSRA , ADPS1);
	CLR_BIT(ADCSRA , ADPS0);
	/* 	1- Enable ADC*/
	SET_BIT(ADCSRA , ADEN);
}

u16  ADC_u16GetDigitalValue(u8 Copy_u8ChannelNum)
{
	G_u8Check = 0 ;
	u16 Local_u16ADCDigitalValue ;
	/*Clear MUX4......0*/
	ADMUX &= 0b11100000 ;
	/*Select Channel*/
	ADMUX |= Copy_u8ChannelNum ;
	/*Start conversion*/
	SET_BIT(ADCSRA , ADSC);
	/*Wait flag = 1*/
	while (GET_BIT(ADCSRA , ADIF) == 0  && G_u8Check == 0);
	/*Clear flag*/
	SET_BIT(ADCSRA , ADIF);
	/* Read the digital value from ADC_REG ==> "High & Low" */
	Local_u16ADCDigitalValue = ADC_REG ;
	return Local_u16ADCDigitalValue ;
}


void ADC_voidADCInt()
{
#if ADC_INT == ENABLE
	SET_BIT(ADCSRA, ADIE);
#elif ADC_INT == DISABLE
	CLR_BIT(ADCSRA, ADIE);
#endif
}

void ADC_voidADCIsDone()
{
	while( GET_BIT(ADCSRA, ADIF) == 0);
	SET_BIT(ADCSRA, ADIF);
}

void ADC_voidADCSetCallBack ( void (*copy_ADCEndConv) (void))
{
	ADC_CONV_END = copy_ADCEndConv;
}

ISR(ADC_vect)
{
	ADC_CONV_END();
}
