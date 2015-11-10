#include "Convert.h"
#include "Math.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif

uint8_t Covert_to_Array(uint8_t * guess, float value) {
	int nTemp;
	int posPeriod = -1; 
	
	if (value < 10) {
		nTemp = (int) (value * 100);
		posPeriod = 3;
	} else if (value < 100) {
		nTemp = (int) (value * 10);
		posPeriod = 2;
	} else
		nTemp = (int) value;

	guess[0] = nTemp % 10; 
	guess[1] = (nTemp % 100 - guess[0]) / 10;
	guess[2] = (nTemp - guess[1]) / 100; 
			
	return posPeriod;
}

int Covert_to_Decimal(int * guess, int i) {
	
		int nGuess = 0; 
	for (int j = 0; j < i; j++)
		nGuess += guess[j]*pow(10,j);
	return nGuess; 
			
}

