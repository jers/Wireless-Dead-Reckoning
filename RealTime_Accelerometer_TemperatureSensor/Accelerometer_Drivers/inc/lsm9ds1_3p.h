/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LSM9DS1
#define __LSM9DS1

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
 #include "stm32f4xx.h"
 #include "stm32f4xx_gpio.h"
 #include "stm32f4xx_rcc.h"
 #include "stm32f4xx_spi.h"
	 
#define LSM9DS1_FLAG_TIMEOUT         ((uint32_t)0x1000)

	 /* LSM9DS1 struct */
typedef struct
{
  uint8_t Power_Mode_Output_DataRate;         /* Ppower down or /active mode with output data rate 3.125 / 6.25 / 12.5 / 25 / 50 / 100 / 400 / 800 / 1600 HZ */
  uint8_t Axes_Enable;                        /* Axes enable */
  uint8_t Filter_Mode;	 				 				      /* Block or update Low/High registers of data until all data is read */
	uint8_t AA_Filter_BW;												/* Choose anti-aliasing filter BW 800 / 400 / 200 / 50 Hz*/
  uint8_t Full_Scale;                         /* Full scale 2 / 4 / 8 / 16 g */
	uint8_t Decimation;													/* Decimation of acceleration data on OUT REG and FIFO. Default value: 00 */
}LSM9DS1_InitTypeDef;
 

/* LSM9DS1 Data ready interrupt struct */
typedef struct
{
  uint8_t Dataready_Interrupt;                /* Enable/Disable data ready interrupt */
}LSM9DS1_DRYInterruptConfigTypeDef;  

/**
  * @}
  */
	 

/**
  * @brief  LSM9DS1 SPI Interface pins
  */
#define LSM9DS1_SPI                       SPI1
#define LSM9DS1_SPI_CLK                   RCC_APB2Periph_SPI1

#define LSM9DS1_SPI_SCK_PIN               GPIO_Pin_5                  /* PA.05 */
#define LSM9DS1_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define LSM9DS1_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define LSM9DS1_SPI_SCK_SOURCE            GPIO_PinSource5
#define LSM9DS1_SPI_SCK_AF                GPIO_AF_SPI1

#define LSM9DS1_SPI_MISO_PIN              GPIO_Pin_6                  /* PA.6 */
#define LSM9DS1_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define LSM9DS1_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define LSM9DS1_SPI_MISO_SOURCE           GPIO_PinSource6
#define LSM9DS1_SPI_MISO_AF               GPIO_AF_SPI1

#define LSM9DS1_SPI_MOSI_PIN              GPIO_Pin_7                  /* PA.7 */
#define LSM9DS1_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOA */
#define LSM9DS1_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define LSM9DS1_SPI_MOSI_SOURCE           GPIO_PinSource7
#define LSM9DS1_SPI_MOSI_AF               GPIO_AF_SPI1

#define LSM9DS1_SPI_CS_PIN                GPIO_Pin_2                  /* PE.02 */
#define LSM9DS1_SPI_CS_GPIO_PORT          GPIOE                       /* GPIOE */
#define LSM9DS1_SPI_CS_GPIO_CLK           RCC_AHB1Periph_GPIOE

#define LSM9DS1_SPI_INT1_PIN              GPIO_Pin_0                  /* PE.00 */
#define LSM9DS1_SPI_INT1_GPIO_PORT        GPIOE                       /* GPIOE */
#define LSM9DS1_SPI_INT1_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LSM9DS1_SPI_INT1_EXTI_LINE        EXTI_Line0
#define LSM9DS1_SPI_INT1_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
#define LSM9DS1_SPI_INT1_EXTI_PIN_SOURCE  EXTI_PinSource0
#define LSM9DS1_SPI_INT1_EXTI_IRQn        EXTI0_IRQn 

#define LSM9DS1_SPI_INT2_PIN              GPIO_Pin_1                  /* PE.01 */
#define LSM9DS1_SPI_INT2_GPIO_PORT        GPIOE                       /* GPIOE */
#define LSM9DS1_SPI_INT2_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LSM9DS1_SPI_INT2_EXTI_LINE        EXTI_Line1
#define LSM9DS1_SPI_INT2_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
#define LSM9DS1_SPI_INT2_EXTI_PIN_SOURCE  EXTI_PinSource1
#define LSM9DS1_SPI_INT2_EXTI_IRQn        EXTI1_IRQn 



/** @defgroup STM32F4_DISCOVERY_LSM9DS1_Exported_Macros
  * @{
  */
	
#define LSM9DS1_CS_LOW()       GPIO_ResetBits(LSM9DS1_SPI_CS_GPIO_PORT, LSM9DS1_SPI_CS_PIN)
#define LSM9DS1_CS_HIGH()      GPIO_SetBits(LSM9DS1_SPI_CS_GPIO_PORT, LSM9DS1_SPI_CS_PIN)

	 /*******************************************************************************
*  CTRL_REG1: Control Register 1
*  Read/Write  register
*  Default value: 0x00
*******************************************************************************/
#define LSM9DS1_CTRL_REG1       	 0x10

	 /*******************************************************************************
*  CTRL_REG1: Control Register 2
*  Read/Write  register
*  Default value: 0x00
*******************************************************************************/
#define LSM9DS1_CTRL_REG2       	 0x11
	 
	 /*******************************************************************************
*  CTRL_REG6: Control Register 6
*  Read/Write  register
*  Default value: 0x00
*******************************************************************************/
#define LSM9DS1_CTRL_REG6       	 0x20
	 
	 
	 	 /*******************************************************************************
*  CTRL_REG5: Accelerometer Control Register 5
*  Read/Write  register
*  Default value: 0x00
*******************************************************************************/
#define LSM9DS1_CTRL_REG5       	 0x1F


	 /*******************************************************************************
*  CTRL_REG6: INT1 Control Register
*  Read/Write  register
*  Default value: 0x00
*******************************************************************************/
#define LSM9DS1_INT1_CTRL       	 0x0C


	   /** @defgroup Power_Mode_selection 
  * @{
  */
