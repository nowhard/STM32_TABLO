#include "tablo.h"

struct tablo tab;//структура табло
//uint8_t uart_buf[0xFF]={0x0};
struct indicator indicators_bus1[IND_SPI_BUS_1_NUM];
struct indicator indicators_bus2[IND_SPI_BUS_2_NUM];
struct indicator indicators_bus3[IND_SPI_BUS_3_NUM];

uint16_t spi1_bus_buf[IND_COMMAND_LEN][IND_SPI_BUS_1_NUM];//буфер шины 1
uint16_t spi2_bus_buf[IND_COMMAND_LEN][IND_SPI_BUS_2_NUM];//буфер шины 2
uint16_t spi3_bus_buf[IND_COMMAND_LEN][IND_SPI_BUS_3_NUM];//буфер шины 3

void tablo_indicator_struct_init(void)//
{
	tab.buses[BUS_SPI_1].indicators_num=IND_SPI_BUS_1_NUM;//количество индикаторов на шине
	tab.buses[BUS_SPI_2].indicators_num=IND_SPI_BUS_2_NUM;
	tab.buses[BUS_SPI_3].indicators_num=IND_SPI_BUS_3_NUM;

	//tab.uart_buf=&uart_buf;

//--------------------------BUS_1-------------------------------------------------
	tab.buses[BUS_SPI_1].indicators[0].number=0;
	tab.buses[BUS_SPI_1].indicators[0].number_in_bus=0;
	tab.buses[BUS_SPI_1].indicators[0].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[0].character_num=5;
	tab.buses[BUS_SPI_1].indicators[0].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[0].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[0].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[0].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[0].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[1].number=1;
	tab.buses[BUS_SPI_1].indicators[1].number_in_bus=1;
	tab.buses[BUS_SPI_1].indicators[1].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[1].character_num=5;
	tab.buses[BUS_SPI_1].indicators[1].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[1].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[1].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[1].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[1].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[2].number=2;
	tab.buses[BUS_SPI_1].indicators[2].number_in_bus=2;
	tab.buses[BUS_SPI_1].indicators[2].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[2].character_num=5;
	tab.buses[BUS_SPI_1].indicators[2].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[2].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[2].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[2].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[2].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[3].number=3;
	tab.buses[BUS_SPI_1].indicators[3].number_in_bus=3;
	tab.buses[BUS_SPI_1].indicators[3].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[3].character_num=5;
	tab.buses[BUS_SPI_1].indicators[3].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[3].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[3].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[3].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[3].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[4].number=4;
	tab.buses[BUS_SPI_1].indicators[4].number_in_bus=4;
	tab.buses[BUS_SPI_1].indicators[4].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[4].character_num=5;
	tab.buses[BUS_SPI_1].indicators[4].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[4].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[4].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[4].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[4].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[5].number=5;
	tab.buses[BUS_SPI_1].indicators[5].number_in_bus=5;
	tab.buses[BUS_SPI_1].indicators[5].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[5].character_num=5;
	tab.buses[BUS_SPI_1].indicators[5].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[5].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[5].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[5].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[5].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[6].number=6;
	tab.buses[BUS_SPI_1].indicators[6].number_in_bus=6;
	tab.buses[BUS_SPI_1].indicators[6].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[6].character_num=5;
	tab.buses[BUS_SPI_1].indicators[6].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[6].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[6].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[6].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[6].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[7].number=7;
	tab.buses[BUS_SPI_1].indicators[7].number_in_bus=7;
	tab.buses[BUS_SPI_1].indicators[7].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[7].character_num=5;
	tab.buses[BUS_SPI_1].indicators[7].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[7].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[7].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[7].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[7].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[8].number=8;
	tab.buses[BUS_SPI_1].indicators[8].number_in_bus=8;
	tab.buses[BUS_SPI_1].indicators[8].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[8].character_num=5;
	tab.buses[BUS_SPI_1].indicators[8].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[8].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[8].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[8].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[8].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_1].indicators[9].number=9;
	tab.buses[BUS_SPI_1].indicators[9].number_in_bus=9;
	tab.buses[BUS_SPI_1].indicators[9].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_1].indicators[9].character_num=5;
	tab.buses[BUS_SPI_1].indicators[9].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_1].indicators[9].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_1].indicators[9].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_1].indicators[0].character_num-1);
	tab.buses[BUS_SPI_1].indicators[9].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_1].indicators[9].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;
