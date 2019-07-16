#include "key.h"
#include "dac.h"
#include "DMA.h"
#include "time.h"
#include "delay.h"
#define	key4		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)
#define	key5		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)
#define	key3		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define	key2		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
unsigned int wave_change = 7;

void led_init(void)
  {
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable the GPIO_led Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	/* Configure PB10、PB11、PC6、PC7 in Output Out_PP mode */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable the GPIO_led Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	
    }
void key_test()
{	

	if(key2 == Bit_SET)
	{	
		 while(key2);
		 wave_change = wave_change+1;	
		 GPIO_Configuration();
		 TIM2_Configuration();	
		 DAC_Configuration();
		 MDA_Configuration();
		 led_init();	
		 TIM_Cmd(TIM2, ENABLE); 
//		 GPIO_WriteBit(GPIOE, GPIO_Pin_2, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_2)));/*PC6管脚翻转*/
		 
	}
//	if(key3 == Bit_SET)
//	{	
//		 while(key3);
//		 wave_change = wave_change-1;	
//		 GPIO_Configuration();
//		 TIM2_Configuration();	
//		 DAC_Configuration();
//		 MDA_Configuration();
//		 led_init();	
//		 TIM_Cmd(TIM2, ENABLE); /*PC6管脚翻转*/
//		 
//	}

//	if(key3 == Bit_RESET)
//	{	 
//		 while((BitAction)(1 -key3));
//		 wave_change = wave_change-1;	
//		 GPIO_Configuration();
//		 TIM2_Configuration();	
//		 DAC_Configuration();
//		 MDA_Configuration();
//		 led_init();	
//		 TIM_Cmd(TIM2, ENABLE); 
//		 GPIO_WriteBit(GPIOE, GPIO_Pin_3, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_3)));/*PC6管脚翻转*/
//		 
//	}
//	if(key4 == Bit_RESET)
//	{
//		 while((BitAction)(1 -key4));
//		 wave_change = wave_change-1;	
//		 GPIO_Configuration();
//		 TIM2_Configuration();	
//		 DAC_Configuration();
//		 MDA_Configuration();
//		 led_init();	
//		 TIM_Cmd(TIM2, ENABLE); 	
//		 GPIO_WriteBit(GPIOE, GPIO_Pin_4, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_4)));/*PC6管脚翻转*/
//		 
//	}
//	if(key5 == Bit_RESET)
//	{
//		 while((BitAction)(1 -key5));
//		 GPIO_WriteBit(GPIOE, GPIO_Pin_5, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5)));/*PC6管脚翻转*/
//		 
//	}
}
