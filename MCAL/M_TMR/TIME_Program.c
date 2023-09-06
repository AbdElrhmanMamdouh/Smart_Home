#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "math.h"
#include <avr/interrupt.h>
#include "../DIO/DIO_Interface.h"
#include "TIME_Interface.h"

#define NULL ((void *)0)

static void (*TIMER_PFTIMER0OVF)(void) = NULL;
static void (*TIMER_PFTIMER0COMP)(void) = NULL;


static void (*TIMER_PFTIMER2OVF)(void) = NULL;
static void (*TIMER_PFTIMER2COMP)(void) = NULL;

static u8  G_u8Reg;
static u32 G_u32Overflows;

u32* P_u32OVF_Ptr;

static volatile u8 G_u8Check;
////////////////////////////////////////////////////////////////////////////////////////



void MTIMER_voidTimer0OVFInit(void)
{
	/*CHOOSE NORMAL MODE*/
		CLR_BIT(TCCR0, WGM00);
		CLR_BIT(TCCR0, WGM01);

		SET_BIT(TIMSK, TOIE0);

#if		CLK == ONE
		TCCR0 = (TCCR0 & 0xf8) | 0x01;
#elif 	CLK == EIGHT
		TCCR0 = (TCCR0 & 0xf8) | 0x02;
#elif 	CLK == SIXTYFOUR
		TCCR0 = (TCCR0 & 0xf8) | 0x03;
#elif 	CLK == TWOFIFTYSIX
		TCCR0 = (TCCR0 & 0xf8) | 0x04;
#elif 	CLK == TENTWENTYFOUR
		TCCR0 = (TCCR0 & 0xf8) | 0x05;
#elif 	CLK == EXTERN_FALLING
		TCCR0 = (TCCR0 & 0xf8) | 0x06;
#elif 	CLK == EXTERN_RISING
		TCCR0 = (TCCR0 & 0xf8) | 0x07;
#endif

}

void MTIMER_voidTimer0OVFDelay(u32 copy_u32Delay_ms)
{
	f32 L_f32MaxCompare;
	f32 L_f32OverFlowCount;
	u32 L_u32Carry;
	u8 L_u8Offset;

	G_u8Check = 0;
	MTIMER_voidTimer0OVFInit();

#if		CLK == ONE
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256;
#elif 	CLK == EIGHT
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 8;
#elif 	CLK == SIXTYFOUR
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 64;
#elif 	CLK == TWOFIFTYSIX
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 256;
#elif 	CLK == TENTWENTYFOUR
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 1024;

#endif


	if (copy_u32Delay_ms * 1000  <= L_f32MaxCompare)
		{
			L_f32OverFlowCount = (copy_u32Delay_ms / (L_f32MaxCompare/1000.0));
			L_u8Offset = L_f32OverFlowCount * 256.0;
			G_u32Overflows = 1;
			G_u8Reg = 256 - L_u8Offset;
			TCNT0 = G_u8Reg;
		}
	else
		{
			L_f32OverFlowCount = (copy_u32Delay_ms / (L_f32MaxCompare/1000.0));
			L_u32Carry = (copy_u32Delay_ms / (L_f32MaxCompare/1000));

			L_u8Offset = (L_f32OverFlowCount - L_u32Carry) * 256.0;
			G_u32Overflows = L_u32Carry +1 ;
			G_u8Reg = 256 - L_u8Offset;
			TCNT0 = G_u8Reg;
		}

		while (GET_BIT(TIFR, TOV0) == 0 && G_u8Check == 0);
}

void MTIMER_voidTimer0OVFSetCallBack ( void (*copy_PFvoidTimer0OVF) (void))
{
	TIMER_PFTIMER0OVF = copy_PFvoidTimer0OVF ;
}



void MTIMER_voidTimer0COMPInit(void)
{
	/*CHOOSE CTC MODE*/
		CLR_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);

		SET_BIT(TIMSK, OCIE0);

#if		CLK == ONE
		TCCR0 = (TCCR0 & 0xf8) | 0x01;
#elif 	CLK == EIGHT
		TCCR0 = (TCCR0 & 0xf8) | 0x02;
#elif 	CLK == SIXTYFOUR
		TCCR0 = (TCCR0 & 0xf8) | 0x03;
#elif 	CLK == TWOFIFTYSIX
		TCCR0 = (TCCR0 & 0xf8) | 0x04;
