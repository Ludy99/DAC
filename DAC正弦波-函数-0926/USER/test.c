#include "sys.h" 	
#include "delay.h"	
#include "led.h"

//ALIENTEKս��STM32������ ʵ��1
//����� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾


//, STM32F10X_HD             103ZE���ơ�STM32F10X_HD����define
//USE_STDPERIPH_DRIVER       107VC���ơ�USE_STDPERIPH_DRIVER����define


int main(void)
{				  
	Stm32_Clock_Init(2);//ϵͳʱ������9
	delay_init(72);	  	//��ʱ��ʼ��
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�	
//	SineWave1_Init(50);
	while(1)
	{
//		LED0=0;
		SineWave1_Init(50);
//		delay_ms(1000);
	}	 
}







