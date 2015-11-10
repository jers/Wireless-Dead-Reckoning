/* Includes ------------------------------------------------------------------*/
#include "lis3dsh.h"


int debug_acc = 0;

__IO uint32_t  LSM9DS1Timeout = LSM9DS1_FLAG_TIMEOUT;  

/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80) 
/* Multiple byte read/write command */ 
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x00)

#define USE_DEFAULT_TIMEOUT_CALLBACK


static uint8_t LSM9DS1_SendByte(uint8_t byte);
static void LSM9DS1_LowLevel_Init(void);


void LSM9DS1_Init(LSM9DS1_InitTypeDef *LSM9DS1_InitStruct)
{
  uint8_t ctrl = 0x00;
 
  /* Configure the low level interface ---------------------------------------*/
  LSM9DS1_LowLevel_Init();
  
  /* Configure MEMS: data rate, update mode and axes */
  ctrl = (uint8_t) (LSM9DS1_InitStruct->Power_Mode_Output_DataRate  | \
										LSM9DS1_InitStruct->Full_Scale           				| \
										LSM9DS1_InitStruct->Filter_Mode									| \
										LSM9DS1_InitStruct->AA_Filter_BW);
                    
  /* Write value to MEMS CTRL_REG4 regsister */
  LSM9DS1_Write(&ctrl, LSM9DS1_CTRL_REG6, 1);
	
	/* Configure MEMS: Anti-aliasing filter, full scale, self test  */
	ctrl = (uint8_t) (LSM9DS1_InitStruct->Decimation | \
										LSM9DS1_InitStruct->Axes_Enable);
	
	/* Write value to MEMS CTRL_REG5 regsister */
	LSM9DS1_Write(&ctrl, LSM9DS1_CTRL_REG5, 1);
	
}


void LSM9DS1_DataReadyInterruptConfig(LSM9DS1_DRYInterruptConfigTypeDef *LSM9DS1_IntConfigStruct)
{
  uint8_t ctrl = 0x00;
  
  /* Read CLICK_CFG register */
  //LSM9DS1_Read(&ctrl, LSM9DS1_INT1_CTRL, 1);
  
  /* Configure latch Interrupt request, click interrupts and double click interrupts */                   
  ctrl = (uint8_t)(LSM9DS1_IntConfigStruct->Dataready_Interrupt);
  
  /* Write value to MEMS CLICK_CFG register */
  LSM9DS1_Write(&ctrl, LSM9DS1_INT1_CTRL, 1);
}




void LSM9DS1_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  /* Configure the MS bit: 
       - When 0, the address will remain unchanged in multiple read/write commands.
       - When 1, the address will be auto incremented in multiple read/write commands.
  */
  if(NumByteToWrite > 0x01)
  {
    WriteAddr |= (uint8_t)MULTIPLEBYTE_CMD;
  }
  /* Set chip select Low at the start of the transmission */
  LSM9DS1_CS_LOW();
  
  /* Send the Address of the indexed register */
  LSM9DS1_SendByte(WriteAddr);
  /* Send the data that will be written into the device (MSB First) */
  while(NumByteToWrite >= 0x01)
  {
    LSM9DS1_SendByte(*pBuffer);
    NumByteToWrite--;
    pBuffer++;
  }
  
  /* Set chip select High at the end of the transmission */ 
  LSM9DS1_CS_HIGH();
}


void LSM9DS1_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{  
  if(NumByteToRead > 0x01)
  {
    ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
  }
  else
  {
    ReadAddr |= (uint8_t)READWRITE_CMD;
  }
  /* Set chip select Low at the start of the transmission */
  LSM9DS1_CS_LOW();
  
  /* Send the Address of the indexed register */
  LSM9DS1_SendByte(ReadAddr);
  
  /* Receive the data that will be read from the device (MSB First) */
  while(NumByteToRead > 0x00)
  {
    /* Send dummy byte (0x00) to generate the SPI clock to LSM9DS1 (Slave device) */
    *pBuffer = LSM9DS1_SendByte(DUMMY_BYTE);
    NumByteToRead--;
    pBuffer++;
  }
  
  /* Set chip select High at the end of the transmission */ 
  LSM9DS1_CS_HIGH();
}

