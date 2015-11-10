#include "Initialize_Timers.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
void Initialize_Timers() {
	Initialize_Timer_3();
	Initialize_Timer_4();
}


void Initialize_Timer_3() { 
	
		NVIC_InitTypeDef NVIC_Initialize;
		NVIC_Initialize.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Initialize.NVIC_IRQChannelPreemptionPriority = 0x03;
		NVIC_Initialize.NVIC_IRQChannelSubPriority = 0x01;
		NVIC_Initialize.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_Init(&NVIC_Initialize);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
		TIM_TimeBaseInitTypeDef TIM_Initialize; 
		TIM_Initialize.TIM_Prescaler = 84 - 1;
		TIM_Initialize.TIM_Period = (1000) * 20  -1;//1000 - 1; 50 hz
		TIM_Initialize.TIM_ClockDivision = 0;
		TIM_Initialize.TIM_CounterMode = TIM_CounterMode_Up;
	
		TIM_TimeBaseInit(TIM3, &TIM_Initialize); 

		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
		TIM_Cmd(TIM3, ENABLE);

}

void Initialize_Timer_4() { 
	
		NVIC_InitTypeDef NVIC_Initialize;
		NVIC_Initialize.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Initialize.NVIC_IRQChannelPreemptionPriority = 0x01;
		NVIC_Initialize.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_Initialize.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_Init(&NVIC_Initialize);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
		TIM_TimeBaseInitTypeDef TIM_Initialize; 
		TIM_Initialize.TIM_Prescaler = 84 - 1;
		TIM_Initialize.TIM_Period = (1000) -1;//1000 - 1; 1khz hz
		TIM_Initialize.TIM_ClockDivision = 0;
		TIM_Initialize.TIM_CounterMode = TIM_CounterMode_Up;
	
		TIM_TimeBaseInit(TIM4, &TIM_Initialize); 

		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
		TIM_Cmd(TIM4, ENABLE);

}




void TIM3_IRQHandler() {
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		osSignalSet(TemperatureSensor_thread, 0x10);

	}

}

void TIM4_IRQHandler() {
	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		osSignalSet(Display_thread, 0x10);

	}

}

	
