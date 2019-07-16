#include "stm32f10x.h"


#define SEND_BUF_SIZE 8200
u8 SendBuff[SEND_BUF_SIZE]; //�������ݻ�����

/******************���Ҳ��α�***********************/
#ifdef  Sine_WaveOutput_Enable 
         u16 SineWave_Value[256];       //�ú�����װ
#endif
 

void SineWave_Data( u16 cycle ,u16 *D);

/****************��ʼ������******************/
void SineWave_GPIO_Config(void)
{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��ʱ��
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //�������ģʽ
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //������� 
//    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 ; //ѡ������
//    GPIO_SetBits(GPIOA,GPIO_Pin_5)  ;   //�������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);      //��ʼ��

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //��ʼ������ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;//DAC channel1��channel2��Ӧ������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//��ʼ��DAC
/******************DAC��ʼ����*************************/
void SineWave_DAC_Config( void)
{
//    DAC_InitTypeDef            DAC_InitStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��DACʱ��
//     
//  /**************DAC�ṹ��ʼ��*******************/
//    DAC_StructInit(&DAC_InitStructure);    
//    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//����������
//    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable; //��ʹ���������
//    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC����Ϊ��ʱ��2����
//    DAC_Init(DAC_Channel_1, &DAC_InitStructure);//��ʼ��
//    DAC_Cmd(DAC_Channel_1, ENABLE);    //ʹ��DAC��ͨ��1
//    DAC_DMACmd(DAC_Channel_1, ENABLE); //ʹ��DACͨ��1��DMA  

	DAC_InitTypeDef DAC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��ʼ��DAC��ʱ��

	DAC_StructInit(&DAC_InitStructure);
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//ָ��DAC1�Ĵ�����ʱ��TIM2
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//�޲��β���
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable; //������DAC�������
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);//��ʼ��DAC channel1

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;//ָ��DAC2�Ĵ�����ʱ��TIM6
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);//��ʼ��DAC channel2

	DAC_Cmd(DAC_Channel_1, ENABLE); //ʹ��DAC channel1
	DAC_Cmd(DAC_Channel_2, ENABLE); //ʹ��DAC channel2

	DAC_DMACmd(DAC_Channel_1, ENABLE); //ʹ��DAC Channel1��DMA
	DAC_DMACmd(DAC_Channel_2, ENABLE); //ʹ��DAC Channel2��DMA
}

//��ʱ������
/*********��ʱ����ʼ��************/
void SineWave_TIM_Config(u32 Wave1_Fre)
{
//    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//��ʱ��
//	
//    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;     //��Ԥ��Ƶ
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //����Ƶ<br>����TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
//    TIM_TimeBaseStructure.TIM_Period = Wave1_Fre;//�������Ƶ��
//    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//����TIME�������Ϊ����ģʽ

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM6, ENABLE);//��ʼ����ʱ��2��6��ʱ��

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = Wave1_Fre; //���Ҳ�1Ƶ������
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; //û��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//������
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period = Wave1_Fre; //���Ҳ�2Ƶ������
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//����TIM2�������
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);//����TIM6�������
}




	



