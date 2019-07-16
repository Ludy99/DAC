#include "stm32f10x.h"


#define SEND_BUF_SIZE 8200
u8 SendBuff[SEND_BUF_SIZE]; //发送数据缓冲区

/******************正弦波形表***********************/
#ifdef  Sine_WaveOutput_Enable 
         u16 SineWave_Value[256];       //用函数封装
#endif
 

void SineWave_Data( u16 cycle ,u16 *D);

/****************初始化引脚******************/
void SineWave_GPIO_Config(void)
{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //开时钟
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //推挽输出模式
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //输出速率 
//    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 ; //选择引脚
//    GPIO_SetBits(GPIOA,GPIO_Pin_5)  ;   //拉高输出
//    GPIO_Init(GPIOA, &GPIO_InitStructure);      //初始化

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //初始化引脚时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;//DAC channel1和channel2对应的引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//初始化DAC
/******************DAC初始化ˉ*************************/
void SineWave_DAC_Config( void)
{
//    DAC_InitTypeDef            DAC_InitStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//开DAC时钟
//     
//  /**************DAC结构初始化*******************/
//    DAC_StructInit(&DAC_InitStructure);    
//    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//不产生波形
//    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable; //不使能输出缓存
//    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC触发为定时器2触发
//    DAC_Init(DAC_Channel_1, &DAC_InitStructure);//初始化
//    DAC_Cmd(DAC_Channel_1, ENABLE);    //使能DAC的通道1
//    DAC_DMACmd(DAC_Channel_1, ENABLE); //使能DAC通道1的DMA  

	DAC_InitTypeDef DAC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//初始化DAC的时钟

	DAC_StructInit(&DAC_InitStructure);
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//指定DAC1的触发定时器TIM2
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//无波形产生
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable; //不是能DAC输出缓冲
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);//初始化DAC channel1

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;//指定DAC2的触发定时器TIM6
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);//初始化DAC channel2

	DAC_Cmd(DAC_Channel_1, ENABLE); //使能DAC channel1
	DAC_Cmd(DAC_Channel_2, ENABLE); //使能DAC channel2

	DAC_DMACmd(DAC_Channel_1, ENABLE); //使能DAC Channel1的DMA
	DAC_DMACmd(DAC_Channel_2, ENABLE); //使能DAC Channel2的DMA
}

//定时器配置
/*********定时器初始化************/
void SineWave_TIM_Config(u32 Wave1_Fre)
{
//    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//开时钟
//	
//    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;     //不预分频
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //不分频<br>　　TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
//    TIM_TimeBaseStructure.TIM_Period = Wave1_Fre;//设置输出频率
//    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//设置TIME输出触发为更新模式

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM6, ENABLE);//初始化定时器2与6的时钟

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = Wave1_Fre; //正弦波1频率设置
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; //没有预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //时钟不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//增计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period = Wave1_Fre; //正弦波2频率设置
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//更新TIM2输出触发
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);//更新TIM6输出触发
}




	



