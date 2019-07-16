#include "sys.h" 	
#include "delay.h"	
#include "led.h"

//ALIENTEK战舰STM32开发板 实验1
//跑马灯 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

	void SineWave1_Init(u16 Wave1_Fre);

int main(void)
{				  
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);	  	//延时初始化
	LED_Init();		  	//初始化与LED连接的硬件接口
	SineWave1_Init(50);
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(1000);
		LED0=1;
		LED1=0;
		delay_ms(1000);
	}	 
}

