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


int main(void)
{
	SystemInit();

	spi1_config();
	spi2_config();
//	spi3_config();
//
	tablo_devices_init();

    Proto_Init();

    vTaskStartScheduler();

    while(1);
}
