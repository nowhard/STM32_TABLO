#include "spi_bus.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include <misc.h>

uint8_t spi_buses_init(void)//инициализация шин SPI и выделение памяти под буферы
{
	uint8_t error=0;


	return error;
}


void	spi1_config(void)//конфигурация аппаратных интерфейсов
{
//	uint32_t i=0;
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC | RCC_APB2Periph_SPI1, ENABLE);

	    GPIO_InitTypeDef GPIO_InitStructure;
	    SPI_InitTypeDef SPI_InitStructure;

	    /* Configure SPI1 pins: SCK, MISO and MOSI -------------------------------*/
	    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 |GPIO_Pin_7;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);

	    // MISO: ������������������ ����
	 /*   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);*/

	    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);

	    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
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
	  //  NVIC_InitTypeDef NVIC_InitStructure;

		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);


		DMA_StructInit(&DMA_InitStructure);

		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&SPI1->DR);
		//DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)txBuffer;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		//DMA_InitStructure.DMA_BufferSize = INDICATORS_NUM;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel3, &DMA_InitStructure);



		DMA_ClearFlag(DMA1_FLAG_TC3);

		// Enable DMA request
		SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
}

void	spi2_config(void)//
{

}

void 	spi3_config(void)//
{

}

void spi1_write_buf(uint16_t* pBuffer, uint16_t len)//перекинуть буфер через dma
{
	  DMA1_Channel3->CMAR = (uint32_t)pBuffer;
	  DMA1_Channel3->CNDTR = len;

	  DMA_ClearFlag(DMA1_FLAG_TC3);

	  DMA_Cmd(DMA1_Channel3, ENABLE);
}

void spi2_write_buf(uint16_t* pBuffer, uint16_t len)
{

}

void spi3_write_buf(uint16_t* pBuffer, uint16_t len)
{

}
