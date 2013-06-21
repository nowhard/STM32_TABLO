#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include <misc.h>

#include <stdio.h>
#include <math.h>

//������� �� FreeRTOS:

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


#include "tablo_parser.h"


static void SPI_Test(void *pvParameters);
//-----------------------------------------------------------------
unsigned char buf[]={0x3A,0x88 ,0x5B ,0x00 ,'r' ,'L' ,0x2E ,'O' ,0x5D ,0x5B ,0x01 ,0x37 ,0x37 ,0x2E ,0x37 ,0x5D ,0x5B ,0x02 ,0x38 ,0x38 ,0x2E ,0x38 ,0x5D ,0x5B ,0x03 ,0x39 ,0x39 ,0x2E ,0x39 ,0x5D ,0x5B ,0x04 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x05 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x06 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x07 ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x08 ,0x32 ,0x32 ,0x2E ,0x32 ,0x32 ,0x32 ,0x5D ,0x5B ,0x0A ,0x32 ,0x2E ,0x32 ,0x32 ,0x32 ,0x5D ,0x5B ,0x0B ,0x32 ,0x32 ,0x2E ,0x32 ,0x5D ,0x5B ,0x0C ,0x32 ,0x2E ,0x32 ,0x32 ,0x32 ,0x5D ,0x5B ,0x0D ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x0E ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x0F ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x10 ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x12 ,0x00 ,0x10 ,0x00 ,0x1F ,0x5D ,0x5B ,0x13 ,0x00 ,0x10 ,0x00 ,0x1E ,0x5D ,0x5B ,0x2A ,0x0F ,0x5D};
extern uint16_t display_buf[INDICATOR_BUF_LEN][INDICATORS_NUM];//
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
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    //SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);



    /* Enable SPI1 */
    SPI_CalculateCRC(SPI1, DISABLE);
    SPI_SSOutputCmd(SPI1, ENABLE);
    SPI_Cmd(SPI1, ENABLE);

    GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);

    SPI_DataSizeConfig(SPI1,SPI_DataSize_16b);

}
//-----------------------------------------------------------------

//------------------------------------------------
static void SPI_Test(void *pvParameters)
{
	//#define BufferSize 10
	#define CS_DELAY	200
//	uint16_t SPI1_Buffer_Tx[BufferSize] ={0xC01,0x9FF,0xF00,0xA0E,0xB05,0x101,0x201,0x301,0x401,0x501};
//	uint8_t Tx_Idx = 0;
	uint16_t delay=CS_DELAY;

	uint8_t i=0,j=0;

	while(1)
	{
		//GPIO_WriteBit(GPIOC, GPIO_Pin_9, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9));//мигаем светодиодом
//		Tx_Idx=0;
//		uint8_t i=0;
//

		tablo_proto_parser(&buf);

//		while (Tx_Idx < BufferSize)
//        {
        /* Send SPI1 data */

		for(i=0;i<INDICATOR_BUF_LEN;i++)
		{

			for(j=0;j<2/*INDICATORS_NUM*/;j++)
			{
				GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);


				SPI_I2S_SendData(SPI1, display_buf[i][j]);
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);



			}
			while(delay)
			{
				delay--;
			}
			delay=CS_DELAY;

			GPIO_WriteBit(GPIOA, GPIO_Pin_4,1);
			while(delay)
			{
				delay--;
			}
			delay=CS_DELAY;

			GPIO_WriteBit(GPIOA, GPIO_Pin_4,0);

        }

//		for(i=5;i<BufferSize;i++)
//		{
//			SPI1_Buffer_Tx[i]=(SPI1_Buffer_Tx[i]&0xFF00)|((SPI1_Buffer_Tx[i]+1)&0xF);
//
//
//
////			if((SPI1_Buffer_Tx[i]&0xFF)>=0x80)
////			{
////				SPI1_Buffer_Tx[i]&=0xFF00;
////				SPI1_Buffer_Tx[i]|=0x1;
////			}
////			SPI1_Buffer_Tx[i]=(SPI1_Buffer_Tx[i]&0xFF00)|((SPI1_Buffer_Tx[i]<<1)&0xFF);
//
//		}
//		point++;
//		if(point==5)
//		{
//			point=0;
//		}
//		SPI1_Buffer_Tx[point+5]=(SPI1_Buffer_Tx[point+5]&0xFF00)|((SPI1_Buffer_Tx[point+5]|0x80)&0xFF);
////		SPI1_Buffer_Tx[8]++;


		vTaskDelay(500);
	}
}
//------------------------------------------------------------------

int main(void)
{

	SystemInit();
	//prvSetupHardware();


	SPI1_Config();
    //Proto_Init();

	tablo_indicator_struct_init();


    xTaskCreate(SPI_Test,(signed char*)"SPI",256,NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    while(1);
}
