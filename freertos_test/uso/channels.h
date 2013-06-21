#ifndef CHANNELS_H
#define CHANNELS_H
#include <stm32f10x.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
//#include "stm32f10x_flash.h"
//#include "preferences.h"
#include "misc.h"
//---------------------------------------
#define CHANNEL_NUMBER	1//���������� �������
//---------------------------------------
#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#else
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif

#define DESC_BANK1_WRITE_START_ADDR  ((uint32_t)0x08020400)
#define DESC_BANK1_WRITE_END_ADDR    ((uint32_t)0x08020800)


#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08020000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x08020400)

#ifdef STM32F10X_XL
  #define BANK2_WRITE_START_ADDR   ((uint32_t)0x08088000)
  #define BANK2_WRITE_END_ADDR     ((uint32_t)0x0808C000)
#endif /* STM32F10X_XL */
//---------------------------------------
struct Channel
{
	unsigned char number ;	  	// ����� ������

	union
	{
		struct
		{
			unsigned char type;		  // ��� ������
			unsigned char modific;	  // ����������� ������
			unsigned char state_byte_1;	// ���� ��������� ������
			unsigned char state_byte_2;
		}set;

		unsigned long serialize;//��������������� ����� ���������
	} settings;

	unsigned long channel_data;		  // �������� ������
	unsigned long channel_data_calibrate;//�������� ������ �������������

	union
	{
		struct
		{
			unsigned char calibrate;//���� ��������������� ������


			float K;//
			float C;//y=kx+c


		} cal;
		unsigned long serialize[3];//��������������� ����� ���������
	} calibrate;

} ;
//---------------------------------------
void ChannelsInit(void);//������������� ��������� �������
//void Store_Channels_Data(void);//�������� ������ ������� � ����
//void Restore_Channels_Data(void);//����������� ������ ������� �� ����

//---------------------------------------
#endif
