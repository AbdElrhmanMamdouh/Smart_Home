#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H


#include "..//LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

// The Number OF LM35 Sensors To Be Used In The Project

#define LM35_CHANNEL_ID         channel_0
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150


u8 LM35_TempSensor_u8ReadTemp(void);

#endif
