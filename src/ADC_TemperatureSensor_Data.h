#include "stm32f4xx_rcc.h"

void Initialize_Temperature_Filter(void);
void updateADC_Temperature(float * temp);
void readADC_Temperature(float * temp);
void convert_ADC_to_TemperatureCelcius(float * temp);
