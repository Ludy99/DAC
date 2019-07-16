/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ʹ��DAC������Ҳ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./dac/bsp_dac.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
		
	LED_GPIO_Config();
	
	  /*��ʼ������*/
  Debug_USART_Config();
 

	printf("\r\n ��ӭʹ�ñ���  STM32 F429 �����塣\r\n");	
	printf("\r\n DAC������̣�������Ҳ�\r\n");	
  printf("\r\n ʹ��ʾ������⿪�����PA4��PA5���ţ��ɲ�����Ҳ�\r\n ");

	
	/*��ʼ��DAC����ʼDACת��,ʹ��ʾ�������PA4/PA5���ɹ۲쵽���Ҳ�*/
	DAC_Mode_Init();

	while(1);	 

}


/*********************************************END OF FILE**********************/

