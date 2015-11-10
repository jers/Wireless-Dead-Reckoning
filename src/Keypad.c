#include "Keypad.h"
#include "GPIO_Manager.h"
#include "stm32f4xx_gpio.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif




int readKeypad(uint8_t col) {
	
	int number; 
	
  for(int i = 0; i < 10; i++); //debouncing delay; 
	
	 
	int row = getRow();

//	debug_b = row; 
	if (row == -1)//incorrect keypad read
		return 0;
	switch (row) {
		
		case 1: number = col;
			break;
		case 2: number = col + 3;
			break;
		case 3: number = col + 6;
			break;
		case 4: number = (col + 9);
			break;
	}
	
//	debug_c = number;

	return number; 

		
}

int getColumn() {
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == Bit_RESET)
		return 1;
	else if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == Bit_RESET)
		return 2;
	else if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == Bit_RESET)
		return 3;
	else if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == Bit_RESET)
		return 4;
	else 
		return -1; 
}

int getRow() {
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == Bit_RESET)
		return 1;
	else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == Bit_RESET)
		return 2;
	else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == Bit_RESET)
		return 3;
	else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == Bit_RESET)
		return 4;
	else 
		return -1; 
}


int getKeypadNumber(uint8_t * State, uint8_t Column) {
	
	int number = 0; 
	int tries = 0; 
	osMutexWait(GPIO_Keypad_Mutex, osWaitForever);
	Initialize_Keypad_readRow_GPIO();
	osMutexRelease(GPIO_Keypad_Mutex);

	while(number == 0 && tries < 10) {
		number = readKeypad(Column);
		tries++;
	}

	
	osMutexWait(GPIO_Keypad_Mutex, osWaitForever);
	Initialize_Keypad_readColumn_GPIO();
	osMutexRelease(GPIO_Keypad_Mutex);

	
	
	if (number == 11)
		*State = RESET_STATE; 
	else if (number == 10)
		*State = SWITCH_ANGLE_STATE;
	else if (number == 12) 
		*State =SWITCH_STATE;
	else 
		return 0;
	
	return 1; 


	
	
}
