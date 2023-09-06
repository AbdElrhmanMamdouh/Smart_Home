#ifndef TIME_INTERFACE_H
#define TIME_INTERFACE_H
///////////////////////////////
/********CLK SELECT***********/

#define ONE				0
#define EIGHT			1
#define SIXTYFOUR		2
#define TWOFIFTYSIX		3
#define TENTWENTYFOUR	4
//FOR TIMER TWO
#define THRITYTWO		5
#define	ONETWENTYEIGHT	6

//FOR TIMER ONE
#define EXTERN_FALLING 	7
#define EXTERN_RISING	8
/*
 * SELECT CLK
 *ONE
 *EIGHT
 *THIRTYTWO
 *SIXTYFOUR
 *ONETWENTYEIGHT
 *TWOFIFTYSIX
 *TENTWENTYFOUR
 */

#define CLK TWOFIFTYSIX

/*TIMER0*/

void MTIMER_voidTimer0OVFInit(void);

void MTIMER_voidTimer0OVFDelay(u32 copy_u32Delay_ms);

void MTIMER_voidTimer0OVFSetCallBack ( void (*copy_PFvoidTimer0OVF) (void));


void MTIMER_voidTimer0COMPInit(void);

void MTIMER_voidTimer0COMPDelay(u8 copy_u8Offset, u32 copy_u32Counts);

void MTIMER_voidTimer0COMPSetCallBack ( void (*copy_PFvoidTimer0COMP) (void));


void MTIMER_voidTimer0FPWMInit();
void MTIMER_voidTimer0FPWMWrite(u8 copy_u8Value);






/////////////////////////////////////////
/*TIMER1*/

void MTIMER_voidTimer1OVFInit(void);

void MTIMER_voidTimer1COMPInit(void);

void MTIMER_voidTimer1FPWM_ICR_INIT (void);








//////////////////////////////////////
/*TIMER2*/

void MTIMER_voidTimer2OVFInit(void);

void MTIMER_voidTimer2OVFDelay(u32 copy_u32Delay_ms);

void MTIMER_voidTimer2OVFSetCallBack ( void (*copy_PFvoidTimer2OVF) (void));




void MTIMER_voidTimer2COMPInit(void);

void MTIMER_voidTimer2COMPDelay(u8 copy_u8Offset, u32 copy_u32Counts);

void MTIMER_voidTimer2COMPSetCallBack ( void (*copy_PFvoidTimer2COMP) (void));


void MTIMER_voidTimer2FPWMInit();

void MTIMER_voidTimer2FPWMWrite(u8 copy_u8Value);

#endif
