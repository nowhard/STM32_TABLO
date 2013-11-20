#include "spi_bus.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_dma.h"
#include <misc.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "tablo.h"

extern struct tablo tab;//структура табло

static void spi1_task(void *pvParameters);//задачи шин
static void spi2_task(void *pvParameters);
static void spi3_task(void *pvParameters);

xSemaphoreHandle xSPI_Buf_Mutex;


uint8_t spi_buses_init(void)//
{
	uint8_t error=0;
	 xTaskCreate(spi1_task,(signed char*)"SPI_1_TASK",64,NULL, tskIDLE_PRIORITY + 1, NULL);
	 xTaskCreate(spi2_task,(signed char*)"SPI_2_TASK",64,NULL, tskIDLE_PRIORITY + 1, NULL);
	 xTaskCreate(spi3_task,(signed char*)"SPI_3_TASK",64,NULL, tskIDLE_PRIORITY + 1, NULL);

	 xSPI_Buf_Mutex=xSemaphoreCreateMutex();

	 if( xSPI_Buf_Mutex != NULL )
	 {
		//
	 }

	return error;
}


void	spi1_config(void)//
{
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA |RCC_AHB1Periph_GPIOC, ENABLE);
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);

	    GPIO_InitTypeDef GPIO_InitStructure;
	    SPI_InitTypeDef SPI_InitStructure;

	    /* Configure SPI1 pins: SCK, MISO and MOSI -------------------------------*/
	    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 |GPIO_Pin_6|GPIO_Pin_7;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	    GPIO_Init(GPIOA, &GPIO_InitStructure);

	    // MISO:
	 /*   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);*/

	    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
	    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	    //SPI_InitStructure.SPI_CRCPolynomial = 7;
	    SPI_Init(SPI1, &SPI_InitStructure);

	    /* Enable SPI1 */
	    SPI_CalculateCRC(SPI1, DISABLE);
	   // SPI_SSOutputCmd(SPI1, ENABLE);
	    SPI_Cmd(SPI1, ENABLE);

	    GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
	//--------------------------------------------------------------------------
		DMA_InitTypeDef DMA_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
//---------------------------
		DMA_StructInit(&DMA_InitStructure);//mosi

		DMA_DeInit(DMA2_Stream3);

		DMA_InitStructure.DMA_Channel = DMA_Channel_3;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI1->DR)) ;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
		DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
		DMA_Init(DMA2_Stream3,&DMA_InitStructure);
//-----------------------------
		// Enable DMA request
		DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);

		SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
//		SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
}

void	spi2_config(void)//
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    /* Configure SPI1 pins: SCK, MISO and MOSI -------------------------------*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // MISO:
 /*   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);*/

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    //SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);


    /* Enable SPI2 */
    SPI_CalculateCRC(SPI2, DISABLE);
    SPI_Cmd(SPI2, ENABLE);

    GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//--------------------------------------------------------------------------
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_StructInit(&DMA_InitStructure);
	DMA_DeInit(DMA1_Stream4);

	//-----------------------------
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI2->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
	DMA_Init(DMA1_Stream4,&DMA_InitStructure);


	DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
//	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
}

void 	spi3_config(void)//
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    /* Configure SPI1 pins: SCK, MISO and MOSI -------------------------------*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // MISO:
 /*   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);*/

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SPI3);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    //SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI3, &SPI_InitStructure);


    /* Enable SPI2 */
    SPI_CalculateCRC(SPI3, DISABLE);
    SPI_Cmd(SPI3, ENABLE);

    GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_RESET);
//--------------------------------------------------------------------------
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_StructInit(&DMA_InitStructure);
	DMA_DeInit(DMA1_Stream5);

	//-----------------------------
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI3->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
	DMA_Init(DMA1_Stream5,&DMA_InitStructure);


	DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);
	SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Tx, ENABLE);
//	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
}

void spi1_write_buf(uint16_t* pBuffer, uint16_t len)//перекинуть буфер через dma
{
	  DMA2_Stream3->M0AR= (uint32_t)pBuffer;
	  DMA2_Stream3->NDTR= len;

	  DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);

	  DMA_Cmd(DMA2_Stream3, ENABLE);

}

//void spi1_read_buf(uint16_t* pBuffer, uint16_t len)//перекинуть буфер через dma
//{
//	  DMA2_Stream3->M0AR= (uint32_t)pBuffer;
//	  DMA2_Stream3->NDTR= len;
//
//	//  DMA_ClearFlag(DMA1_FLAG_TC2);
//
//	  DMA_Cmd(DMA2_Stream3, ENABLE);
//}

void spi2_write_buf(uint16_t* pBuffer, uint16_t len)
{
	  DMA1_Stream4->M0AR= (uint32_t)pBuffer;
	  DMA1_Stream4->NDTR= len;

	  DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);

	  DMA_Cmd(DMA1_Stream4, ENABLE);
}

