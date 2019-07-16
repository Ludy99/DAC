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
	DMA_DeInit(DMA2_Channel3);//将 DMA的通道 x 寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_Address;//该参数用以定义 DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&Sine12bit;//用以定义 DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//外设作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = 32;//DMA_BufferSize 用以定义指定 DMA通道的DMA缓存的大小，单位为数据单位。根据
	                               //传输方向，数据单位等于结构中参数 DMA_PeripheralDataSize 或者参数 DMA_MemoryDataSize 的值。 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址寄存器不变 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//内存地址寄存器递增 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //外设数据宽度为 32 位 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;//内存数据宽度为 32 位 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//工作在循环缓存模式 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA通道 x拥有高优先级 	     
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //使能 DMA通道的内存到内存传输	   
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);	
	/* Enable DMA2 Channel4 */

	DMA_Cmd(DMA2_Channel3, ENABLE);   	
}


