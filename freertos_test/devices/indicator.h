#ifndef INDICATOR_H
#define INDICATOR_H

#include "stm32f4xx.h"

struct indicator{
    //uint16_t number;//
    uint16_t number_in_bus;//
    uint16_t bus;//
    uint16_t type;//
    uint16_t character_num;//
    uint16_t brightness;//
    uint16_t decode_mode;//
    uint16_t scan_limit;//
    uint16_t shutdown;//
    uint16_t display_test;//

    uint8_t renew_data;//���������� ������� ��������� �� ���������
};

#define IND_BRIGHTNESS      0xA00 //0-15
#define IND_DECODE          0x900//
    #define IND_DECODE_ON       0xFF
    #define IND_DECODE_OFF      0x0
#define IND_SCAN_LIMIT      0xB00//0-8
#define IND_SHUTDOWN        0xC00
    #define IND_SHUTDOWN_ON     0x0
    #define IND_SHUTDOWN_OFF    0x1
#define IND_DISPLAY_TEST    0xF00
    #define IND_DISPLAY_TEST_ON     0x1
    #define IND_DISPLAY_TEST_OFF    0x0


#define IND_NEW_DATA_FALSE	0
#define IND_NEW_DATA_TRUE	1
/*
Типы индикаторов
  */
#define IND_TYPE_NONE       0x0//
#define IND_TYPE_SEGMENT    0x1//
#define IND_TYPE_LINE       0x2//
#define IND_TYPE_ARC        0x3//

#define IND_COMMAND_LEN		13//

#define IND_ALL_NUM			20//

#define IND_SPI_BUS_1_NUM	6 //
#define IND_SPI_BUS_2_NUM	6
#define IND_SPI_BUS_3_NUM	6

uint8_t indicators_init(void);//





#endif
