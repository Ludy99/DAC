#include "time.h"
extern unsigned int wave_change;

//ռ�ձ�=CCR1/TIM_Period+1
//ʱ��Ƶ��=72/��IM_Prescaler+1��    Ҳ����˵1S�����Ĵ���Ϊʱ�ӷ�Ƶ
//��ʱ����ʱ��ΪT=TIM_Period/ʱ��Ƶ��
//TIM_Period�������6

void TIM2_Configuration(void)
{ 	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_DeInit(TIM2);	 //����TIMX��ȱʡֵ
	TIM_InternalClockConfig(TIM2);	//����TIMX���ڲ�ʱ�� 
	TIM_TimeBaseStructure.TIM_Period =wave_change;//�Ƚ�ֵ                
	TIM_TimeBaseStructure.TIM_Prescaler = 2-1;//��Ƶֵ       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ʱ�ӷ�Ƶ     
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ ���ϼ���  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);      //���TIMX�Ĵ������־λ

}



//void NVIC_Config(void)	  //�жϹ����ʼ��
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//ѡ���жϷ���1
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //ѡ��TIM2���ж�ͨ�� 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռʽ�ж����ȼ�����Ϊ0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //��Ӧʽ�ж����ȼ�����Ϊ0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	  //ʹ���ж�
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


