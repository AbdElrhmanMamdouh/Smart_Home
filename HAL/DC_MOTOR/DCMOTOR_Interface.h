#ifndef DCMOTOR_INTERFACE_H
#define DCMOTOR_INTERFACE_H


#define DCMOTOR_PORT      DIO_PORTD
#define DCMOTOR_PIN1      DIO_PIN6
#define DCMOTOR_PIN2      DIO_PIN7

void DCMOTOR_voidInit(void);
void DCMOTOR_voidRotateCW(void);
void DCMOTOR_voidRotateCCW(void);
void DCMOTOR_voidStop(void);

#endif
