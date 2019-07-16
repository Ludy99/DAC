#include "time.h"
extern unsigned int wave_change;

//占空比=CCR1/TIM_Period+1
//时钟频率=72/（IM_Prescaler+1）    也就是说1S内数的次数为时钟分频
//定时器的时间为T=TIM_Period/时钟频率
//TIM_Period必须大于6

void TIM2_Configuration(void)
{ 	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_DeInit(TIM2);	 //重设TIMX的缺省值
	TIM_InternalClockConfig(TIM2);	//设置TIMX的内部时钟 
	TIM_TimeBaseStructure.TIM_Period =wave_change;//比较值                
	TIM_TimeBaseStructure.TIM_Prescaler = 2-1;//分频值       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//时钟分频     
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数模式 向上计数  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);      //清除TIMX的待处理标志位

}



//void NVIC_Config(void)	  //中断管理初始化
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//选择中断分组1
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //选择TIM2的中断通道 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占式中断优先级设置为0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应式中断优先级设置为0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	  //使能中断
//	NVIC_Init(&NVIC_InitStructure);
//
//}

//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//	{
//		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
//		wave_change = wave_change+1;
//		if(wave_change == 4095)
//		{
//			wave_change = 0;
//		}
//	}
//}


