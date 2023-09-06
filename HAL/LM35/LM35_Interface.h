#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H




// The Number OF LM35 Sensors To Be Used In The Project

#define LM35_CHANNEL_ID         CHANNEL_2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

#define TARGET_LM		7



u8 LM35_TempSensor_u8ReadTemp(void);

#endif
