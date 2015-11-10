#include "Globals.h"
#include "Display.h"
#include "Convert.h"
#include "stm32f4xx_gpio.h"



void successState() { 
	GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_SetBits(GPIOD, GPIO_Pin_12); //GREEN LED
	prevState = State;
	State = SUCCESS_STATE;
}

void failState(int failType, int numGuesses) { 
	GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
	if (numGuesses > 2) {
		prevState = State;
		State = FAIL_STATE;
	}
	else if (failType == 2) 
		GPIO_SetBits(GPIOD, GPIO_Pin_14); //RED LED
	else 
		GPIO_SetBits(GPIOD, GPIO_Pin_15); //BLUE LED

}


void resetState(int *guess, int * nGuess, int * guessResult, int * i) {
	guess[0] = 0;
	guess[1] = 0;
	guess[2] = 0;
	*nGuess = 0; 
	*guessResult = 0;
	*i = 0;
	display_init(); //resets display

}
