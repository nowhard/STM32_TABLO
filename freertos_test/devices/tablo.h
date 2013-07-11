#ifndef TABLO_H
#define TABLO_H

#include "stm32f10x.h"
#include "spi_bus.h"

#define UART_BUF_LEN			0xC0
#define TABLO_PROTO_BUF_LEN		0xC0

struct tablo{//основная структура устройства
	struct bus buses[BUS_NUM];//создаем шиины табло
	struct indicator indicators[IND_ALL_NUM];//индикаторы устройства
	uint8_t uart_buf[UART_BUF_LEN];//буфер UART
	uint8_t tablo_proto_buf[TABLO_PROTO_BUF_LEN];//кадр табло
};

void tablo_indicator_struct_init(void);//инициализация структур индикаторов
uint8_t tablo_devices_init(void);//инициализация буферов устройств табло

#endif
