#ifndef BUZZER_H
#define BUZZER_H

#include "stm32f10x.h"

#define BUZZER_ON	0x1
#define BUZZER_OFF	0x0

#define BUZZER_EFFECT_0	0x0
#define BUZZER_EFFECT_1	0x1
#define BUZZER_EFFECT_2	0x2
#define BUZZER_EFFECT_3	0x3
#define BUZZER_EFFECT_4	0x4
#define BUZZER_EFFECT_5	0x5
#define BUZZER_EFFECT_6	0x6
#define BUZZER_EFFECT_7	0x7

struct buzzer{
	uint8_t buzzer_enable;//включить/выключить гудок
	uint8_t buzzer_effect;// тип звукового эффекта
};

#endif
