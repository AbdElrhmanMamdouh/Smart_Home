/**********/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <avr/interrupt.h>
#include "EXIT_Interface.h"

#define NULL ((void *)0)
static void (*EXTI_pf_EXTI[3])(void) = {NULL, NULL, NULL};

void EXTI_voidInit(void)
{
#if EXTI_INDEX_0 == INT0
	SET_BIT(GICR, GICR_INT0);
//CHOOSE CLOCK
#if EXTI_CLOCK_0 == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_CLOCK_0 == ANY_LOGICAL
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_CLOCK_0 == FALLING
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_CLOCK_0 == RAISING
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#endif
#endif

#if EXIT_INDEX_1== INT1
	SET_BIT(GICR, GICR_INT1);
//CHOOSE CLOCK
#if EXTI_CLOCK_1 == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_CLOCK_1 == ANY_LOGICAL
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_CLOCK_1 == FALLING
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_CLOCK_1 == RAISING
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#endif
#endif

#if EXTI_INDEX_2 == INT2
	SET_BIT(GICR, GICR_INT2);
#if EXTI_CLOCK_2 == FALLING
	CLR_BIT(MCUCSR, MCUCSR_ISC2);
#elif EXTI_CLOCK_2 == RAISING
	SET_BIT(MCUCSR, MCUCSR_ISC2);
#endif
#endif
}


void EXTI_voidGIE(void)
{
#if GIE == ENABLE
	SET_BIT(SREG, SREG_PIN);
#elif GIE == DISABLE
	CLR_BIT(SREG, SREG_PIN);
#endif
}

void EXTI_voidEXTISetCallBack(u8 copy_u8EXTIIndex, void (*copy_pf)(void))
{
	EXTI_pf_EXTI[copy_u8EXTIIndex] = copy_pf;
}

ISR(INT0_vect)
{
	if ( EXTI_pf_EXTI[0] != NULL )
	{
		EXTI_pf_EXTI[0]();
	}
}

ISR(INT1_vect)
{
	if ( EXTI_pf_EXTI[1] != NULL )
	{
		EXTI_pf_EXTI[1]();
	}
}

ISR(INT2_vect)
{
	if ( EXTI_pf_EXTI[2] != NULL )
	{
		EXTI_pf_EXTI[2]();
	}
}
