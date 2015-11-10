#include "Initialize_Interrupts.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
void Initialize_Interrupts(){
	Initialize_Accelerometer_Int1();
	Initialize_Keypad_Column_Interrupts();
	//Initialize_ADC_Interrupt();
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

void Initialize_Keypad_Column_Interrupts(){
	
	Initialize_Column_1_Interrupt();
	Initialize_Column_2_Interrupt();
	Initialize_Column_3_Interrupt();
	Initialize_Column_4_Interrupt();

	
}

void Initialize_Column_1_Interrupt() {
	
	EXTI_InitTypeDef EXTI_Initialize;
	NVIC_InitTypeDef NVIC_Initialize;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	EXTI_Initialize.EXTI_LineCmd = ENABLE;
	EXTI_Initialize.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initialize.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_Initialize.EXTI_Line = EXTI_Line2; 
	
	NVIC_Initialize.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Initialize.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initialize.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_Initialize.NVIC_IRQChannelSubPriority = 0x00;
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2);

	EXTI_Init(&EXTI_Initialize);
	NVIC_Init(&NVIC_Initialize);

}

void Initialize_Column_2_Interrupt() {

	EXTI_InitTypeDef EXTI_Initialize;
	NVIC_InitTypeDef NVIC_Initialize;

	
	EXTI_Initialize.EXTI_LineCmd = ENABLE;
	EXTI_Initialize.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initialize.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_Initialize.EXTI_Line = EXTI_Line3; 
	
	NVIC_Initialize.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Initialize.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initialize.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_Initialize.NVIC_IRQChannelSubPriority = 0x00;
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource3);

	EXTI_Init(&EXTI_Initialize);
	NVIC_Init(&NVIC_Initialize);
	
}

void Initialize_Column_3_Interrupt() {

	EXTI_InitTypeDef EXTI_Initialize;
	NVIC_InitTypeDef NVIC_Initialize;

	EXTI_Initialize.EXTI_LineCmd = ENABLE;
	EXTI_Initialize.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initialize.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_Initialize.EXTI_Line = EXTI_Line4; 
	
	NVIC_Initialize.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Initialize.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initialize.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_Initialize.NVIC_IRQChannelSubPriority = 0x00;
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource4);

	EXTI_Init(&EXTI_Initialize);
	NVIC_Init(&NVIC_Initialize);
	
}

void Initialize_Column_4_Interrupt() {

	EXTI_InitTypeDef EXTI_Initialize;
	NVIC_InitTypeDef NVIC_Initialize;

	EXTI_Initialize.EXTI_LineCmd = ENABLE;
	EXTI_Initialize.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initialize.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_Initialize.EXTI_Line = EXTI_Line5; 
	
	NVIC_Initialize.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Initialize.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initialize.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_Initialize.NVIC_IRQChannelSubPriority = 0x00;
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource5);

	EXTI_Init(&EXTI_Initialize);
	NVIC_Init(&NVIC_Initialize);
	
	
}


/*
void Initialize_ADC_Interrupt() {

  NVIC_SetPriority(ADC_IRQn, 0x01);
  NVIC_EnableIRQ(ADC_IRQn);

	
}
	
	


*/
/*
void ADC_IRQHandler() {
	

	if (ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET)
	{	  
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		osSignalSet(TemperatureSensor_thread, 0x00000010);



	}

	
}*/


void  EXTI0_IRQHandler() {

		if (EXTI_GetITStatus(EXTI_Line0) != RESET) {

			osSignalSet(Accelerometer_thread, 0x10);
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
}


void  EXTI2_IRQHandler() {

		if (EXTI_GetITStatus(EXTI_Line2) != RESET) {

			//reset interrupt 
			EXTI_ClearITPendingBit(EXTI_Line2);
			
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == Bit_RESET) {
				
				osSignalSet(Keypad_thread, 0x00000011);
//				debug_b = 1;

			}

  }

}


void EXTI3_IRQHandler() {
		if (EXTI_GetITStatus(EXTI_Line3) != RESET) {

			//reset interrupt 
			EXTI_ClearITPendingBit(EXTI_Line3);
			
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == Bit_RESET) {

				osSignalSet(Keypad_thread, 0x00000101);
				//debug_b = 2;

			}
		}	
	
}

void EXTI4_IRQHandler() {
		if (EXTI_GetITStatus(EXTI_Line4) != RESET) {

			//reset interrupt 
			EXTI_ClearITPendingBit(EXTI_Line4);
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == Bit_RESET) {

				osSignalSet(Keypad_thread, 0x00000111);
				//debug_b = 3;


			}
		}	
	
}

void EXTI9_5_IRQHandler() {
		if (EXTI_GetITStatus(EXTI_Line5) != RESET) {

			//reset interrupt 
			EXTI_ClearITPendingBit(EXTI_Line5);
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == Bit_RESET) {

				osSignalSet(Keypad_thread, 0x00001001);
				//debug_b = 4;

			}
		}	
	
}

