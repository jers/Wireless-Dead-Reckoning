#include "Guess.h"
#include "Globals.h"

int testGuess(int nGuess) {
	int roundPitch = (int) Pitch; 
	int range = roundPitch - nGuess; 
	
	
	if (range > 4)
		return 2;
	else if (range < -4)
		return 3;
	
	return 1;
	
	
}

