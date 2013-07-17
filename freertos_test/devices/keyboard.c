#include "keyboard.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include <misc.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"



void keyboard_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure port -------------------------------*/
    GPIO_InitStructure.GPIO_Pin   = KEY_X1|KEY_X2|KEY_X3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(PORT_X, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = KEY_Y1|KEY_Y2|KEY_Y3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    GPIO_Init(PORT_Y, &GPIO_InitStructure);

    GPIO_WriteBit(PORT_X, KEY_X1,0);
    GPIO_WriteBit(PORT_X, KEY_X2,0);
    GPIO_WriteBit(PORT_X, KEY_X3,0);

    GPIO_WriteBit(PORT_Y, KEY_Y1,0);
    GPIO_WriteBit(PORT_Y, KEY_Y2,0);
    GPIO_WriteBit(PORT_Y, KEY_Y3,0);

    xTaskCreate(keyboard_task,(signed char*)"KEYBOARD",64,NULL, tskIDLE_PRIORITY + 1, NULL);
}
void keyboard_task(void *pvParameters )
{
	uint8_t key_read_1=0,key_read_2=0;
	while(1)
	{
		vTaskDelay(50);

		key_read_1=0x0;

		GPIO_WriteBit(PORT_X, KEY_X1,1);
		GPIO_WriteBit(PORT_X, KEY_X2,0);
		GPIO_WriteBit(PORT_X, KEY_X3,0);

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y1))
		{
			key_read_1=KEY_X1|(KEY_Y1<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y2))
		{
			key_read_1=KEY_X1|(KEY_Y2<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y3))
		{
			key_read_1=KEY_X1|(KEY_Y3<<4);
		}

		GPIO_WriteBit(PORT_X, KEY_X1,0);
		GPIO_WriteBit(PORT_X, KEY_X2,1);
		GPIO_WriteBit(PORT_X, KEY_X3,0);

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y1))
		{
			key_read_1=KEY_X2|(KEY_Y1<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y2))
		{
			key_read_1=KEY_X2|(KEY_Y2<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y3))
		{
			key_read_1=KEY_X2|(KEY_Y3<<4);
		}

		GPIO_WriteBit(PORT_X, KEY_X1,0);
		GPIO_WriteBit(PORT_X, KEY_X2,0);
		GPIO_WriteBit(PORT_X, KEY_X3,1);

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y1))
		{
			key_read_1=KEY_X3|(KEY_Y1<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y2))
		{
			key_read_1=KEY_X3|(KEY_Y2<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y3))
		{
			key_read_1=KEY_X3|(KEY_Y3<<4);
		}

		GPIO_WriteBit(PORT_X, KEY_X1,0);
		GPIO_WriteBit(PORT_X, KEY_X2,0);
		GPIO_WriteBit(PORT_X, KEY_X3,0);

		vTaskDelay(50);

		key_read_2=0x0;

		GPIO_WriteBit(PORT_X, KEY_X1,1);
		GPIO_WriteBit(PORT_X, KEY_X2,0);
		GPIO_WriteBit(PORT_X, KEY_X3,0);

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y1))
		{
			key_read_2=KEY_X1|(KEY_Y1<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y2))
		{
			key_read_2=KEY_X1|(KEY_Y2<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y3))
		{
			key_read_2=KEY_X1|(KEY_Y3<<4);
		}

		GPIO_WriteBit(PORT_X, KEY_X1,0);
		GPIO_WriteBit(PORT_X, KEY_X2,1);
		GPIO_WriteBit(PORT_X, KEY_X3,0);

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y1))
		{
			key_read_2=KEY_X2|(KEY_Y1<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y2))
		{
			key_read_2=KEY_X2|(KEY_Y2<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y3))
		{
			key_read_2=KEY_X2|(KEY_Y3<<4);
		}

		GPIO_WriteBit(PORT_X, KEY_X1,0);
		GPIO_WriteBit(PORT_X, KEY_X2,0);
		GPIO_WriteBit(PORT_X, KEY_X3,1);

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y1))
		{
			key_read_2=KEY_X3|(KEY_Y1<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y2))
		{
			key_read_2=KEY_X3|(KEY_Y2<<4);
		}

		if(GPIO_ReadInputDataBit(PORT_Y,KEY_Y3))
		{
			key_read_2=KEY_X3|(KEY_Y3<<4);
		}

		GPIO_WriteBit(PORT_X, KEY_X1,0);
		GPIO_WriteBit(PORT_X, KEY_X2,0);
		GPIO_WriteBit(PORT_X, KEY_X3,0);


		if((key_read_1==key_read_2) && (key_read_1!=0x0))//проверка на дребезг
		{
			key_read_2=0x0;
		}

	}
}
