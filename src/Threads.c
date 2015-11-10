
#ifndef GLOBALS
#define GLOBALS
#include "Globals.h"
#endif
#include "Threads.h"
#include "Accelerometer_Data.h"
#include "Keypad.h"
#include "ADC_TemperatureSensor_Data.h"
#include "Display.h"
#include "GPIO_Manager.h"
#include "Convert.h"

osThreadId Accelerometer_thread;
osThreadId TemperatureSensor_thread;
osThreadId Display_thread; 
osThreadId Keypad_thread; 
osThreadId Control_thread;

osMutexId GPIO_Keypad_Mutex; 
osMutexId Keypad_Mutex; 
osMutexId display_Mail_Mutex; 

 



osMailQId mail_box_Peripherals_to_Control;
osMailQId mail_box_Control_to_Display;



osMailQDef(mail_box_Peripherals_to_Control, 10 , mail_Peripherals_to_Control);
osMailQDef(mail_box_Control_to_Display, 10 , mail_Control_to_Display);










void Accelerometer(void const *argument){

	mail_Peripherals_to_Control Accelerometer_Data;

	float pitch, roll; 
	while(1){
			osSignalWait( 0x10 , osWaitForever );
			updateAccelerometer(&pitch, &roll);
			Accelerometer_Data.pitch = pitch;
			Accelerometer_Data.roll = roll;
			Accelerometer_Data.state = 0;
			Accelerometer_Data.temperature = 0; 

			Accelerometer_Data.update_Type = ACC; 

			osMailPut(mail_box_Peripherals_to_Control, &Accelerometer_Data);
	}
	
}

void Keypad(void const *argument){
	uint8_t State, Column; 
	mail_Peripherals_to_Control Keypad_Data;
	osEvent ColumnSignal; 
	
	while(1){
		
			ColumnSignal = osSignalWait( 0x00 , osWaitForever );
			
			osMutexWait(Keypad_Mutex, osWaitForever);
			
			switch(ColumnSignal.value.signals) {
				
				case 0x00000011: Column = 1;
					State = SWITCH_STATE;
					break;
				case 0x00000101: Column = 2;
					State = RESET_STATE;
					break;
				case 0x00000111: Column = 3;
					State = SWITCH_ANGLE_STATE;
					break;
				case 0x00001001: Column = 4;
					State = RESET_STATE;
					break;
				default: Column = 0;
					break;
			}	
			debug_b= Column;
			if (Column) {
			//if (getKeypadNumber(&State, Column)) {
				Keypad_Data.state = State;
				Keypad_Data.update_Type = KEY;
				Keypad_Data.temperature = 0;
				Keypad_Data.pitch = 0;
				Keypad_Data.roll = 0;
				osMailPut(mail_box_Peripherals_to_Control, &Keypad_Data);

			} else {
				
				Keypad_Data.state = 0;
				Keypad_Data.update_Type = PRS;
				Keypad_Data.temperature = 0;
				Keypad_Data.pitch = 0;
				Keypad_Data.roll = 0;
				osMailPut(mail_box_Peripherals_to_Control, &Keypad_Data);
				
			}
			
			osSignalWait( 0x00001111, osWaitForever);

			osMutexRelease(Keypad_Mutex); 
			
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
			Temperature_Data.state = 0;
			Temperature_Data.pitch = 0;
			Temperature_Data.roll = 0;
			osMailPut(mail_box_Peripherals_to_Control, &Temperature_Data);


	}
	

	
}


void Display(void const *argument){ 
	
	osEvent Control_Mail_Event; 
	uint8_t digits [3];
	uint8_t state;
	uint8_t period_location;
	uint8_t is_display_on;
	
	while(1){
		
		osSignalWait(0x10, osWaitForever);
		
		


		Control_Mail_Event = osMailGet(mail_box_Control_to_Display, 0); //wait for Mail

		if (Control_Mail_Event.status == osEventMail) {
			
			mail_Control_to_Display *received_Control = (mail_Control_to_Display *)Control_Mail_Event.value.p;       // ".p" indicates that the message is a pointer

			debug_d[0] = digits[0] = received_Control->digits[0];
			debug_d[1] = digits[1] = received_Control->digits[1];
			debug_d[2] = digits[2] = received_Control->digits[2];
			state = received_Control->State;
			period_location = received_Control->display_periodLocation;
			debug_a = state;
			is_display_on = received_Control->display_on;
			osMailFree(mail_box_Control_to_Display, received_Control);

		}
		if (!is_display_on)
			display_empty();
		else {
			switch(state) {
				case RESET_STATE:
					display_empty();
					break;
				default:
					display(digits, 3, period_location);
					break;
			}
		}



	}
}

//polling data (slower) 100hz & 50hz << 500hz control << 2khz display

