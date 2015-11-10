#include "lis3dsh.h"





void Initialize_Accelerometer_movingFilters(void);
void updateAccelerometer(float * pitch, float * roll);
void readAccelerometer(float * Accelerometer_Datat);
void applyCalibrationMatrix(float * Accelerometer_Data);
void calculate_Pitch(float * Accelerometer_Data, float * pitch);
void calculate_Roll(float * Accelerometer_Data, float * roll);
