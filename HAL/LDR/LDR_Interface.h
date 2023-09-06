#ifndef LDR_H_
#define LDR_H_



#define SENSOR_CHANNEL_ID         CHANNEL_3
#define SENSOR_MAX_VOLT_VALUE     3
#define SENSOR_MAX_INTENSITY    1000

#define TARGET_LDR		8



u16 LDR_readint(void);

//void LDR_check();

#endif /* LDR_H_ */
