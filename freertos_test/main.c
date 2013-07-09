#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include <misc.h>

#include <stdio.h>
#include <math.h>

//FreeRTOS:

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


#include "tablo_parser.h"
#include "spi_bus.h"
#include "tablo.h"
#include "proto.h"

 extern struct tablo tab;//структура табло
static void SPI_Test(void *pvParameters);


static void SPI_Test(void *pvParameters)
{
	uint8_t i=0;

	while(1)
	{
		for(i=0;i<IND_COMMAND_LEN;i++)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);
			spi1_write_buf(&tab.buses[BUS_SPI_1].bus_buf[i][0],1);

			while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);
			 DMA_Cmd(DMA1_Channel3, DISABLE);


			while(SPI1->SR & SPI_SR_BSY);


			GPIO_WriteBit(GPIOA, GPIO_Pin_4,1);

			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);
			//------------------------------------------------
			GPIO_WriteBit(GPIOB, GPIO_Pin_12,0);

			spi2_write_buf(&tab.buses[BUS_SPI_2].bus_buf[i][0],1);

			while(DMA_GetFlagStatus(DMA1_FLAG_TC5)==RESET);
			DMA_Cmd(DMA1_Channel5, DISABLE);

			while(SPI2->SR & SPI_SR_BSY);


			GPIO_WriteBit(GPIOB, GPIO_Pin_12,1);

			GPIO_WriteBit(GPIOB, GPIO_Pin_12,0);
        }
		vTaskDelay(50);
	}
}
//------------------------------------------------------------------

int main(void)
{
	SystemInit();

	spi1_config();
	spi2_config();
//	spi3_config();
//
	tablo_devices_init();

    Proto_Init();

    xTaskCreate(SPI_Test,(signed char*)"SPI",64,NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    while(1);
}
