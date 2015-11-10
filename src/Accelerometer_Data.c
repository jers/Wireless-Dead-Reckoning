#include "Accelerometer_Data.h"
#include "Filter_Data.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
#include "Math.h"
#define PI  3.14159265

float	Cal1 [3][3] = { {  0.001003123061,	 0.000014174236,	0.000006273702 },
			           { -0.000017299253,	 0.001020204071,	0.000017503067 },
			           {  0.000006878142, -0.000003705638,	0.001004035037 } };
	
float	Cal2 [3] = { -0.019095429218, -0.009445278270, -0.045678042626 };
	
buffer  buffer_list [5];

buffer Accelerometer_Filter_x;
buffer Accelerometer_Filter_y;
buffer Accelerometer_Filter_z;
buffer Pitch_Filter; 
buffer Roll_Filter;


void Initialize_Accelerometer_movingFilters() {
	
	Initialize_Filters(&Accelerometer_Filter_x);
	Initialize_Filters(&Accelerometer_Filter_y);
	Initialize_Filters(&Accelerometer_Filter_z);
	Initialize_Filters(&Pitch_Filter);
	Initialize_Filters(&Roll_Filter);
	

	buffer_list[0] = Accelerometer_Filter_x;
	buffer_list[1] = Accelerometer_Filter_y;
	buffer_list[2] = Accelerometer_Filter_z;
	buffer_list[3] = Pitch_Filter;
	buffer_list[4] = Roll_Filter;

}

void updateAccelerometer(float * pitch, float * roll) {
		
		float Accelerometer_Data [3];
		readAccelerometer(Accelerometer_Data);
		for(int i = 0; i < 3; i++)
			moving_filter(&buffer_list[i], &Accelerometer_Data[i]);
		
		calculate_Pitch(Accelerometer_Data, pitch);
		calculate_Roll(Accelerometer_Data, roll);
		
		moving_filter(&buffer_list[3], pitch);
		moving_filter(&buffer_list[4], roll);
}

void readAccelerometer(float * Accelerometer_Data) {
	
	float raw_Accelerometer [3];
	LIS3DSH_ReadACC(raw_Accelerometer); 
	
	
	float Matrix_calibration_Value;
	
	
	for(int i = 0; i < 3; i++) {
		Matrix_calibration_Value = 0;
		for(int j = 0; j < 3; j++) {
			Matrix_calibration_Value += raw_Accelerometer[j] * Cal1[i][j];
		}
		Accelerometer_Data[i] = Matrix_calibration_Value + Cal2[i];
		//debug_d[i] = Accelerometer_Data[i];
	}
	
	
	
}


void calculate_Pitch(float * Accelerometer_Data, float * pitch) {
	
	float y = Accelerometer_Data[0];
	float x = Accelerometer_Data[1];
	float z = Accelerometer_Data[2];
	
	float Pitch; 
	
	Pitch = atan(x / sqrt(y*y + z*z)) * (180 / PI);
	if (Pitch < 0)
		Pitch = -Pitch; 
	
	
	*pitch = Pitch; 
	
}

void calculate_Roll(float * Accelerometer_Data, float * roll) {

	float y = Accelerometer_Data[0];
	float x = Accelerometer_Data[1];
	float z = Accelerometer_Data[2];
	
	float Roll;
	
	Roll = atan(y / sqrt(x*x + z*z)) * (180 / PI);
	if (Roll < 0)
		Roll = -Roll; 
	
	*roll = Roll;

}