#elif 	CLK == TENTWENTYFOUR
		TCCR0 = (TCCR0 & 0xf8) | 0x05;
#elif 	CLK == EXTERN_FALLING
		TCCR0 = (TCCR0 & 0xf8) | 0x06;
#elif 	CLK == EXTERN_RISING
		TCCR0 = (TCCR0 & 0xf8) | 0x07;
#endif
}


void MTIMER_voidTimer0COMPDelay(u8 copy_u8Offset, u32 copy_u32Counts)
{
	G_u8Check = 0;
	G_u32Overflows = copy_u32Counts;
	if (copy_u32Counts == 1)
	{
		OCR0 = copy_u8Offset;
	}
	else if (copy_u32Counts > 1)
	{
		G_u8Reg = copy_u8Offset;
		OCR0 = 255;
	}
	MTIMER_voidTimer0COMPInit();
	while (GET_BIT(TIFR, OCF0) == 0  &&  G_u8Check == 0);
	//TCCR0 = 0;
}




void MTIMER_voidTimer0COMPSetCallBack ( void (*copy_PFvoidTimer0COMP) (void))
{
	TIMER_PFTIMER0COMP = copy_PFvoidTimer0COMP ;
}


ISR (TIMER0_OVF_vect)
{
	static u32 L_u32OVFCounter = 0 ;
	L_u32OVFCounter ++ ;
	if (L_u32OVFCounter == G_u32Overflows)
	{
		L_u32OVFCounter = 0 ;
		TCNT0 = G_u8Reg;
		if(TIMER_PFTIMER0OVF != NULL)
			TIMER_PFTIMER0OVF() ;
		G_u8Check = 1;
	}
}

ISR (TIMER0_COMP_vect)
{
	static u32 G_u32CompCounter = 0;
	G_u32CompCounter ++ ;
	if( G_u32Overflows ==  G_u32CompCounter)
	{
		if( TIMER_PFTIMER0COMP != NULL )
			TIMER_PFTIMER0COMP() ;
		G_u32CompCounter = 0 ;
		G_u8Check = 1;
	}
	else if(G_u32Overflows == G_u32CompCounter + 1)
	{
		OCR0 = G_u8Reg;
	}
	else if (G_u32Overflows != G_u32CompCounter)
	{
		OCR0 = 255;
	}

}


void MTIMER_voidTimer0FPWMInit()
{
	/*CHOOSE FPWM MODE*/
		SET_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);

		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);

		//SET_BIT(TIMSK, OCIE0);

#if		CLK == ONE
		TCCR0 = (TCCR0 & 0xf8) | 0x01;
#elif 	CLK == EIGHT
		TCCR0 = (TCCR0 & 0xf8) | 0x02;
#elif 	CLK == SIXTYFOUR
		TCCR0 = (TCCR0 & 0xf8) | 0x03;
#elif 	CLK == TWOFIFTYSIX
		TCCR0 = (TCCR0 & 0xf8) | 0x04;
#elif 	CLK == TENTWENTYFOUR
		TCCR0 = (TCCR0 & 0xf8) | 0x05;
#elif 	CLK == EXTERN_FALLING
		TCCR0 = (TCCR0 & 0xf8) | 0x06;
#elif 	CLK == EXTERN_RISING
		TCCR0 = (TCCR0 & 0xf8) | 0x07;
#endif
}

