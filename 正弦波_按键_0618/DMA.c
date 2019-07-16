#include"DMA.h"

#define DAC_DHR12RD_Address      0x40007408

u32 Sine12bit[32] = {2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909, 
                      599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};


//u32 Sine12bit[32] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,0, 
//                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
//                      0, 0, 0, 0, 0, 4095, 4095, 4095, 4095, 4095, 4095, 4095};
//


void MDA_Configuration(void)
{
	DMA_InitTypeDef            DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	DMA_DeInit(DMA2_Channel3);//�� DMA��ͨ�� x �Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_Address;//�ò������Զ��� DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&Sine12bit;//���Զ��� DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//������Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = 32;//DMA_BufferSize ���Զ���ָ�� DMAͨ����DMA����Ĵ�С����λΪ���ݵ�λ������
	                               //���䷽�����ݵ�λ���ڽṹ�в��� DMA_PeripheralDataSize ���߲��� DMA_MemoryDataSize ��ֵ�� 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ������� 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ������� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //�������ݿ��Ϊ 32 λ 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;//�ڴ����ݿ��Ϊ 32 λ 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//������ѭ������ģʽ 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ�� xӵ�и����ȼ� 	     
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //ʹ�� DMAͨ�����ڴ浽�ڴ洫��	   
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);	
	/* Enable DMA2 Channel4 */

	DMA_Cmd(DMA2_Channel3, ENABLE);   	
}


