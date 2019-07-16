#include "sys.h" 	
#include "delay.h"	
#include "led.h"

//ALIENTEK战舰STM32开发板 实验1
//跑马灯 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

 //   void SineWave_Init(void);
	void SineWave1_Init(u16 Wave1_Fre);

//, STM32F10X_HD             103ZE则复制“STM32F10X_HD”到define
//USE_STDPERIPH_DRIVER       107VC则复制“USE_STDPERIPH_DRIVER”到define
int main(void)
{				  
	Stm32_Clock_Init(2);//系统时钟设置9
	delay_init(72);	  	//延时初始化
	LED_Init();		  	//初始化与LED连接的硬件接口
//    SineWave_Init();
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