void MTIMER_voidTimer0FPWMWrite(u8 copy_u8Value)
{
	OCR0 = copy_u8Value;

}
/////////////////////////////////////////////////////////////////////////////////////////
void MTIMER_voidTimer1FPWM_ICR_INIT (void)
{
	/*CHOOSING FWPM W/ ICR*/

	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

	/* CLEAR OC1A */
	CLR_BIT(TCCR1A, COM1A0);
	SET_BIT(TCCR1A, COM1A1);

	/*FREQUENCY CONTROL*/
#if		CLK_ONE == ONE
		TCCR1B = (TCCR1B & 0xf8) | 0x01;
#elif 	CLK_ONE == EIGHT
		TCCR1B = (TCCR1B & 0xf8) | 0x02;
#elif 	CLK_ONE == SIXTYFOUR
		TCCR1B = (TCCR1B & 0xf8) | 0x03;
#elif 	CLK_ONE == TWOFIFTYSIX
		TCCR1B = (TCCR1B & 0xf8) | 0x04;
#elif 	CLK_ONE == TENTWENTYFOUR
		TCCR1B = (TCCR1B & 0xf8) | 0x05;
#elif 	CLK_ONE == EXTERN_FALLING
		TCCR1B = (TCCR1B & 0xf8) | 0x06;
#elif 	CLK_ONE == EXTERN_RISING
		TCCR1B = (TCCR1B & 0xf8) | 0x07;
#endif


	/* ICR1 */
	ICR1 = 19999;
	/*With ICR1 = 19999, and CLK_ONE = 8MHz,
	 * and Prescalar = 8 ,
	 *  frequency of PWM = 50 Hz.
	 * */

	/*N.B. Regarding FREQ and ICR1
	 * At mode 14, TIMER1 works in FPWM mode,
	 * with the value of ICR1 controlling
	 *the top value, hence, the frequency of PWM
	 * */
}


////////////////////////////////////////////////////////////////////////////////////////

void MTIMER_voidTimer2COMPInit(void)

{
	/*CHOOSE CTC MODE*/
		CLR_BIT(TCCR2, WGM20);
		SET_BIT(TCCR2, WGM21);

		SET_BIT(TIMSK, OCIE2);

#if		CLK == ONE
		TCCR2 = (TCCR2 & 0xf8) | 0x01;
#elif 	CLK == EIGHT
		TCCR2 = (TCCR2 & 0xf8) | 0x02;
#elif 	CLK == THRITYTWO
		TCCR2 = (TCCR2 & 0xf8) | 0x03;
#elif 	CLK == SIXTYFOUR
		TCCR2 |= (1<<2);
		//TCCR2 = (TCCR2 & 0xf8) | 0x04;
#elif 	CLK == ONETWENTYEIGHT
		TCCR2 = (TCCR2 & 0xf8) | 0x05;
#elif 	CLK == TWOFIFTYSIX
		TCCR2 = (TCCR2 & 0xf8) | 0x06;
#elif 	CLK == TENTWENTYFOUR
		TCCR2 = (TCCR2 & 0xf8) | 0x07;
#endif

}

void MTIMER_voidTimer2COMPDelay(u8 copy_u8Offset, u32 copy_u32Counts)
{
	G_u8Check = 0;
	G_u32Overflows = copy_u32Counts;
	if (copy_u32Counts == 1)
	{
		OCR2 = copy_u8Offset;
	}
	else if (copy_u32Counts > 1)
	{
		G_u8Reg = copy_u8Offset;
		OCR2 = 255;

	}
	MTIMER_voidTimer2COMPInit();
	while (GET_BIT(TIFR, OCF2) == 0  &&  G_u8Check == 0);
	}

void MTIMER_voidTimer2COMPSetCallBack ( void (*copy_PFvoidTimer2COMP) (void))
{
	TIMER_PFTIMER2COMP = copy_PFvoidTimer2COMP ;
}


void MTIMER_voidTimer2OVFInit(void)

{
	/*CHOOSE NORMAL MODE*/
		CLR_BIT(TCCR2, WGM20);
		CLR_BIT(TCCR2, WGM21);

		SET_BIT(TIMSK, TOIE2);

#if		CLK == ONE
		TCCR2 = (TCCR2 & 0xf8) | 0x01;
#elif 	CLK == EIGHT
		TCCR2 = (TCCR2 & 0xf8) | 0x02;
#elif 	CLK == THRITYTWO
		TCCR2 = (TCCR2 & 0xf8) | 0x03;
#elif 	CLK == SIXTYFOUR
		TCCR2 |= (1<<2);
		//TCCR2 = (TCCR2 & 0xf8) | 0x04;
#elif 	CLK == ONETWENTYEIGHT
		TCCR2 = (TCCR2 & 0xf8) | 0x05;
#elif 	CLK == TWOFIFTYSIX
		TCCR2 = (TCCR2 & 0xf8) | 0x06;
#elif 	CLK == TENTWENTYFOUR
		TCCR2 = (TCCR2 & 0xf8) | 0x07;
#endif

}

