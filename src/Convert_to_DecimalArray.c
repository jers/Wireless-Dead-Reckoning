#include "Convert_to_DecimalArray.h"


int Covert(int * guess, float value) {
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