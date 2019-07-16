#ifndef __SINE_WAVE1_H
#define __SINE_WAVE1_H
#include "stm32f10x.h"


 extern u16 dacval;
void SineWave1_Init(u16 Wave1_Fre);
void SineWave_Data( u16 cycle ,u16 *D);
void SineWave_GPIO_Config(void);
void SineWave_DAC_Config( void);
 void SineWave_DMA_Config(void);

#endif


