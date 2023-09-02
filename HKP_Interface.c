//LIB Layer
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>
//MCAL
#include "DIO_interface.h"
//HAL
#include "HKP_interface.h"

u8 Row[4] = {HKP_R1_PIN, HKP_R2_PIN, HKP_R3_PIN, HKP_R4_PIN};
u8 Col[4] = {HKP_C1_PIN, HKP_C2_PIN, HKP_C3_PIN, HKP_C4_PIN};
u8 Keys[4][4] = HKP_KEYS;

void HKP_voidInit(void){
	DIO_voidSetPortDirection(HKP_PORT,0b00001111);
	DIO_voidSetPortValue(HKP_PORT,HKP_KEY_NOT_PRESSED);
}

u8 HKP_u8GetKeyValue(void) {
    u8 Local_u8RowsCounter, Local_u8ColsCounter;

    for (Local_u8RowsCounter = 0; Local_u8RowsCounter < 4; Local_u8RowsCounter++) {  // Change condition to < instead of <=

        DIO_voidSetPinValue(HKP_PORT, Row[Local_u8RowsCounter], DIO_LOW);

        for (Local_u8ColsCounter = 0; Local_u8ColsCounter < 4; Local_u8ColsCounter++) {  // Change condition to < instead of <=
            if (DIO_u8GetPinValue(HKP_PORT, Col[Local_u8ColsCounter]) == 0) {
                _delay_ms(20);
                while (DIO_u8GetPinValue(HKP_PORT, Col[Local_u8ColsCounter]) == 0) {
                    /*Do Nothing*/
                }
                return Keys[Local_u8RowsCounter][Local_u8ColsCounter];
            }
        }
        DIO_voidSetPinValue(HKP_PORT, Row[Local_u8RowsCounter], DIO_HIGH);
    }
    return HKP_KEY_NOT_PRESSED;
}

