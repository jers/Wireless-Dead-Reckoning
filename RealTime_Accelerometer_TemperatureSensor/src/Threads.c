
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
#include "Threads.h"
#include "Accelerometer_Data.h"
#include "ADC_TemperatureSensor_Data.h"
#include "GPIO_Manager.h"

osThreadId Accelerometer_thread;
osThreadId TemperatureSensor_thread;
osThreadId Control_thread;



 



osMailQId mail_box_Peripherals_to_Control;



osMailQDef(mail_box_Peripherals_to_Control, 10 , mail_Peripherals_to_Control);










void Accelerometer(void const *argument){

	mail_Peripherals_to_Control Accelerometer_Data;

	float pitch, roll; 
	while(1){
			osSignalWait( 0x10 , osWaitForever );
			updateAccelerometer(&pitch, &roll);
			Accelerometer_Data.pitch = pitch;
			Accelerometer_Data.roll = roll;
			Accelerometer_Data.temperature = 0; 

			Accelerometer_Data.update_Type = ACC; 

			osMailPut(mail_box_Peripherals_to_Control, &Accelerometer_Data);
	}
	
}


void TemperatureSensor(void const *argument) {

	float Temperature_Celcius; 
	mail_Peripherals_to_Control Temperature_Data;
	

	while(1){
			osSignalWait( 0x10 , osWaitForever );
			updateADC_Temperature(&Temperature_Celcius);
		
			Temperature_Data.temperature = Temperature_Celcius; 
			Temperature_Data.update_Type = TMP;
			Temperature_Data.pitch = 0;
			Temperature_Data.roll = 0;
			osMailPut(mail_box_Peripherals_to_Control, &Temperature_Data);


	}
	

	
}


//polling data (slower) 100hz & 50hz << 500hz control << 2khz display

void Control(void const *argument) {
	
	float pitch = 0;
	float roll = 0;
	float Degrees_Celcius = 0;
	
	
	osEvent  Peripheral_Mail_Event;
	
	
		
	while(1){


			
		Peripheral_Mail_Event = osMailGet(mail_box_Peripherals_to_Control,osWaitForever); //wait for Mail	
		if (Peripheral_Mail_Event.status == osEventMail) {
			mail_Peripherals_to_Control *received_Peripheral = (mail_Peripherals_to_Control *) Peripheral_Mail_Event.value.p;      // ".p" indicates that the message is a pointer
			switch (received_Peripheral->update_Type) {
				case ACC:
					pitch = received_Peripheral->pitch;
					roll = received_Peripheral->roll;
					break;
				case TMP:
					Degrees_Celcius = received_Peripheral->temperature;
					break;
				
			}
			osMailFree(mail_box_Peripherals_to_Control, received_Peripheral);
		}
						
		
		debug_b = pitch;
		debug_c = Degrees_Celcius; 
		
		

	}	

}

void Create_Threads() {
	
	Create_Mutexs();
	Create_Message_Queues();
	
	osThreadDef(Accelerometer, osPriorityRealtime, 1, 0);
	osThreadDef(TemperatureSensor, osPriorityRealtime, 1, 0);
	osThreadDef(Control, osPriorityNormal, 1, 0);



	TemperatureSensor_thread = osThreadCreate ( osThread ( TemperatureSensor) , NULL );
	Accelerometer_thread     = osThreadCreate ( osThread ( Accelerometer    ) , NULL );
 	Control_thread           = osThreadCreate ( osThread ( Control          ) , NULL ); 

}

void Create_Mutexs() {
	

	
}

void Create_Message_Queues() {
	
		mail_box_Peripherals_to_Control = osMailCreate(osMailQ(mail_box_Peripherals_to_Control), NULL);
}
