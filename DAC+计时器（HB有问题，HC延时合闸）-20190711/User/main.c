/**
  ******************************************************************************
  * @file    USART/DMA_Interrupt/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "SineWave1.h"
#include "stdio.h"

//STM32F10X_HD             STM32F103ZEоƬ���ơ�STM32F10X_HD����define 
//STM32F10X_CL,USE_STDPERIPH_DRIVER       STM32F107VCоƬֻ��Ҫ���ơ�USE_STDPERIPH_DRIVER����define 

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_DMA_Interrupt
  * @{
  */ 

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
  
  //������ԭ�ȶ����PA4��PA5�ⲿ�ж�����
int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured, 
	this is done through SystemInit() function which is called from startup
	file (startup_stm32f10x_xx.s) before to branch to application main.
	To reconfigure the default setting of SystemInit() function, refer to
	system_stm32f10x.c file
	*/     


	uint8_t i=0;
	uint8_t k=0;
//	/* Configure the GPIO ports */
	RCC_Configuration();//��Ҫ��ֲ	
	GPIO_Configuration(); //��Ҫ��ֲ	
	LedGPIO_Configuration();//PE7��Ӳ��û�нӴ˵ƣ�   20190615
	KeyGPIO_Configuration();//��Ҫ��ֲ	
	
	//���ⲿ������ѹ��ֵ��С
	for(i=0;i<TRIGGERn;i++)
	{
		TRIGGER_Init(i);	 //��ʼ���ⲿ�����Ķ˿�
	}
	for(i=0;i<RELAYn;i++)
	{
		RELAY_Init(i);   //��ʼ���̵����Ķ˿�
	}
	for(i=0;i<TIMEn;i++)
	{
		TIMET_Init(i);   //��ʼ��ģ����բ��LED�˿�
	}
	for(i=0;i<TIMEn;i++)
	{
		TIMEH_Init(i);   //��ʼ��ģ���բ��LED�˿�
	}

	Delay_init(72);	 //��Ҫ��ֲ		
	// USART3_Configuration(); 
	DMA2_Configuration();//��Ҫ��ֲ	 ԭDMA2_Channel3��DMA2_Channel2�����Ҳ�DMAΪDMA2_Channel3
	UART4_Configuration();//��Ҫ��ֲ	
	/* Configure the DMA */
	DMA_Configuration();//��Ҫ��ֲ	DMA1
	/*		usart initing	*/
	USART_Configuration();//��Ҫ��ֲ	
	/* NVIC configuration */
	NVIC_Configuration();//��Ҫ��ֲ	
	EXTI_Configuration(); 
	TimeBase_Configuration(3,5); //ԭTIM2 ��ʱ5s  ��Ҫ��ֲ	��TIM2��ΪTIM3�����Ҳ�ʹ��TIM2

	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	
	Send_Series_Data(&F_Res[0],8);	//Ƶ����ʾ����Ϊ��ɫ
    Send_Series_Data(&V_Res[0],8);	//��ֵ��ʾ����Ϊ��ɫ

	Send_Series_Data(&Qianwei_0[0],8); //��ʱ����ʼֵ��ʾΪ0
	Send_Series_Data(&Baiwei_0[0],8); 
	Send_Series_Data(&Shiwei_0[0],8); 
	Send_Series_Data(&Gewei_0[0],8); 
	
	while (1)
	{	
	
		
	/*          ѡ�񱾵�ģʽ����Զ��ģʽ                */		
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)
	{
		k=1;//PE1=0
	}
	else
	{
		k=0;//PE1=1
	}
	if(k==0 && flag_mode==1)	    //����ģʽ  PE1=1
	{
		DMA_Configuration();	     //DMA1	
		Delay_ms(100);
		flag_mode=0;
	}
	if(k==1 && flag_mode==0) 		//Զ��ģʽ    PE1=0
	{
		DMA2_Configuration();	     //DMA2	
		Delay_ms(100);
		flag_mode=1;
	}
	/******************************************************/			
	if(Buf_Ok==TRUE)//BUF����  (��dma�ж�����λ)
	{  	 	
	   Buf_Ok=FALSE; //20190531����
		
	//���ر�־20190531
	if(Flag_u==1)  //USART1�жϷ���
	{
	if(Free_Buf_Now==BUF_NO1)//���BUF1����   
	{
		SineWave1_Init();	//���Ҳ���ʼ����50Hz,Um=1000mV(��ֵ1.92V)  //���⣺����98-165�����Ƶ�ʣ���������С��20���ߴ���200��Ƶ�ʻ�ʹ���������Կؼ�ʧЧ	
		Menu_Handle(&USART1_DMA_Buf1[0]);
		Save(&StatusBuffer_Save[0],15); 
	}
	else //���BUF2����
	{
		SineWave1_Init();	//���Ҳ���ʼ����50Hz,Um=1000mV(��ֵ1.92V)
		Menu_Handle(&USART1_DMA_Buf2[0]);
		Save(&StatusBuffer_Save[0],15); 
	}
		Flag_u=0;
	}
	
	//Զ�̱�־20190531
	if(Flag_u==2)      //USART4�жϷ���
	{
	if(Free_Buf_Now==BUF_NO1)//���BUF1����
	{
		Menu_Handle(&USART1_DMA_Buf1[0]);
		Save(&StatusBuffer_Save[0],15);
	}
	else //���BUF2����
	{
		Menu_Handle(&USART1_DMA_Buf2[0]);
		Save(&StatusBuffer_Save[0],15);
	}
		Flag_u=0;
	}
	}
	
	if(Start==3)				 							//�����ѯ״̬
	{
		TimeBase_Configuration(3,10); //TIM3����ʱ10s
	}
	
	if(Start==1)										 //�����Զ�����״̬
	{
		Restore(&StatusBuffer_Restore[0],15); //�����ѱ������ֿ���������ݶ�������洢�ռ�
		Delay_ms(200);
		Send(&Tx_Return[0],7);	 //�����л���������   
		Send(&Ts[0],7);			//����ȥ�������洢�ռ������22���ֵ�����������������Ļָ��ϴεĹ���ģʽ
		Start=0;		   //�Զ������Ժ�����ʼ��״̬
	}
	

		if(time_stop_flag)   //��ʱֹͣ��־
	{
		Send_Series_Data(&Tx_Return[0],7);
		
		Qianwei = Time_show/1000;
		Baiwei = Time_show%1000/100;
		Shiwei = Time_show%1000%100/10;
		Gewei = Time_show%1000%100%10;
		
		Send_Series_Qianwei(Qianwei);//��ʾ��ʱʱ��
		Send_Series_Baiwei(Baiwei);	
		Send_Series_Shiwei(Shiwei);	
		Send_Series_Gewei(Gewei);
		time_stop_flag=0;
		time_start_flag=0;
	}
	
	
	if(TH_6)				//��·��ʧ�鲢�Ҽ�⵽�ⲿ�����ȴ���ʱ20�뷵��
	{	
		Send_Series_Data(&Count_21[0],8);
		GPIOE->BRR =0xFF80; //��PE7-PE15��0������բ������20190531
		GPIOB->BRR =0x0007; //��PB0-PB2��0
		Delay_ms(1000);
	for(i=20;i>0;i--)					//��ʼ������ʱ
	{
		Send_Series_Time(i);
		Delay_ms(1000);	   	   
	}
		Send_Series_Data(&Tx_Return[0],7);	//ʧ��״̬����������������
		Send_Series_Data(&Tx_Cancle[0],8);  //ʧ��״̬��������·��ʧ�鰴ť�ָ�������״̬
		Machine_Status[7]=0;     //��·������������״̬

		CT_Operation(Current_T);					 //ʧ��״̬�������ָ���բ��������
		CH_Operation(Current_H);					 //ʧ��״̬�������ָ���բ��������
		RAD_Operation(Rad);					 //ʧ��״̬�������ָ���բ��������

		TH_5=0;
		TH_6=0;					

}
	}
}



/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

