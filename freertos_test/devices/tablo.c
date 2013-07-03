#include "tablo.h"

struct tablo tab;//структура табло
uint8_t uart_buf[0xFF]={0x0};
struct indicator indicators_bus1[IND_SPI_BUS_1_NUM];
struct indicator indicators_bus2[IND_SPI_BUS_2_NUM];
struct indicator indicators_bus3[IND_SPI_BUS_3_NUM];

uint16_t spi1_bus_buf[IND_COMMAND_LEN][IND_SPI_BUS_1_NUM];//буфер шины 1
uint16_t spi2_bus_buf[IND_COMMAND_LEN][IND_SPI_BUS_2_NUM];//буфер шины 2
uint16_t spi3_bus_buf[IND_COMMAND_LEN][IND_SPI_BUS_3_NUM];//буфер шины 3



uint8_t tablo_devices_init(void)//инициализация буферов устройств табло
{
	uint8_t error=0;

	tab.uart_buf=&uart_buf;
	tab.buses[BUS_SPI_1].indicators=&indicators_bus1;
	tab.buses[BUS_SPI_2].indicators=&indicators_bus2;
	tab.buses[BUS_SPI_3].indicators=&indicators_bus3;

	tab.buses[BUS_SPI_1].bus_buf=&spi1_bus_buf;
	tab.buses[BUS_SPI_2].bus_buf=&spi2_bus_buf;
	tab.buses[BUS_SPI_3].bus_buf=&spi3_bus_buf;


	return error;
}
