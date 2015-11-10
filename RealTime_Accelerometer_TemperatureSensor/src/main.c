/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/


#include "Initialize_Modules.h"
#include "Initialize_Interrupts.h"
#include "Initialize_Timers.h"
#include "GPIO_Manager.h"

#include "Accelerometer_Data.h"
#include "ADC_TemperatureSensor_Data.h"
#include "Filter_Data.h"

#include "Threads.h"
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
#include "main.h"



/*
 * main: initialize and start the system
 */
int main (void) {
	
	
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	
  //initialize peripherals here
	Initialize_Modules();
	Initialize_Interrupts();
  Initialize_Timers();
	Initialize_GPIO();
	
  // create 'thread' functions that start executing,
	Create_Threads();
	
	osKernelStart ();                         // start thread execution 
	
	

		
		
		
		
}
	
		
		
		
		
	



