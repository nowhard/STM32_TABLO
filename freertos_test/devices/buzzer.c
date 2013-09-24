#include "buzzer.h"

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

void buzzer_init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure port -------------------------------*/
    GPIO_InitStructure.GPIO_Pin   = BUZZER_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);


    GPIO_WriteBit(BUZZER_PORT, BUZZER_PIN,0);

    xTaskCreate(buzzer_task,(signed char*)"BUZZER",64,NULL, tskIDLE_PRIORITY + 1, NULL);
}
void buzzer_task(void *pvParameters )
{
	while(1)
	{
		if(tab.buz.buzzer_enable)
		{
			switch(tab.buz.buzzer_effect)
			{
				case BUZZER_EFFECT_0:
				{
					GPIO_WriteBit(BUZZER_PORT, BUZZER_PIN,1);
					vTaskDelay(500);
					GPIO_WriteBit(BUZZER_PORT, BUZZER_PIN,0);
					vTaskDelay(500);
				}
				break;

				case BUZZER_EFFECT_1:
				{
					GPIO_WriteBit(BUZZER_PORT, BUZZER_PIN,1);
					vTaskDelay(100);
					GPIO_WriteBit(BUZZER_PORT, BUZZER_PIN,0);
					vTaskDelay(200);
				}
				break;

				case BUZZER_EFFECT_2:
				{

				}
				break;

				case BUZZER_EFFECT_3:
				{

				}
				break;

				case BUZZER_EFFECT_4:
				{

				}
				break;

				case BUZZER_EFFECT_5:
				{

				}
				break;

				case BUZZER_EFFECT_6:
				{

				}
				break;

				case BUZZER_EFFECT_7:
				{

				}
				break;

				default:
				{

				}
			}
		}
	}
}
