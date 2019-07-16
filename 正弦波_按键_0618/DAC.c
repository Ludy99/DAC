#include "dac.h"
#include "time.h"
 
//u8 Idx=0;

void GPIO_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void DAC_Configuration()
{
  	DAC_InitTypeDef        DAC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_4095;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

	DAC_Init(DAC_Channel_1,  &DAC_InitStructure);
	DAC_DMACmd(DAC_Channel_1, ENABLE); 
	DAC_Cmd(DAC_Channel_1, ENABLE);
}



