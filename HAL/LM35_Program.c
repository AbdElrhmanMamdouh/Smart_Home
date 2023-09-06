/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 * by: Fady Maher
 * created: 5/9/2023
 */
#include "..//LIB/STD_TYPES.h"
#include "..//LIB/BIT_MATH.h"
#include "LM35_Interface.h"
#include "../MCAL/ADC.h"
#include "../HAL/LCD_Interface.h"


u8 LM35_TempSensor_u8ReadTemp(void)
{
// initialize the ADC
	ADC_voidInit();
//	Declare the value of tempreture value & ADC Value
	u8 temp_value = 0;
	u16 adc_value;

	/*
     *  get the digital value of the sensor Analog reading
	 *  that sensor on channel 0
 	 */
	adc_value = ADC_u16GetDigitalValue(LM35_CHANNEL_ID);

	/* temp_value is declared as a variable of type u8, which typically represents an 8-bit unsigned integer. This variable will store the result of the temperature calculation.

     * adc_value is assumed to be a variable representing the raw ADC reading, and it's cast to an u32 (32-bit unsigned integer) to ensure the calculations are performed with sufficient precision.

	 * SENSOR_MAX_TEMPERATURE is representing the maximum temperature that the sensor can measure.

     * ADC_REF_VOLT_VALUE is representing the reference voltage of the ADC, which is used to convert the ADC reading to a voltage value.

     * ADC_MAXIMUM_VALUE is representing the maximum possible value that the ADC can return.

     * SENSOR_MAX_VOLT_VALUE is representing the maximum voltage value that the sensor can produce.

 *     "adc_value * SENSOR_MAX_TEMPERATURE" This operation is done to scale the ADC reading to the temperature range.

 *	   " * ADC_REF_VOLT_VALUE"  This operation converts the scaled ADC reading into a voltage value.

 *	   "ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE"   This step scales the voltage value down to a fractional value between 0 and 1, representing the relative position within the full range.

 *      the entire result is cast back to u8, which truncates the fractional part of the value and keeps only the integer part.
 */
	temp_value = (u8)(((u32) adc_value * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));
//	temp_value = adc_value * 0.25;
	return temp_value;
}


