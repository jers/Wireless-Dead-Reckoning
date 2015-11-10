#include "Filter_Data.h"




/*buffer buffer_Accelerometer_x; 
buffer buffer_Accelerometer_y; 
buffer buffer_Accelerometer_z;
buffer buffer_Pitch;
buffer buffer_Roll;
buffer buffer_Temperature; 

buffer  buffer_list [6];
*/

void Initialize_Filters(buffer * filter) {
		for (int i = 0; i < D; i++) 
			filter->buffer[i] = 0;
		filter->i = 0; 
	
	
}

	/*for (int i = 0; i < D; i++) {
		buffer_Accelerometer_x.buffer[i] =  buffer_Accelerometer_y.buffer[i] = buffer_Accelerometer_z.buffer[i] = buffer_Pitch.buffer[i] = buffer_Roll.buffer[i] = buffer_Temperature.buffer[i] = 0;
	}
	buffer_Accelerometer_x.i =  buffer_Accelerometer_y.i = buffer_Accelerometer_z.i = buffer_Pitch.i = buffer_Roll.i = buffer_Temperature.i = 0;

	
	buffer_list[0] = buffer_Accelerometer_x;
	buffer_list[1] = buffer_Accelerometer_y;
	buffer_list[2] = buffer_Accelerometer_z;
	buffer_list[3] = buffer_Pitch;
	buffer_list[4] = buffer_Roll;
	buffer_list[5] = buffer_Temperature;
	
}*/
/*
void moving_filter(float * value, int type) {
	
	buffer movingFilter_Buffer = buffer_list[type];
	
	uint32_t i, j;
			
	i = movingFilter_Buffer.i;
	j = (i + 2) % D;
	
	*value = (.4*movingFilter_Buffer.buffer[i] + .4 * *value + .2 * movingFilter_Buffer.buffer[j]);
	
	i = (i + 1) % D;
	
	movingFilter_Buffer.i = i;
	movingFilter_Buffer.buffer[i] = *value;
	
	
}
/*/

void moving_filter(buffer * filter, float * value) {
	
	uint32_t i, j;
			
	i = filter->i;
	j = (i + 2) % D;
	
	*value = (.4*filter->buffer[i] + .4 * *value + .2 * filter->buffer[j]);
	
	i = (i + 1) % D;
	
	filter->i = i;
	filter->buffer[i] = *value;
	
	
	
}

