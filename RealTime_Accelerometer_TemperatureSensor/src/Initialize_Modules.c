#include "Initialize_Modules.h"
#include "Accelerometer_Data.h"
#include "ADC_TemperatureSensor_Data.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
int debug_a;
float debug_b, debug_c;
float debug_d [3];


void Initialize_Modules() {
	
	Initialize_Accelerometer();
	Initialize_ADC();
	Initialize_Globals();
	Initialize_Accelerometer_movingFilters();
	Initialize_Temperature_Filter();
	
}

void Initialize_Globals() {

		debug_a = 0;
		debug_b = debug_c = 0;
		debug_d[0] = debug_d[1] = debug_d[2] = 0;

}


void Initialize_Accelerometer() {
	
	LIS3DSH_InitTypeDef LIS3DSH_Initialize;
	LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_DRYInterruptConfig;
	
	
	LIS3DSH_Initialize.Power_Mode_Output_DataRate = LIS3DSH_DATARATE_100; //reasonable data rate 
	LIS3DSH_Initialize.Axes_Enable = LIS3DSH_X_ENABLE|LIS3DSH_Y_ENABLE|LIS3DSH_Z_ENABLE; 
	LIS3DSH_Initialize.Continous_Update = LIS3DSH_ContinousUpdate_Disabled;
	LIS3DSH_Initialize.Full_Scale = LIS3DSH_FULLSCALE_2;
	LIS3DSH_Initialize.Self_Test = LIS3DSH_SELFTEST_NORMAL;
	LIS3DSH_Initialize.AA_Filter_BW = LIS3DSH_AA_BW_50;
	
	LIS3DSH_DRYInterruptConfig.Dataready_Interrupt = LIS3DSH_DATA_READY_INTERRUPT_ENABLED; 
	LIS3DSH_DRYInterruptConfig.Interrupt_signal = LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL; 
	LIS3DSH_DRYInterruptConfig.Interrupt_type = LIS3DSH_INTERRUPT_REQUEST_PULSED; 
		
	LIS3DSH_Init(&LIS3DSH_Initialize); 
	LIS3DSH_DataReadyInterruptConfig(&LIS3DSH_DRYInterruptConfig);

	
}


void Initialize_ADC() {
	
	
	/*
	Code used from ECSE 426 Lecture Notes
	Mark Coates 
	
	*/
	
	 //set default values into the ADC init struct;
	ADC_InitTypeDef adc_init_s; 
	ADC_CommonInitTypeDef adc_common_init_s;  
	ADC_DeInit();  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // load the clock to power the ADC (1) via the APB2 bus
	
	
	//initialize ADC common struct values 
	adc_common_init_s.ADC_Mode = ADC_Mode_Independent; 
	adc_common_init_s.ADC_Prescaler = ADC_Prescaler_Div2; 
	adc_common_init_s.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 
	adc_common_init_s.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; 
	ADC_CommonInit(&adc_common_init_s);
	
	//initialize ADC values
	adc_init_s.ADC_Resolution = ADC_Resolution_12b; 
	adc_init_s.ADC_ScanConvMode = DISABLE; 
	adc_init_s.ADC_ContinuousConvMode = DISABLE;
	adc_init_s.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; 
	adc_init_s.ADC_DataAlign = ADC_DataAlign_Right; 
	adc_init_s.ADC_NbrOfConversion = 1; 
	
	//enable temperature sensor 
	ADC_TempSensorVrefintCmd(ENABLE); 
	ADC_Cmd(ADC1, ENABLE); 
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_480Cycles); 
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	ADC_Init(ADC1, &adc_init_s); 
	
	
}