//void spi2_read_buf(uint16_t* pBuffer, uint16_t len)
//{
//	  DMA1_Stream4->M0AR= (uint32_t)pBuffer;
//	  DMA1_Stream4->NDTR= len;
//
//	//  DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
//
//	  DMA_Cmd(DMA1_Stream4, ENABLE);
//}

void spi3_write_buf(uint16_t* pBuffer, uint16_t len)
{
	  DMA1_Stream5->M0AR= (uint32_t)pBuffer;
	  DMA1_Stream5->NDTR= len;

	  DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);

	  DMA_Cmd(DMA1_Stream5, ENABLE);
}

static void spi1_task(void *pvParameters)//�
{
	uint8_t i=0,j=0;
	while(1)
	{
		for(i=0;i<IND_COMMAND_LEN;i++)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);

			if( xSemaphoreTake( xSPI_Buf_Mutex, portMAX_DELAY ) == pdTRUE )
			{
				 spi1_write_buf(&tab.buses[BUS_SPI_1].bus_buf[i][0],IND_SPI_BUS_1_NUM);

				 while(DMA_GetFlagStatus(DMA2_Stream3,DMA_FLAG_TCIF3)==RESET)
				 {
					 taskYIELD();
				 }
				 DMA_Cmd(DMA2_Stream3, DISABLE);
				 DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);

				 while(SPI1->SR & SPI_SR_BSY)
				 {
					 taskYIELD();
				 }


//				for(j=0;j<IND_SPI_BUS_1_NUM;j++)
//				{
//					SPI_I2S_SendData(SPI1,tab.buses[BUS_SPI_1].bus_buf[i][j]);
//
//
//				 while(SPI1->SR & SPI_SR_BSY)
//				 {
//					 taskYIELD();
//				  }
//				}

				 xSemaphoreGive( xSPI_Buf_Mutex );
			}
			vTaskDelay(1);
			GPIO_WriteBit(GPIOA, GPIO_Pin_4,1);
			taskYIELD();
			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);
			//vTaskDelay(1000);
		}
		vTaskDelay(50);
	}
}


static void spi2_task(void *pvParameters)
{
	uint8_t i=0;
	while(1)
	{
		for(i=0;i<IND_COMMAND_LEN;i++)
		{
			GPIO_WriteBit(GPIOB, GPIO_Pin_11,0);
			if( xSemaphoreTake( xSPI_Buf_Mutex, portMAX_DELAY ) == pdTRUE )
			{
				spi2_write_buf(&tab.buses[BUS_SPI_2].bus_buf[i][0],IND_SPI_BUS_2_NUM);

				while(DMA_GetFlagStatus(DMA1_Stream4,DMA_FLAG_TCIF4)==RESET)
				{
					taskYIELD();
				}
				DMA_Cmd(DMA1_Stream4, DISABLE);
				DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);

				while(SPI2->SR & SPI_SR_BSY)
				{
					taskYIELD();
				}

				xSemaphoreGive( xSPI_Buf_Mutex );
			}

			GPIO_WriteBit(GPIOB, GPIO_Pin_11,1);
			taskYIELD();
			GPIO_WriteBit(GPIOB, GPIO_Pin_11,0);
		}
		vTaskDelay(50);
	}
}


static void spi3_task(void *pvParameters)
{
	uint8_t i=0;
	uint16_t test_buf[8]={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0xFFFF};
	while(1)
	{
		for(i=0;i<IND_COMMAND_LEN;i++)
		{
			GPIO_WriteBit(GPIOD, GPIO_Pin_0,0);
			if( xSemaphoreTake( xSPI_Buf_Mutex, portMAX_DELAY ) == pdTRUE )
			{
				spi3_write_buf(&tab.buses[BUS_SPI_3].bus_buf[i][0],IND_SPI_BUS_3_NUM);

				while(DMA_GetFlagStatus(DMA1_Stream5,DMA_FLAG_TCIF5)==RESET)
				{
					taskYIELD();
				}
				DMA_Cmd(DMA1_Stream5, DISABLE);
				DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);

				while(SPI3->SR & SPI_SR_BSY)
				{
					taskYIELD();
				}

				xSemaphoreGive( xSPI_Buf_Mutex );
			}

			GPIO_WriteBit(GPIOD, GPIO_Pin_0,1);
			taskYIELD();
			GPIO_WriteBit(GPIOD, GPIO_Pin_0,0);
		}

//		spi3_write_buf(&test_buf,8);
//		while(DMA_GetFlagStatus(DMA1_Stream5,DMA_FLAG_TCIF5)==RESET)
//		{
//			taskYIELD();
//		}
//		DMA_Cmd(DMA1_Stream5, DISABLE);
//		DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);
//
//		while(SPI3->SR & SPI_SR_BSY)
//		{
//			taskYIELD();
//		}

		vTaskDelay(50);
	}
}

