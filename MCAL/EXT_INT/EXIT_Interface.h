
#ifndef MCAL_EXT_INT_EXIT_INTERFACE_H_
#define MCAL_EXT_INT_EXIT_INTERFACE_H_

#define LOW_LEVEL 	0
#define ANY_LOGICAL 1
#define FALLING 	2
#define RAISING 	3

/*MCUCR BITS*/
#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3

/*MCUCSR BIT*/

#define MCUCSR_ISC2 6

/*GICR BITS*/
#define GICR_INT0	6
#define GICR_INT1	7
#define GICR_INT2	5

/*SREG_BIT*/
#define SREG_PIN	7

#define ENABLE		0
#define DISABLE		1

/*
 * SELECT INT_INDEX:
 * INT0
 * INT1
 * INT2
 */

#define EXTI_INDEX_0 INT0
#define EXIT_INDEX_1 INT1
//#define EXTI_INDEX_2 INT2

/*
 * SELECT INT_CLK FOR INT0, INT1:
 * LOW_LEVEL
 * ANY_LOGICAL
 * FALLING
 * RAISING
 * NONE
 */
#define EXTI_CLOCK_0	ANY_LOGICAL
#define EXTI_CLOCK_1	ANY_LOGICAL

/*
 * SELECT INT_CLK FOR INT2:
 * FALLING
 * RAISING
 * NONE
 */
#define EXTI_CLOCK_2	NONE


/*
 * SELECT ENABLE/DISABLE
 */

#define GIE 	ENABLE
/*******************************/
/*FUNCTIONS*/
void EXTI_voidInit(void);
void EXTI_voidGIE(void);
void EXTI_voidEXTISetCallBack(u8 copy_u8EXTIIndex, void (*copy_pf)(void));

#endif /* MCAL_EXT_INT_EXIT_INTERFACE_H_ */
