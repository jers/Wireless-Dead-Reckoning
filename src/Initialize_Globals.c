#include "Globals.h"

float Accelerometer_Data [3];
float Temperature_Celcius;

int debug;


buffer buffer_Accelerometer_x; 
buffer buffer_Accelerometer_y; 
buffer buffer_Accelerometer_z;
buffer buffer_Pitch;
buffer buffer_Roll;
buffer buffer_Temperature; 

int digits [3];
int i; 
int alternate_keyPress;
int display_periodLocation; 
int Alarm; 
int Display_off; 
int State; 
int decimalGuess; 
int Column; 
int keypad_Availible;

int prevState;
int prevDigits[3]; 
int guessResult; 
float Pitch, Roll;
int num_guesses;


void Initialize_Globals() {
	for(int i = 0; i < 3; i++) {
		digits[i] = prevDigits[i] = Accelerometer_Data[i] = 0;
	}
	
	i = 0; 
	alternate_keyPress = 0; 
	keypad_Availible = 0;
	Temperature_Celcius = 0.0;
	debug = 0; 
	display_periodLocation = 0; 
	Alarm = 0; 
	Display_off = 0; 
	State = STANDARD_STATE; 
	prevState = TEMPERATURE_STATE; 
	decimalGuess = 0; 
	guessResult = 0;
	Pitch = 0;
	Roll = 0;
	num_guesses = 0;
	Column = 0;
	
	for (int i = 0; i < D; i++) {
		buffer_Accelerometer_x.buffer[i] =  buffer_Accelerometer_y.buffer[i] = buffer_Accelerometer_z.buffer[i] = buffer_Pitch.buffer[i] = buffer_Roll.buffer[i] = buffer_Temperature.buffer[i] = 0;
	}
	buffer_Accelerometer_x.i =  buffer_Accelerometer_y.i = buffer_Accelerometer_z.i = buffer_Pitch.i = buffer_Roll.i = buffer_Temperature.i = 0;

}


