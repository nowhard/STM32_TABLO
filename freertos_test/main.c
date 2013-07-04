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
#include "spi_bus.h"
#include "tablo.h"
#include "proto.h"


static void SPI_Test(void *pvParameters);

static void SPI_Test(void *pvParameters)
{
//	uint8_t i=0,j=0;
//
//	while(1)
//	{
//		tablo_proto_parser(&tab_proto_buf);
//
//		for(i=0;i<INDICATOR_BUF_LEN;i++)
//		{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);
//
//
//
//			_start_spi_dma(&display_buf[i][0],2);
//			while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);
//			 DMA_Cmd(DMA1_Channel3, DISABLE);
//			//DMA_ClearFlag(DMA1_FLAG_TC3);
//
//			while(SPI1->SR & SPI_SR_BSY);
//
//
//			GPIO_WriteBit(GPIOA, GPIO_Pin_4,1);
//
//			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);
//        }
//		vTaskDelay(50);
//	}
}
//------------------------------------------------------------------

int main(void)
{

	SystemInit();

//	spi1_config();
//	spi2_config();
//	spi3_config();
//
//	tablo_devices_init();

    Proto_Init();


//    xTaskCreate(SPI_Test,(signed char*)"SPI",256,NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    while(1);
}
