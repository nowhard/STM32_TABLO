#ifndef WATCHDOG_H
#define WATCHDOG_H
#include "stm32f4xx.h"

#define TASK_NUM	6//количество задач, кроме задачи ватчдога , в системе

enum
{
	SPI_TASK_1=0,
	SPI_TASK_2,
	SPI_TASK_3,
	PROTO_TASK,
	KEYBOARD_TASK,
	BUZZER_TASK
};

enum
{
	TASK_ACTIVE=0,
	TASK_IDLE
};

struct task_watch
{
	uint32_t counter;
	uint8_t  task_status;
};

void Watchdog_Init(void);

#endif
