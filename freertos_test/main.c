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

 extern struct tablo tab;//структура табло
static void SPI_Test(void *pvParameters);

uint16_t buf={0xC01,0x9FF,0xF00,0xA0E,0xB05,0x101,0x201,0x301,0x401,0x501};

static void SPI_Test(void *pvParameters)
{
	uint8_t i=0,j=0;

	while(1)
	{


		for(i=0;i<IND_COMMAND_LEN;i++)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);

			//---------------------
//			tab.buses[BUS_SPI_1].bus_buf[0][0]=0xC01;
//			tab.buses[BUS_SPI_1].bus_buf[1][0]=0x9FF;
//			tab.buses[BUS_SPI_1].bus_buf[2][0]=0xF00;
//			tab.buses[BUS_SPI_1].bus_buf[3][0]=0xA0E;
//			tab.buses[BUS_SPI_1].bus_buf[4][0]=0xB05;
//			tab.buses[BUS_SPI_1].bus_buf[5][0]=0x101;
//			tab.buses[BUS_SPI_1].bus_buf[6][0]=0x201;
//			tab.buses[BUS_SPI_1].bus_buf[7][0]=0x301;
//			tab.buses[BUS_SPI_1].bus_buf[8][0]=0x401;
//			tab.buses[BUS_SPI_1].bus_buf[9][0]=0x501;
//			tab.buses[BUS_SPI_1].bus_buf[10][0]=0x601;
//			tab.buses[BUS_SPI_1].bus_buf[11][0]=0x701;
//			tab.buses[BUS_SPI_1].bus_buf[12][0]=0x801;

			//---------------------


			spi1_write_buf(&tab.buses[BUS_SPI_1].bus_buf[i][0],1);
			//_start_spi_dma(&display_buf[i][0],2);


			while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);
			 DMA_Cmd(DMA1_Channel3, DISABLE);
			//DMA_ClearFlag(DMA1_FLAG_TC3);

			while(SPI1->SR & SPI_SR_BSY);


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

	spi1_config();
//	spi2_config();
//	spi3_config();
//
	tablo_devices_init();

    Proto_Init();


    xTaskCreate(SPI_Test,(signed char*)"SPI",64,NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    while(1);
}
