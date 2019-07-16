#include "sys.h" 	
#include "delay.h"	
#include "led.h"
#include "usart.h"	

//ALIENTEKս��STM32������ ʵ��1
//����� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

void USART1_IRQHandler(void);

int main(void)
{				  
  	u16 t;
	u16 len;
	u16 times=0;  
	Stm32_Clock_Init(9);//ϵͳʱ������
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	  	//��ʱ��ʼ��
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	USART1_IRQHandler();
	
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(1000);
		LED0=1;
		LED1=0;
		delay_ms(1000);
		
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nս��STM32������ ����ʵ��\r\n");
				printf("����ԭ��@ALIENTEK\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}	 
}

