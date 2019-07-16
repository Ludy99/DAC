#include"Delay.h"
extern u16 fac_ms;
void Delay_init(u8 SYSCLK)
{
    SysTick->CTRL&=0xfffffffb;//ѡ���ڲ�ʱ�� HCLK/8
//	SysTick->CTRL|=0x02;               //������ʱ���ж�     
    fac_ms=(u16)SYSCLK/8*1000;
}            
//��ʱNms
//ע��Nms�ķ�Χ
//Nms<=0xffffff*8/SYSCLK
//��72M������,Nms<=1864 
void Delay_ms(u16 Nms)
{   
    uint32_t temp;

    if(Nms>1864)
	Nms=1864;
	if(Nms)
	{
     SysTick->LOAD=(u32)Nms*fac_ms; //ʱ�����
	 SysTick->VAL = 0x00;   //���val  
     SysTick->CTRL|=0x01;               //��ʼ����   
	
	 do  
     {   
       temp = SysTick->CTRL;  //ʱ�䵽��֮��,��λ����Ӳ����1,������ѯ���Զ���0   
     }   
     while(temp & 0x01 && !(temp &(1<<16))); //��ѯ   
     SysTick->CTRL = 0x00;  //�رռ�����   
     SysTick->VAL = 0x00;   //���val  
	}     
}






 
