#ifndef LDR_H_
#define LDR_H_

#include "../LIB/STD_TYPES.h"
#include "../MCAL/ADC.h"

#define SENSOR_CHANNEL_ID         channel_1
#define SENSOR_MAX_VOLT_VALUE     5
#define SENSOR_MAX_INTENSITY    1000



u16 LDR_readint(void);

//void LDR_check();

#endif /* LDR_H_ */