/**
  * @brief  Read LSM9DS1 output register, and calculate the acceleration 
  *         ACC[mg]=SENSITIVITY* (out_h*256+out_l)/16 (12 bit rappresentation)
  * @param  s16 buffer to store data
  * @retval None
  */
void LSM9DS1_ReadACC(float* out)
{
  uint8_t buffer[6];
  uint8_t ctrl = 0x00, i = 0x00;
	//uint8_t offsetX, offsetY, offsetZ;
	int16_t aggregateResult = 0;
  
  LSM9DS1_Read(&ctrl, LSM9DS1_CTRL_REG6, 1);  
	LSM9DS1_Read(&buffer[0], LSM9DS1_ACC_OUT_X_L, 1);
	LSM9DS1_Read(&buffer[1], LSM9DS1_ACC_OUT_X_H, 1);
	LSM9DS1_Read(&buffer[2], LSM9DS1_ACC_OUT_Y_L, 1);
	LSM9DS1_Read(&buffer[3], LSM9DS1_ACC_OUT_Y_H, 1);
	LSM9DS1_Read(&buffer[4], LSM9DS1_ACC_OUT_Z_L, 1);
	LSM9DS1_Read(&buffer[5], LSM9DS1_ACC_OUT_Z_H, 1);
  
	ctrl = (ctrl & 0x18	) >> 3;
	debug_acc++;
	
  switch(ctrl)
    {
    /* FS bits = 000 ==> Sensitivity typical value = 0.061 milligals/digit*/ 
    case 0x00:
      for(i=0; i<0x06; i=i+2)
      {
				aggregateResult = (int32_t)(buffer[i] | buffer[i+1] << 8);
        *out =(float)(LSM9DS1_ACC_SENSITIVITY_2G * (float)aggregateResult);
        out++;
      }
      break;
			
    /* FS bit = 001 ==> Sensitivity typical value = 0.122 milligals/digit*/ 
    case 0x01:
      for(i=0; i<0x06; i=i+2)
      {
				aggregateResult = (int32_t)(buffer[i] | buffer[i+1] << 8);
        *out =(float)(LSM9DS1_ACC_SENSITIVITY_16G * (float)aggregateResult);
        out++;
      }         
      break;
			
		/* FS bit = 010 ==> Sensitivity typical value = 0.183 milligals/digit*/ 
    case 0x02:
      for(i=0; i<0x06; i=i+2)
      {
				aggregateResult = (int32_t)(buffer[i] | buffer[i+1] << 8);
        *out =(float)(LSM9DS1_ACC_SENSITIVITY_4G * (float)aggregateResult);
        out++;
      }         
      break;
			
		 /* FS bit = 011 ==> Sensitivity typical value = 0.244 milligals/digit*/ 
    case 0x03:
      for(i=0; i<0x06; i=i+2)
      {
				aggregateResult = (int32_t)(buffer[i] | buffer[i+1] << 8);
        *out =(float)(LSM9DS1_ACC_SENSITIVITY_8G * (float)aggregateResult);
        out++;
      }         
      break;
			
    default:
      break;
    }
 }

/**
  * @brief  Initializes the low level interface used to drive the LSM9DS1
  * @param  None
  * @retval None
  */
