#include "ADC_TemperatureSensor_Data.h"
#include "Filter_Data.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif

buffer Temperature_Filter;


void Initialize_Temperature_Filter() {
	Initialize_Filters(&Temperature_Filter);

	
}

void updateADC_Temperature(float * temp) {

	readADC_Temperature(temp);
	convert_ADC_to_TemperatureCelcius(temp);
	moving_filter(&Temperature_Filter, temp);
	
}

void readADC_Temperature(float * temp) {
		ADC_SoftwareStartConv(ADC1);
	
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET){};

		*temp = ADC_GetConversionValue(ADC1); 

}

		
void convert_ADC_to_TemperatureCelcius(float * temp) {
		
	//Temperature (in °C) = {(VSENSE – V25) / Avg_Slope} + 25
	*temp = ((*temp*(3.0f / 4096.0f) - 0.76)/0.0025) + 25;
	
}
