
#ifndef osObjectsPublic
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#endif
#define D 30

#define ACC 0
#define TMP 1


typedef struct {

	float buffer[D];
	int i; 

} buffer;


 typedef struct {
	 
	uint8_t update_Type;
	float pitch;
	float roll; 
	float temperature;
	 
} mail_Peripherals_to_Control;


extern osMailQId mail_box_Peripherals_to_Control;


extern osThreadId	Accelerometer_thread;
extern osThreadId	TemperatureSensor_thread;
extern osThreadId Control_thread; 


extern int debug_a;
extern float debug_b, debug_c; 
extern float debug_d [3];

