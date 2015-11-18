#include "Initialize_Interrupts.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
void Initialize_Interrupts(){
	Initialize_Accelerometer_Int1();
}


//Accelerometer INT1 interrupt line initialization
void Initialize_Accelerometer_Int1(){

	EXTI_InitTypeDef EXTI_Initialize;
	NVIC_InitTypeDef NVIC_Initialize;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	EXTI_Initialize.EXTI_LineCmd = ENABLE;
	EXTI_Initialize.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initialize.EXTI_Trigger = EXTI_Trigger_Rising; 
	EXTI_Initialize.EXTI_Line = EXTI_Line0; 

	NVIC_Initialize.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initialize.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_Initialize.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Initialize.NVIC_IRQChannel = EXTI0_IRQn;

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);

	EXTI_Init(&EXTI_Initialize);
	NVIC_Init(&NVIC_Initialize); 

}



void  EXTI0_IRQHandler() {

		if (EXTI_GetITStatus(EXTI_Line0) != RESET) {

			osSignalSet(Accelerometer_thread, 0x10);
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
}