void Control(void const *argument) {
	
	float pitch = 0;
	float roll = 0;
	float Degrees_Celcius = 0;
	int loopCount = 0; 
	uint8_t Alarm = OFF;
	uint8_t Keypad_readReady = ON;
	
	uint8_t Switch_State = NO_SWITCH;
	uint8_t State = ANGLE_STATE;
	uint8_t prevState = TEMPERATURE_STATE;
	uint8_t angleType = ANGLE_PITCH;
	uint8_t Display_On = ON;
	
	osEvent  Peripheral_Mail_Event;
	mail_Control_to_Display Control_Data;
	
	
	Control_Data.State = State;
	Control_Data.digits[0] = 0;
	Control_Data.digits[1] = 0;
	Control_Data.digits[2] = 0;
	Control_Data.display_periodLocation = 0;
	Control_Data.display_on = 1;
		
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
				case KEY:
					Switch_State = received_Peripheral->state;
					if (Switch_State != SWITCH_ANGLE_STATE && Switch_State != SWITCH_STATE)
						Switch_State = NO_SWITCH;
					//debug_a = State;
					Keypad_readReady = OFF;				
					break;
				case PRS:
					Keypad_readReady = OFF;				
				break;
			}
			osMailFree(mail_box_Peripherals_to_Control, received_Peripheral);
		}
						
		
		//debug_b = pitch;
		//debug_c = Degrees_Celcius; 
		
		


		
		if (Degrees_Celcius > 36) {
			Alarm = ON; 
			if (loopCount % 20 == 0) {
				Display_On = !Display_On;
			}
		}
		else {
			Alarm = OFF;
			Display_On = 1; 
		}
		
		Control_Data.display_on = Display_On;

		if (Keypad_readReady && loopCount % 10 == 0) {
					
					
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == Bit_SET && GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == Bit_SET && GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == Bit_SET && GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == Bit_SET) {
				
				osSignalSet(Keypad_thread, 0x00001111);
				
				Keypad_readReady = ON;
			
			
			}
		}
		if(Switch_State != NO_SWITCH) {
			switch (Switch_State) {
				case SWITCH_STATE:
					if (State == TEMPERATURE_STATE) {
						State = prevState;
						prevState = TEMPERATURE_STATE;
					} else {
						prevState = State;
						State = TEMPERATURE_STATE;
					}
					break; 
				case SWITCH_ANGLE_STATE:
					angleType = (angleType == ANGLE_PITCH)? ANGLE_ROLL : ANGLE_PITCH;
					break;
			}
			Switch_State = NO_SWITCH;
		}
		switch (State) {
			case TEMPERATURE_STATE:
				Control_Data.display_periodLocation = Covert_to_Array(Control_Data.digits, Degrees_Celcius);			
			break;
			case ANGLE_STATE:
				if (angleType == ANGLE_PITCH)
					Control_Data.display_periodLocation = Covert_to_Array(Control_Data.digits, pitch);
				else 
					Control_Data.display_periodLocation = Covert_to_Array(Control_Data.digits, roll);
				break;
			case RESET_STATE:
				prevState = State;
				State = ANGLE_STATE;
				break; 
		}
		
		Control_Data.State = State; 
		osMailPut(mail_box_Control_to_Display, &Control_Data);


		loopCount++;
	}	

}

void Create_Threads() {
	
	Create_Mutexs();
	Create_Message_Queues();
	
	osThreadDef(Accelerometer, osPriorityRealtime, 1, 0);
	osThreadDef(Display, osPriorityNormal, 1, 0);
	osThreadDef(Keypad, osPriorityNormal, 1, 0);
	osThreadDef(TemperatureSensor, osPriorityRealtime, 1, 0);
	osThreadDef(Control, osPriorityNormal, 1, 0);



	TemperatureSensor_thread = osThreadCreate ( osThread ( TemperatureSensor) , NULL );
	Accelerometer_thread     = osThreadCreate ( osThread ( Accelerometer    ) , NULL );
	Display_thread           = osThreadCreate ( osThread ( Display          ) , NULL );
 	Control_thread           = osThreadCreate ( osThread ( Control          ) , NULL ); 
	Keypad_thread            = osThreadCreate ( osThread ( Keypad           ) , NULL );

}

void Create_Mutexs() {
	


	
	osMutexDef(GPIO_Keypad_Mutex);
	osMutexDef(Keypad_Mutex);
	osMutexDef(display_Mail_Mutex );
//	osMutexDef(Column_Mutex);


  GPIO_Keypad_Mutex  = osMutexCreate (osMutex (GPIO_Keypad_Mutex));
	Keypad_Mutex = osMutexCreate (osMutex (Keypad_Mutex));
  display_Mail_Mutex  = osMutexCreate (osMutex (display_Mail_Mutex ));
//	Column_Mutex = osMutexCreate (osMutex (Column_Mutex));

	
}

void Create_Message_Queues() {
	
		
		mail_box_Peripherals_to_Control = osMailCreate(osMailQ(mail_box_Peripherals_to_Control), NULL);
		mail_box_Control_to_Display = osMailCreate(osMailQ(mail_box_Control_to_Display), NULL); 
	
}