void MTIMER_voidTimer2OVFDelay(u32 copy_u32Delay_ms)
{
	f32 L_f32MaxCompare;
	f32 L_f32OverFlowCount;
	u32 L_u32Carry;
	u8 L_u8Offset;

	G_u8Check = 0;

	MTIMER_voidTimer2OVFInit();

#if		CLK == ONE
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256;
#elif 	CLK == EIGHT
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 8;
#elif 	CLK == THRITYTWO
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 32;
#elif 	CLK == SIXTYFOUR
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 64;
#elif 	CLK == ONETWENTYEIGHT
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 128;
#elif 	CLK == TWOFIFTYSIX
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 256;
#elif 	CLK == TENTWENTYFOUR
		L_f32MaxCompare = (1000000.0) / F_CPU;
		L_f32MaxCompare = L_f32MaxCompare * 256 * 1024;

#endif


	if (copy_u32Delay_ms * 1000  <= L_f32MaxCompare)
		{
			L_f32OverFlowCount = (copy_u32Delay_ms / (L_f32MaxCompare/1000.0));
			L_u8Offset = L_f32OverFlowCount * 256.0;
			G_u32Overflows = 1;
			G_u8Reg = 256 - L_u8Offset;
			TCNT2 = G_u8Reg;
		}
	else
	{
		L_f32OverFlowCount = (copy_u32Delay_ms / (L_f32MaxCompare/1000.0));
		L_u32Carry = (copy_u32Delay_ms / (L_f32MaxCompare/1000));

		L_u8Offset = (L_f32OverFlowCount - L_u32Carry) * 256.0;
		G_u32Overflows = L_u32Carry +1 ;
		G_u8Reg = 256 - L_u8Offset;
		TCNT2 = G_u8Reg;

	}

	while (GET_BIT(TIFR, TOV2) == 0 && G_u8Check == 0);
}

void MTIMER_voidTimer2OVFSetCallBack ( void (*copy_PFvoidTimer2OVF) (void))
{
	TIMER_PFTIMER2OVF = copy_PFvoidTimer2OVF ;
}


void MTIMER_voidTimer2FPWMInit()
{
	/*CHOOSE FPWM MODE*/
		SET_BIT(TCCR2, WGM20);
		SET_BIT(TCCR2, WGM21);

		CLR_BIT(TCCR2, COM20);
		SET_BIT(TCCR2, COM21);

#if		CLK == ONE
		TCCR2 = (TCCR2 & 0xf8) | 0x01;
#elif 	CLK == EIGHT
		TCCR2 = (TCCR2 & 0xf8) | 0x02;
#elif 	CLK == THRITYTWO
		TCCR2 = (TCCR2 & 0xf8) | 0x03;
#elif 	CLK == SIXTYFOUR
		TCCR2 |= (1<<2);
		//TCCR2 = (TCCR2 & 0xf8) | 0x04;
#elif 	CLK == ONETWENTYEIGHT
		TCCR2 = (TCCR2 & 0xf8) | 0x05;
#elif 	CLK == TWOFIFTYSIX
		TCCR2 = (TCCR2 & 0xf8) | 0x06;
#elif 	CLK == TENTWENTYFOUR
		TCCR2 = (TCCR2 & 0xf8) | 0x07;
#endif
}


void MTIMER_voidTimer2FPWMWrite(u8 copy_u8Value)
{
	OCR2 = copy_u8Value;
}




ISR (TIMER2_OVF_vect)
{
	static u32 L_u32OVFCounter = 0 ;
	L_u32OVFCounter ++ ;
	if (L_u32OVFCounter == G_u32Overflows)
	{
		L_u32OVFCounter = 0 ;
		TCNT2 = G_u8Reg;
		if ( TIMER_PFTIMER2OVF != NULL )
			TIMER_PFTIMER2OVF() ;
		G_u8Check = 1;
	}
}


ISR (TIMER2_COMP_vect)
{
	static u32 G_u32CompCounter = 0;
	G_u32CompCounter ++ ;
	if( G_u32CompCounter == G_u32Overflows )
	{
		if(TIMER_PFTIMER2COMP != NULL)
			TIMER_PFTIMER2COMP() ;
		G_u32CompCounter = 0 ;
		G_u8Check = 1;
	}
	else if(G_u32CompCounter == G_u32Overflows - 1)
	{
		OCR2 = G_u8Reg;
	}
	else if (G_u32CompCounter != G_u32Overflows)
	{
		OCR2 = 255;
	}

}

