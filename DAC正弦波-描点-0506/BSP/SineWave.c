#include "SineWave.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/*************************************************************
Function : SineWave_GPIO_Config
Description: ��������
Input : none
return : none
*************************************************************/
static void SineWave_GPIO_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //��ʼ������ʱ��

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;//DAC channel1��channel2��Ӧ������
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);
}



#define _800Hz (u16)(72000000/sizeof(Sine12bit)*2/50) //800Hz
#define _1600Hz (u16)(72000000/sizeof(Sine12bit)*2/1600) //1600Hz
const u16 Sine12bit[256] = { //���Ҳ����
2048, 2098, 2148, 2198, 2248, 2298, 2348, 2398, 2447, 2496,
2545, 2594, 2642, 2690, 2737, 2785, 2831, 2877, 2923, 2968,
3013, 3057, 3100, 3143, 3185, 3227, 3267, 3307, 3347, 3385,
3423, 3460, 3496, 3531, 3565, 3598, 3631, 3662, 3692, 3722,
3750, 3778, 3804, 3829, 3854, 3877, 3899, 3920, 3940, 3958,
3976, 3992, 4007, 4021, 4034, 4046, 4056, 4065, 4073, 4080,
4086, 4090, 4093, 4095, 4095, 4095, 4093, 4090, 4086, 4080,
4073, 4065, 4056, 4046, 4034, 4021, 4007, 3992, 3976, 3958,
3940, 3920, 3899, 3877, 3854, 3829, 3804, 3778, 3750, 3722,
3692, 3662, 3631, 3598, 3565, 3531, 3496, 3460, 3423, 3385,
3347, 3307, 3267, 3227, 3185, 3143, 3100, 3057, 3013, 2968,
2923, 2877, 2831, 2785, 2737, 2690, 2642, 2594, 2545, 2496,
2447, 2398, 2348, 2298, 2248, 2198, 2148, 2098, 2047, 1997,
1947, 1897, 1847, 1797, 1747, 1697, 1648, 1599, 1550, 1501,
1453, 1405, 1358, 1310, 1264, 1218, 1172, 1127, 1082, 1038,
995, 952, 910, 868, 828, 788, 748, 710, 672, 635,
599, 564, 530, 497, 464, 433, 403, 373, 345, 317,
291, 266, 241, 218, 196, 175, 155, 137, 119, 103,
88, 74, 61, 49, 39, 30, 22, 15, 9, 5,
2, 0, 0, 0, 2, 5, 9, 15, 22, 30,
39, 49, 61, 74, 88, 103, 119, 137, 155, 175,
196, 218, 241, 266, 291, 317, 345, 373, 403, 433,
464, 497, 530, 564, 599, 635, 672, 710, 748, 788,
828, 868, 910, 952, 995, 1038, 1082, 1127, 1172, 1218,
1264, 1310, 1358, 1405, 1453, 1501, 1550, 1599, 1648, 1697,
1747, 1797, 1847, 1897, 1947, 1997 };

//const u16 Sine12bit[32] = { //�������
// 2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
// 3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
// 599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};
 
/*************************************************************
Function : SineWave_TIM_Config
Description: ��ʱ������
Input : none
return : none
*************************************************************/
static void SineWave_TIM_Config(void)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM6, ENABLE);//��ʼ����ʱ��2��6��ʱ��

TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
TIM_TimeBaseStructure.TIM_Period = _800Hz; //���Ҳ�1Ƶ������
TIM_TimeBaseStructure.TIM_Prescaler = 0x0; //û��Ԥ��Ƶ
TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //ʱ�Ӳ���Ƶ
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//������
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

TIM_TimeBaseStructure.TIM_Period = _1600Hz; //���Ҳ�2Ƶ������
TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//����TIM2�������
TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);//����TIM6�������
}




/*************************************************************
Function : SineWave_DAC_Config
Description: DAC����
Input : none
return : none
*************************************************************/
static void SineWave_DAC_Config(void)
{
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

#define DAC_DHR12R1 0x40007408 //����DACͨ��1�Ļ���ַ
#define DAC_DHR12R2 0x40007414 //����DACͨ��2�Ļ���ַ
/*************************************************************
Function : SineWave_DMA_Config
Description: DMA����
Input : none
return : none
*************************************************************/
static void SineWave_DMA_Config(void)
{
DMA_InitTypeDef DMA_InitStructure;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//��ʼ��DMA2��ʱ��

DMA_DeInit(DMA2_Channel3); //��DMA���ó�Ĭ��ֵ
DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1;//ָ��DMA2ͨ��3��Ŀ���ַΪDAC1_DHR12R1
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Sine12bit;//ָ��DMA��Դ��ַΪ����Sine12bit
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//������Ϊ���ݴ����Ŀ�ĵ�
DMA_InitStructure.DMA_BufferSize = sizeof(Sine12bit)/2;//DMA��������С
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�������ַ��������
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݿ��Ϊ����
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�ڴ����ݿ��Ϊ����
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//������ѭ������ģʽ�����ݴ�����Ϊ0ʱ���Զ��ָ����ó�ֵ
DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//�ǳ������ȼ�
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//ͨ��δ�����ó��ڴ浽�ڴ�ģʽ����ѭ��ģʽ���
DMA_Init(DMA2_Channel3, &DMA_InitStructure);//��ʼ��DMA

DMA_DeInit(DMA2_Channel4);
DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2;//ָ��DMA2ͨ��3��Ŀ���ַΪDAC2_DHR12R2
DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
DMA_Init(DMA2_Channel4, &DMA_InitStructure);

DMA_Cmd(DMA2_Channel3, ENABLE); //ʹ��DMA��channel3
DMA_Cmd(DMA2_Channel4, ENABLE); //ʹ��DMA��channel4
}




/*************************************************************
Function : SineWave_Init();
Description: ���Ҳ���ʼ��
Input : none
return : none
*************************************************************/
void SineWave_Init(void)
{
SineWave_GPIO_Config(); //��������
SineWave_TIM_Config(); //���ö�ʱ��
SineWave_DAC_Config(); //����DAC
SineWave_DMA_Config(); //����DMA

TIM_Cmd(TIM2, ENABLE); //��TIM2
TIM_Cmd(TIM6, ENABLE); //��TIM6
}

