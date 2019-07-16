#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x_conf.h"

void TIM2_Int_Init(u32 Hz);
void  Set_Period(u32 value);
void Set_Sine12bit(float MAX,float MIN);
#endif


