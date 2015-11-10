
#ifndef osObjectsPublic
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#endif
#define D 30
#define ANGLE_STATE 0
#define TEMPERATURE_STATE 1
#define RESET_STATE 2
#define DISPLAY_OFF 3

#define NO_SWITCH 4
#define SWITCH_STATE 5
#define SWITCH_ANGLE_STATE 6

#define ANGLE_PITCH 7
#define ANGLE_ROLL 8

#define ON 0
#define OFF 1

#define ACC 0
#define TMP 1
#define KEY 2
#define PRS 3

typedef struct {

	float buffer[D];
	int i; 

} buffer;

typedef struct {
	uint8_t State;
	uint8_t digits[3];
	uint8_t display_periodLocation;
	uint8_t display_on;
} mail_Control_to_Display;

 typedef struct {
	 
	uint8_t update_Type;
	float pitch;
	float roll; 
	float temperature;
	uint8_t state; 
	 
} mail_Peripherals_to_Control;


extern osMailQId mail_box_Peripherals_to_Control;
extern osMailQId mail_box_Control_to_Display;

extern osMutexId GPIO_Keypad_Mutex; 
extern osMutexId Keypad_Mutex; 
extern osMutexId display_Mail_Mutex; 
//extern osMutexId Column_Mutex; 

extern osThreadId	Accelerometer_thread;
extern osThreadId	TemperatureSensor_thread;
extern osThreadId Display_thread; 
extern osThreadId Keypad_thread; 
extern osThreadId Control_thread; 


extern int debug_a;
extern float debug_b, debug_c; 
extern float debug_d [3];

