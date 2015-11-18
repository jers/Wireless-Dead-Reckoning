#include "GPIO_Manager.h"
#include "stm32f4xx_gpio.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif


void Initialize_GPIO() {
	
	Initialize_Accelerometer_Interrupt_GPIO();
	
}

void Initialize_Accelerometer_Interrupt_GPIO() {
	GPIO_InitTypeDef GPIO_InitDef; 

	GPIO_StructInit(&GPIO_InitDef);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // Enable clock for GPIOE

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE, &GPIO_InitDef);
	
}
