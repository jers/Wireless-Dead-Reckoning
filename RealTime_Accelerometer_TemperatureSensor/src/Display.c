#include "Display.h"
#include "stm32f4xx_gpio.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif

int seg = 0;


void display_init() {
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8);//7 segment
	GPIO_SetBits(GPIOD, GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7); //sections 1 , 2 , 3 and degrees 

	
}


void display(uint8_t digits [3], uint8_t i, uint8_t posPeriod) {
	//multiplex to pins
	
	display_init();
	
	switch(seg) {
		case 0:
			GPIO_ResetBits(GPIOD, GPIO_Pin_7);//degrees symbol
			break;
		case 1:
			GPIO_ResetBits(GPIOD, GPIO_Pin_6);//section 3
			break;
		case 2:
			GPIO_ResetBits(GPIOD, GPIO_Pin_5);//section 2
			break;		
		case 3:
			GPIO_ResetBits(GPIOD, GPIO_Pin_1);//section 1
			break;
	}
	if (posPeriod == seg)
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
	switch(digits[seg-1]) {
		case 0:
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6); //0
			break;
		case 1:
			GPIO_SetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6); //1
			break;
		case 2:
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7); //2
			break;
		case 3:
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7); //3
			break;
		case 4:
			GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7); //4
			break;
		case 5:
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7); //5
			break;
		case 6:
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_6 | GPIO_Pin_7); //6
			break;
		case 7:
			GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4); //7
			break;
		case 8:
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7); //8
			break;
		case 9:
			GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7); //9
			break;
					
	}
	GPIO_SetBits(GPIOD, GPIO_Pin_0); // degrees 
	
	seg = (seg + 1) % (1 + i);
}

void display_empty() {
	display_init(); 
	
}


void display_error() {
	
	display_init();
	GPIO_ResetBits(GPIOD, GPIO_Pin_0);  // not covered by init function
	
	switch(seg) {
		case 0:
			GPIO_ResetBits(GPIOD, GPIO_Pin_1);//section 1
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8); //E
			break;
		case 1:
			GPIO_ResetBits(GPIOD, GPIO_Pin_5);//section 2
			GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8); //R
			break;
		case 2:
			GPIO_ResetBits(GPIOD, GPIO_Pin_6);//section 3
			GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8); //R
			break;		
	}
	
	
	
		seg = (seg + 1) % 3;
	
}

void display_Failure() {
	display_init();
	GPIO_ResetBits(GPIOD, GPIO_Pin_0);  // not covered by init function
	switch(seg) {
		case 0:
			GPIO_ResetBits(GPIOD, GPIO_Pin_1);//section 1
			GPIO_SetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7); //F
			break;
		case 1:
			GPIO_ResetBits(GPIOD, GPIO_Pin_5);//section 2
			GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);//A
			break;
		case 2:
			GPIO_ResetBits(GPIOD, GPIO_Pin_6);//section 3
			GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_6);//I
			break;		
	}
	seg = (seg + 1) % 3;

}

void display_Success() {
	display_init();
	GPIO_ResetBits(GPIOD, GPIO_Pin_0);  // not covered by init function
	switch(seg) {
		case 0:
			GPIO_ResetBits(GPIOD, GPIO_Pin_1);//section 1
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7); ///S
			break;
		case 1:
			GPIO_ResetBits(GPIOD, GPIO_Pin_5);//section 2
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6); //U
			break;
		case 2:
			GPIO_ResetBits(GPIOD, GPIO_Pin_6);//section 3
			GPIO_SetBits(GPIOB, GPIO_Pin_0  | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6); //C
			break;		
	}
	seg = (seg + 1) % 3;


	
}