//--------------------------------------BUS_2----------------------------------------------
	tab.buses[BUS_SPI_2].indicators[0].number=10;
	tab.buses[BUS_SPI_2].indicators[0].number_in_bus=0;
	tab.buses[BUS_SPI_2].indicators[0].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[0].character_num=5;
	tab.buses[BUS_SPI_2].indicators[0].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[0].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[0].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[0].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[0].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[1].number=11;
	tab.buses[BUS_SPI_2].indicators[1].number_in_bus=1;
	tab.buses[BUS_SPI_2].indicators[1].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[1].character_num=5;
	tab.buses[BUS_SPI_2].indicators[1].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[1].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[1].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[1].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[1].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[2].number=12;
	tab.buses[BUS_SPI_2].indicators[2].number_in_bus=2;
	tab.buses[BUS_SPI_2].indicators[2].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[2].character_num=5;
	tab.buses[BUS_SPI_2].indicators[2].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[2].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[2].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[2].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[2].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[3].number=13;
	tab.buses[BUS_SPI_2].indicators[3].number_in_bus=3;
	tab.buses[BUS_SPI_2].indicators[3].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[3].character_num=5;
	tab.buses[BUS_SPI_2].indicators[3].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[3].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[3].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[3].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[3].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[4].number=14;
	tab.buses[BUS_SPI_2].indicators[4].number_in_bus=4;
	tab.buses[BUS_SPI_2].indicators[4].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[4].character_num=5;
	tab.buses[BUS_SPI_2].indicators[4].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[4].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[4].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[4].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[4].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[5].number=15;
	tab.buses[BUS_SPI_2].indicators[5].number_in_bus=5;
	tab.buses[BUS_SPI_2].indicators[5].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[5].character_num=5;
	tab.buses[BUS_SPI_2].indicators[5].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[5].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[5].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[5].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[5].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[6].number=16;
	tab.buses[BUS_SPI_2].indicators[6].number_in_bus=6;
	tab.buses[BUS_SPI_2].indicators[6].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[6].character_num=5;
	tab.buses[BUS_SPI_2].indicators[6].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[6].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[6].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[6].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[6].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[7].number=17;
	tab.buses[BUS_SPI_2].indicators[7].number_in_bus=7;
	tab.buses[BUS_SPI_2].indicators[7].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[7].character_num=5;
	tab.buses[BUS_SPI_2].indicators[7].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[7].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[7].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[7].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[7].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[8].number=18;
	tab.buses[BUS_SPI_2].indicators[8].number_in_bus=8;
	tab.buses[BUS_SPI_2].indicators[8].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[8].character_num=5;
	tab.buses[BUS_SPI_2].indicators[8].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[8].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[8].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[8].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[8].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

	tab.buses[BUS_SPI_2].indicators[9].number=19;
	tab.buses[BUS_SPI_2].indicators[9].number_in_bus=9;
	tab.buses[BUS_SPI_2].indicators[9].type=IND_TYPE_SEGMENT;
	tab.buses[BUS_SPI_2].indicators[9].character_num=5;
	tab.buses[BUS_SPI_2].indicators[9].brightness=IND_BRIGHTNESS|0x9;
	tab.buses[BUS_SPI_2].indicators[9].decode_mode=IND_DECODE|IND_DECODE_OFF;
	tab.buses[BUS_SPI_2].indicators[9].scan_limit=IND_SCAN_LIMIT|(tab.buses[BUS_SPI_2].indicators[0].character_num-1);
	tab.buses[BUS_SPI_2].indicators[9].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
	tab.buses[BUS_SPI_2].indicators[9].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;
//--------------------------------------BUS_3----------------------------------------------
//...
}

uint8_t tablo_devices_init(void)//инициализация буферов устройств табло
{
	uint8_t error=0;

	tab.buses[BUS_SPI_1].indicators=&indicators_bus1;
	tab.buses[BUS_SPI_2].indicators=&indicators_bus2;
	tab.buses[BUS_SPI_3].indicators=&indicators_bus3;

	tab.buses[BUS_SPI_1].bus_buf=&spi1_bus_buf;
	tab.buses[BUS_SPI_2].bus_buf=&spi2_bus_buf;
	tab.buses[BUS_SPI_3].bus_buf=&spi3_bus_buf;


	return error;
}
