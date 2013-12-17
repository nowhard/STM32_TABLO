#include "indicator.h"
#include "tablo.h"
extern struct tablo tab;
uint8_t indicators_init(void)//
{
	uint8_t error=0;


	return error;
}

void Indicator_Blink_Handler(uint8_t bus)
{
	uint8_t i=0;
	static uint8_t counter;//2Hz blink
	static uint8_t blink_state;
	counter++;
	if(counter>=10)
	{
		for(i=0;i<IND_ALL_NUM;i++)
		{
			if(tab.indicators[i].bus==bus)
			{
				if(tab.indicators[i].blink==BLINK_TRUE)
				{

				}
			}
		}
		counter=0;
	}
}
