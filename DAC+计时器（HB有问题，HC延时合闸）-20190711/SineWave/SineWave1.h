#ifndef __SINE_WAVE1_H
#define __SINE_WAVE1_H
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void SineWave_GPIO_Config(void);
void SineWave_DAC_Config( void);
void SineWave_TIM_Config(u32 Wave1_Fre);
void SineWave1_Init(void);
	
#endif


