#ifndef DCMOTOR_INTERFACE_H
#define DCMOTOR_INTERFACE_H


#define DCMOTOR_PORT      DIO_PORTB
#define DCMOTOR_PIN1      DIO_PIN0
#define DCMOTOR_PIN2      DIO_PIN1

void DCMOTOR_voidInit(void);
void DCMOTOR_voidRotateCW(void);
void DCMOTOR_voidRotateCCW(void);
void DCMOTOR_voidStop(void);

#endif