static void LSM9DS1_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  /* Enable the SPI periph */
  RCC_APB2PeriphClockCmd(LSM9DS1_SPI_CLK, ENABLE);

  /* Enable SCK, MOSI and MISO GPIO clocks */
  RCC_AHB1PeriphClockCmd(LSM9DS1_SPI_SCK_GPIO_CLK | LSM9DS1_SPI_MISO_GPIO_CLK | LSM9DS1_SPI_MOSI_GPIO_CLK, ENABLE);

  /* Enable CS  GPIO clock */
  RCC_AHB1PeriphClockCmd(LSM9DS1_SPI_CS_GPIO_CLK, ENABLE);
  
  /* Enable INT1 GPIO clock */
  RCC_AHB1PeriphClockCmd(LSM9DS1_SPI_INT1_GPIO_CLK, ENABLE);
  
  /* Enable INT2 GPIO clock */
  //RCC_AHB1PeriphClockCmd(LSM9DS1_SPI_INT2_GPIO_CLK, ENABLE);

  GPIO_PinAFConfig(LSM9DS1_SPI_SCK_GPIO_PORT, LSM9DS1_SPI_SCK_SOURCE, LSM9DS1_SPI_SCK_AF);
  GPIO_PinAFConfig(LSM9DS1_SPI_MISO_GPIO_PORT, LSM9DS1_SPI_MISO_SOURCE, LSM9DS1_SPI_MISO_AF);
  GPIO_PinAFConfig(LSM9DS1_SPI_MOSI_GPIO_PORT, LSM9DS1_SPI_MOSI_SOURCE, LSM9DS1_SPI_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = LSM9DS1_SPI_SCK_PIN;
  GPIO_Init(LSM9DS1_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  LSM9DS1_SPI_MOSI_PIN;
  GPIO_Init(LSM9DS1_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin = LSM9DS1_SPI_MISO_PIN;
  GPIO_Init(LSM9DS1_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(LSM9DS1_SPI);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(LSM9DS1_SPI, &SPI_InitStructure);

  /* Enable SPI1  */
  SPI_Cmd(LSM9DS1_SPI, ENABLE);

  /* Configure GPIO PIN for Lis Chip select */
  GPIO_InitStructure.GPIO_Pin = LSM9DS1_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LSM9DS1_SPI_CS_GPIO_PORT, &GPIO_InitStructure);

	/* set pin-select to low on LSM9DS1 board */
	GPIO_ResetBits(GPIOE, GPIO_Pin_2);

  /* Deselect : Chip Select high */
  //GPIO_SetBits(LSM9DS1_SPI_CS_GPIO_PORT, LSM9DS1_SPI_CS_PIN);
  
  /* Configure GPIO PINs to detect Interrupts */
  GPIO_InitStructure.GPIO_Pin = LSM9DS1_SPI_INT1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(LSM9DS1_SPI_INT1_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LSM9DS1_SPI_INT2_PIN;
  GPIO_Init(LSM9DS1_SPI_INT2_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Sends a Byte through the SPI interface and return the Byte received 
  *         from the SPI bus.
  * @param  Byte : Byte send.
  * @retval The received byte value
  */
static uint8_t LSM9DS1_SendByte(uint8_t byte)
{
  /* Loop while DR register in not emplty */
  LSM9DS1Timeout = LSM9DS1_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(LSM9DS1_SPI, SPI_I2S_FLAG_TXE) == RESET)
  {
    if((LSM9DS1Timeout--) == 0) return LSM9DS1_TIMEOUT_UserCallback();
  }
  
  /* Send a Byte through the SPI peripheral */
  SPI_I2S_SendData(LSM9DS1_SPI, byte);
  
  /* Wait to receive a Byte */
  LSM9DS1Timeout = LSM9DS1_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(LSM9DS1_SPI, SPI_I2S_FLAG_RXNE) == RESET)
  {
    if((LSM9DS1Timeout--) == 0) return LSM9DS1_TIMEOUT_UserCallback();
  }
  
  /* Return the Byte read from the SPI bus */
  return (uint8_t)SPI_I2S_ReceiveData(LSM9DS1_SPI);
}


#ifdef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t LSM9DS1_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
//  while (1)
 // {   
  //}
	return 0;
}
#endif /* USE_DEFAULT_TIMEOUT_CALLBACK */



