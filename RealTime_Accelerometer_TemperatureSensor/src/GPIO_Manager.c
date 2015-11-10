#include "GPIO_Manager.h"
#include "stm32f4xx_gpio.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif


void Initialize_GPIO() {
	
	Initialize_Accelerometer_Interrupt_GPIO();
	Initialize_Seven_Segment_GPIO();
	Initialize_LEDS_GPIO();
	Initialize_Keypad_readColumn_GPIO();
	
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

void Initialize_Seven_Segment_GPIO() {
	
	Initialize_Segments_GPIO();
	Initialize_DigitSelect_GPIO();
	
} 

void Initialize_Segments_GPIO() {
	GPIO_InitTypeDef GPIO_InitDef; 
		
	GPIO_StructInit(&GPIO_InitDef);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOB, &GPIO_InitDef);

}

void Initialize_DigitSelect_GPIO() {
	GPIO_InitTypeDef GPIO_InitDef; 

	GPIO_StructInit(&GPIO_InitDef);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOD, &GPIO_InitDef);

	
}


void Initialize_LEDS_GPIO() {
	GPIO_InitTypeDef GPIO_InitDef; 


	GPIO_StructInit(&GPIO_InitDef);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOD, &GPIO_InitDef);

	
}


void Initialize_Keypad_readColumn_GPIO() {
	GPIO_InitTypeDef GPIO_InitDef; 

	GPIO_StructInit(&GPIO_InitDef);
	
	//columns
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 ;
	
  GPIO_Init(GPIOC, &GPIO_InitDef);

	
	
	//rows
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8; 
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;

  GPIO_Init(GPIOA, &GPIO_InitDef);
	
	//set row bits low
	GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8);

}

void Initialize_Keypad_readRow_GPIO() {
	GPIO_InitTypeDef GPIO_InitDef; 
	
	GPIO_StructInit(&GPIO_InitDef);
	
	//columns
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 ;
	
  GPIO_Init(GPIOC, &GPIO_InitDef);

	
	
	//rows
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8; 
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;

  GPIO_Init(GPIOA, &GPIO_InitDef);
	
	//set column bits low
	GPIO_ResetBits(GPIOC, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);

}
