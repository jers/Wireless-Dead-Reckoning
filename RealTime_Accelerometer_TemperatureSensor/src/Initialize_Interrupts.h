#ifndef osObjectsPublic
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#endif                    // RTOS object definitions
#include "stm32f4xx_exti.h"


void Initialize_Interrupts(void);
void Initialize_Accelerometer_Int1(void);
void Initialize_Keypad_Column_Interrupts(void);
void Initialize_ADC_Interrupt(void);
void Initialize_Column_1_Interrupt(void);
void Initialize_Column_2_Interrupt(void);
void Initialize_Column_3_Interrupt(void);
void Initialize_Column_4_Interrupt(void);