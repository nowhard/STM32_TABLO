#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include <misc.h>

#include <stdio.h>
#include <math.h>

//������� �� FreeRTOS:

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


#include "tablo_parser.h"
#include "proto.h"


static void SPI_Test(void *pvParameters);
void _start_spi_dma(uint16_t* pBuffer, uint16_t NumToWrite);
//-----------------------------------------------------------------
unsigned char buf[]={0x3A,0x88 ,0x5B ,0x00 ,'r' ,'L' ,0x2E ,'O' ,0x5D ,0x5B ,0x01 ,0x37 ,0x37 ,0x2E ,0x37 ,0x5D ,0x5B ,0x02 ,0x38 ,0x38 ,0x2E ,0x38 ,0x5D ,0x5B ,0x03 ,0x39 ,0x39 ,0x2E ,0x39 ,0x5D ,0x5B ,0x04 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x05 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x06 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x07 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x08 ,0x32 ,0x32 ,0x2E ,0x32 ,0x32 ,0x32 ,0x5D ,0x5B ,0x0A ,0x32 ,0x2E ,0x32 ,0x32 ,0x32 ,0x5D ,0x5B ,0x0B ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x0C ,0x32 ,0x2E ,0x32 ,0x32 ,0x32 ,0x5D ,0x5B ,0x0D ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x0E ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x0F ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x10 ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x12 ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x13 ,0x00 ,0x10 ,0x00 ,0x1E ,0x5D ,0x5B ,0x2A ,0x0F ,0x5D};
extern uint16_t display_buf[INDICATOR_BUF_LEN][INDICATORS_NUM];//
extern uint8_t tab_proto_buf[256];
//-----------------------------------------------------------------
void SPI1_Config()
{
	uint32_t i=0;
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

        //DMA_Cmd(DMA1_Channel3, ENABLE);
//        DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
//
//        // Configure DMA1 Stream4 interrupt
//        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3;
//        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
//        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//        NVIC_Init(&NVIC_InitStructure);

        DMA_ClearFlag(DMA1_FLAG_TC3);

        // Enable DMA request
        SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);

 //---------------------------------------------------------------------------
    }

//-----------------------------------------------------------------
void _start_spi_dma(uint16_t* pBuffer, uint16_t NumToWrite) {
  // Setup buffer
  //DMA1_Channel2->CMAR = (uint32_t)pBuffer;
  DMA1_Channel3->CMAR = (uint32_t)pBuffer;
 // DMA1_Channel2->CNDTR = NumToWrite;
  DMA1_Channel3->CNDTR = NumToWrite;
  //
 // DMA_ClearFlag(DMA1_FLAG_GL2);
  //DMA_ClearFlag(DMA1_FLAG_GL3);
  DMA_ClearFlag(DMA1_FLAG_TC3);
  /* start */
 // DMA_Cmd(DMA1_Channel2, ENABLE);
  DMA_Cmd(DMA1_Channel3, ENABLE);
}
//------------------------------------------------
static void SPI_Test(void *pvParameters)
{
//
//	#define CS_DELAY	200
//
//	uint16_t delay=CS_DELAY;

	uint8_t i=0,j=0;


	while(1)
	{
		tablo_proto_parser(&tab_proto_buf);

		for(i=0;i<INDICATOR_BUF_LEN;i++)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);

//			for(j=0;j<2/*INDICATORS_NUM*/;j++)
//			{
//				//SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_TXE);
//				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//				SPI_I2S_SendData(SPI1, display_buf[i][j]);
//			}

			_start_spi_dma(&display_buf[i][0],20);
			while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);
			 DMA_Cmd(DMA1_Channel3, DISABLE);
			//DMA_ClearFlag(DMA1_FLAG_TC3);

			while(SPI1->SR & SPI_SR_BSY);
//			while(delay)
//			{
//				delay--;
//			}
//			delay=CS_DELAY;

			GPIO_WriteBit(GPIOA, GPIO_Pin_4,1);

			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);
        }

		vTaskDelay(50);
	}
}
//------------------------------------------------------------------

int main(void)
{

	SystemInit();
	//prvSetupHardware();


	SPI1_Config();
    Proto_Init();

	tablo_indicator_struct_init();


    xTaskCreate(SPI_Test,(signed char*)"SPI",256,NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    while(1);
}
