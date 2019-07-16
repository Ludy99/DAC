#include"Delay.h"
extern u16 fac_ms;
void Delay_init(u8 SYSCLK)
{
    SysTick->CTRL&=0xfffffffb;//选择内部时钟 HCLK/8
//	SysTick->CTRL|=0x02;               //开启定时器中断     
    fac_ms=(u16)SYSCLK/8*1000;
}            
//延时Nms
//注意Nms的范围
//Nms<=0xffffff*8/SYSCLK
//对72M条件下,Nms<=1864 
void Delay_ms(u16 Nms)
{   
    uint32_t temp;

    if(Nms>1864)
	Nms=1864;
	if(Nms)
	{
     SysTick->LOAD=(u32)Nms*fac_ms; //时间加载
	 SysTick->VAL = 0x00;   //清空val  
     SysTick->CTRL|=0x01;               //开始倒数   
	
	 do  
     {   
       temp = SysTick->CTRL;  //时间到了之后,该位将被硬件置1,但被查询后自动清0   
     }   
     while(temp & 0x01 && !(temp &(1<<16))); //查询   
     SysTick->CTRL = 0x00;  //关闭计数器   
     SysTick->VAL = 0x00;   //清空val  
	}     
}






 
