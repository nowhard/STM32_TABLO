#ifndef TABLO_H
#define TABLO_H

#include "stm32f10x.h"
#include "spi_bus.h"
#include "buzzer.h"

#define UART_BUF_LEN			0xC0
#define TABLO_PROTO_BUF_LEN		0xC0


#define DISCR_OUT_ON	0x1
#define DISCR_OUT_OFF	0x0

struct tablo{//основная структура устройства
	struct bus buses[BUS_NUM];//создаем шиины табло
	struct indicator indicators[IND_ALL_NUM];//индикаторы устройства
	struct buzzer buz;//структура гудка
	uint8_t discr_outputs[4];//дискретные (релейные выходы)
	uint8_t uart_buf[UART_BUF_LEN];//буфер UART
	uint8_t tablo_proto_buf[TABLO_PROTO_BUF_LEN];//кадр табло
};

void tablo_indicator_struct_init(void);//инициализация структур индикаторов
uint8_t tablo_devices_init(void);//инициализация буферов устройств табло

#endif