#define LSM9DS1_PWRDWN						((uint8_t)0x00)
#define LSM9DS1_DATARATE_10				((uint8_t)0x20)
#define LSM9DS1_DATARATE_50				((uint8_t)0x40)
#define LSM9DS1_DATARATE_119			((uint8_t)0x60)
#define LSM9DS1_DATARATE_238			((uint8_t)0x80)
#define LSM9DS1_DATARATE_476			((uint8_t)0xA0)
#define LSM9DS1_DATARATE_952			((uint8_t)0xC0)
#define LSM9DS1_DATARATE_NA				((uint8_t)0xE0)

	 
  /** @defgroup Full_Scale_selection 
  * @{
  */
#define LSM9DS1_FULLSCALE_2					((uint8_t)0x00)
#define LSM9DS1_FULLSCALE_4					((uint8_t)0x10)
#define LSM9DS1_FULLSCALE_8					((uint8_t)0x18)
#define LSM9DS1_FULLSCALE_16				((uint8_t)0x08)

	 


	
	 /** @defgroup Filter_BW_Option 
		Bandwidth selection. Default value: 0
		(0: bandwidth determined by ODR selection:
		- BW = 408 Hz when ODR = 952 Hz, 50 Hz, 10 Hz;
		- BW = 211 Hz when ODR = 476 Hz;
		- BW = 105 Hz when ODR = 238 Hz;
		- BW = 50 Hz when ODR = 119 Hz;
1: bandwidth selected according to BW_XL [2:1] selection)
  * @{
  */
#define LSM9DS1_BW_MODE_DEFAULT			((uint8_t)0x00)
#define LSM9DS1_BW_MODE_CUSTOM			((uint8_t)0x04)
/**
  * @}
  */ 
	
	 /** @defgroup Antialiasing_Filter_BW 
  * @{
  */
#define LSM9DS1_AA_BW_408						((uint8_t)0x00)
#define LSM9DS1_AA_BW_211						((uint8_t)0x01)
#define LSM9DS1_AA_BW_105						((uint8_t)0x02)
#define LSM9DS1_AA_BW_50						((uint8_t)0x03)
/**
  * @}
  */ 
	
	
	/*******************************************************************************
*  Output registers: X, Y, Z axes 8 bit MSB/LSB registers (combined 16 bits result)
*  Read only register
*  Default value: 0x00 corresponds to 0g acceleration
*******************************************************************************/
#define LSM9DS1_ACC_OUT_X_L       	 	 0x28
#define LSM9DS1_ACC_OUT_X_H       	 	 0x29
#define LSM9DS1_ACC_OUT_Y_L       	 	 0x2A
#define LSM9DS1_ACC_OUT_Y_H       	 	 0x2B
#define LSM9DS1_ACC_OUT_Z_L       	 	 0x2C
#define LSM9DS1_ACC_OUT_Z_H       	 	 0x2D
	 
	 	 /** @defgroup Decimation of acceleration data on OUT REG and FIFO. Default value: 00 
		 0: no decimation
		 2: update every 2 samples
		 4: update every 4 samples
	   8: update every 8 samples
  * @{
  */
#define LSM9DS1_ACC_DEC_0						((uint8_t)0x00)
#define LSM9DS1_ACC_DEC_2						((uint8_t)0x40)
#define LSM9DS1_ACC_DEC_4						((uint8_t)0x80)
#define LSM9DS1_ACC_DEC_8						((uint8_t)0xC0)
/**
  * @}
  */ 
	 
	 
	 	 	 /** @defgroup Accelerometer’s X,Y,Z-axis output enable. Default value: 1 
  * @{
  */
#define LSM9DS1_X_ENABLE						((uint8_t)0x08)
#define LSM9DS1_Y_ENABLE						((uint8_t)0x10)
#define LSM9DS1_Z_ENABLE						((uint8_t)0x20)
/**
  * @}
  */ 
	 
	 	 /** @defgroup Sensitivity 
  * @{
  */
 #define LSM9DS1_ACC_SENSITIVITY_2G    	0.061 		      
 #define LSM9DS1_ACC_SENSITIVITY_4G		  0.122		
 #define LSM9DS1_ACC_SENSITIVITY_6G			0.183 
 #define LSM9DS1_ACC_SENSITIVITY_8G		  0.244	   	 
 #define LSM9DS1_ACC_SENSITIVITY_16G    0.732      
  /**
  * @}
  */
	 
	 	 	 /** @defgroup INT1 register control 
  * @{
  */
 #define LSM9DS1_DATA_READY_INTERRUPT_DISABLED     		 ((uint8_t)0x00)     
 #define LSM9DS1_DATA_READY_INTERRUPT_ENABLED					 ((uint8_t)0x41)
  /**
  * @}
  */
	 
void LSM9DS1_Init(LSM9DS1_InitTypeDef *LSM9DS1Struct);
void LSM9DS1_DataReadyInterruptConfig(LSM9DS1_DRYInterruptConfigTypeDef *LSM9DS1_InterruptConfigStruct);
void LSM9DS1_ReadACC(float* out);
void LSM9DS1_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
void LSM9DS1_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
	 
uint32_t LSM9DS1_TIMEOUT_UserCallback(void);
	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif /* __LSM9DS1_H */
