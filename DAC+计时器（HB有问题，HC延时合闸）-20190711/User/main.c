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

//STM32F10X_HD             STM32F103ZE芯片复制“STM32F10X_HD”到define 
//STM32F10X_CL,USE_STDPERIPH_DRIVER       STM32F107VC芯片只需要复制“USE_STDPERIPH_DRIVER”到define 

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
  
  //已屏蔽原先定义的PA4、PA5外部中断引脚
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
	RCC_Configuration();//需要移植	
	GPIO_Configuration(); //需要移植	
	LedGPIO_Configuration();//PE7，硬件没有接此灯？   20190615
	KeyGPIO_Configuration();//需要移植	
	
	//有外部触发电压幅值变小
	for(i=0;i<TRIGGERn;i++)
	{
		TRIGGER_Init(i);	 //初始化外部触发的端口
	}
	for(i=0;i<RELAYn;i++)
	{
		RELAY_Init(i);   //初始化继电器的端口
	}
	for(i=0;i<TIMEn;i++)
	{
		TIMET_Init(i);   //初始化模拟跳闸的LED端口
	}
	for(i=0;i<TIMEn;i++)
	{
		TIMEH_Init(i);   //初始化模拟合闸的LED端口
	}

	Delay_init(72);	 //需要移植		
	// USART3_Configuration(); 
	DMA2_Configuration();//需要移植	 原DMA2_Channel3改DMA2_Channel2，正弦波DMA为DMA2_Channel3
	UART4_Configuration();//需要移植	
	/* Configure the DMA */
	DMA_Configuration();//需要移植	DMA1
	/*		usart initing	*/
	USART_Configuration();//需要移植	
	/* NVIC configuration */
	NVIC_Configuration();//需要移植	
	EXTI_Configuration(); 
	TimeBase_Configuration(3,5); //原TIM2 延时5s  需要移植	把TIM2改为TIM3，正弦波使用TIM2

	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	
	Send_Series_Data(&F_Res[0],8);	//频率显示设置为红色
    Send_Series_Data(&V_Res[0],8);	//幅值显示设置为红色

	Send_Series_Data(&Qianwei_0[0],8); //计时器初始值显示为0
	Send_Series_Data(&Baiwei_0[0],8); 
	Send_Series_Data(&Shiwei_0[0],8); 
	Send_Series_Data(&Gewei_0[0],8); 
	
	while (1)
	{	
	
		
	/*          选择本地模式还是远程模式                */		
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)
	{
		k=1;//PE1=0
	}
	else
	{
		k=0;//PE1=1
	}
	if(k==0 && flag_mode==1)	    //本地模式  PE1=1
	{
		DMA_Configuration();	     //DMA1	
		Delay_ms(100);
		flag_mode=0;
	}
	if(k==1 && flag_mode==0) 		//远程模式    PE1=0
	{
		DMA2_Configuration();	     //DMA2	
		Delay_ms(100);
		flag_mode=1;
	}
	/******************************************************/			
	if(Buf_Ok==TRUE)//BUF可用  (在dma中断中置位)
	{  	 	
	   Buf_Ok=FALSE; //20190531屏蔽
		
	//本地标志20190531
	if(Flag_u==1)  //USART1中断服务
	{
	if(Free_Buf_Now==BUF_NO1)//如果BUF1空闲   
	{
		SineWave1_Init();	//正弦波初始化，50Hz,Um=1000mV(幅值1.92V)  //问题：设置98-165区间的频率，接着设置小于20或者大于200的频率会使触摸屏所以控件失效	
		Menu_Handle(&USART1_DMA_Buf1[0]);
		Save(&StatusBuffer_Save[0],15); 
	}
	else //如果BUF2空闲
	{
		SineWave1_Init();	//正弦波初始化，50Hz,Um=1000mV(幅值1.92V)
		Menu_Handle(&USART1_DMA_Buf2[0]);
		Save(&StatusBuffer_Save[0],15); 
	}
		Flag_u=0;
	}
	
	//远程标志20190531
	if(Flag_u==2)      //USART4中断服务
	{
	if(Free_Buf_Now==BUF_NO1)//如果BUF1空闲
	{
		Menu_Handle(&USART1_DMA_Buf1[0]);
		Save(&StatusBuffer_Save[0],15);
	}
	else //如果BUF2空闲
	{
		Menu_Handle(&USART1_DMA_Buf2[0]);
		Save(&StatusBuffer_Save[0],15);
	}
		Flag_u=0;
	}
	}
	
	if(Start==3)				 							//进入查询状态
	{
		TimeBase_Configuration(3,10); //TIM3，延时10s
	}
	
	if(Start==1)										 //进入自动进入状态
	{
		Restore(&StatusBuffer_Restore[0],15); //开机把保存在字库里面的数据读入变量存储空间
		Delay_ms(200);
		Send(&Tx_Return[0],7);	 //界面切换到主界面   
		Send(&Ts[0],7);			//开机去读变量存储空间的内容22个字的内容用来后续程序的恢复上次的工作模式
		Start=0;		   //自动进入以后进入初始化状态
	}
	

		if(time_stop_flag)   //计时停止标志
	{
		Send_Series_Data(&Tx_Return[0],7);
		
		Qianwei = Time_show/1000;
		Baiwei = Time_show%1000/100;
		Shiwei = Time_show%1000%100/10;
		Gewei = Time_show%1000%100%10;
		
		Send_Series_Qianwei(Qianwei);//显示计时时间
		Send_Series_Baiwei(Baiwei);	
		Send_Series_Shiwei(Shiwei);	
		Send_Series_Gewei(Gewei);
		time_stop_flag=0;
		time_start_flag=0;
	}
	
	
	if(TH_6)				//断路器失灵并且检测到外部触发等待延时20秒返回
	{	
		Send_Series_Data(&Count_21[0],8);
		GPIOE->BRR =0xFF80; //将PE7-PE15置0（跳合闸电流）20190531
		GPIOB->BRR =0x0007; //将PB0-PB2置0
		Delay_ms(1000);
	for(i=20;i>0;i--)					//开始倒数计时
	{
		Send_Series_Time(i);
		Delay_ms(1000);	   	   
	}
		Send_Series_Data(&Tx_Return[0],7);	//失灵状态结束，返回主界面
		Send_Series_Data(&Tx_Cancle[0],8);  //失灵状态结束，断路器失灵按钮恢复到正常状态
		Machine_Status[7]=0;     //断路器现在是正常状态

		CT_Operation(Current_T);					 //失灵状态结束，恢复跳闸电流设置
		CH_Operation(Current_H);					 //失灵状态结束，恢复合闸电流设置
		RAD_Operation(Rad);					 //失灵状态结束，恢复合闸电流设置

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

