/**
  ******************************************************************************
  * @file    USART/DMA_Interrupt/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
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
#include "stm32f10x_it.h"
#include"Delay.h"
#include "stdio.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_DMA_Interrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
typedef enum {BUF_NO1=0,BUF_NO2=1}BUF_NO;

//uint8_t Trigger1[48]={0x5A,0xA5,0x05,0x82,0x00,0x20,0x00,0x01,0x5A,0xA5,0x05,0x82,0x00,0x21,0x00,0x01,0x5A,0xA5,0x05,0x82,0x00,0x22,0x00,0x01,
//                       0x5A,0xA5,0x05,0x82,0x00,0x23,0x00,0x01,0x5A,0xA5,0x05,0x82,0x00,0x24,0x00,0x01,0x5A,0xA5,0x05,0x82,0x00,0x25,0x00,0x01};
//uint8_t Trigger2[48]={0x5A,0xA5,0x05,0x82,0x00,0x20,0x00,0x00,0x5A,0xA5,0x05,0x82,0x00,0x21,0x00,0x00,0x5A,0xA5,0x05,0x82,0x00,0x22,0x00,0x00,
//                       0x5A,0xA5,0x05,0x82,0x00,0x23,0x00,0x00,0x5A,0xA5,0x05,0x82,0x00,0x24,0x00,0x00,0x5A,0xA5,0x05,0x82,0x00,0x25,0x00,0x00};
//#define TRIGGER_TA_Port						GPIOA
//#define TRIGGER_TA_Pin						GPIO_Pin_5
//#define TRIGGER_TA_RCC_APB2Periph			RCC_APB2Periph_GPIOA


//#define TRIGGER_TB_Port						GPIOA
//#define TRIGGER_TB_Pin						GPIO_Pin_4
//#define TRIGGER_TB_RCC_APB2Periph			RCC_APB2Periph_GPIOA

#define TRIGGER_TC_Port						GPIOA
#define TRIGGER_TC_Pin						GPIO_Pin_3
#define TRIGGER_TC_RCC_APB2Periph			RCC_APB2Periph_GPIOA

#define TRIGGER_HA_Port						GPIOA
#define TRIGGER_HA_Pin						GPIO_Pin_2
#define TRIGGER_HA_RCC_APB2Periph			RCC_APB2Periph_GPIOA

#define TRIGGER_HB_Port						GPIOA
#define TRIGGER_HB_Pin						GPIO_Pin_1
#define TRIGGER_HB_RCC_APB2Periph			RCC_APB2Periph_GPIOA

#define TRIGGER_HC_Port						GPIOA
#define TRIGGER_HC_Pin						GPIO_Pin_0
#define TRIGGER_HC_RCC_APB2Periph			RCC_APB2Periph_GPIOA

#define TRIGGER_TD_Port						GPIOD
#define TRIGGER_TD_Pin						GPIO_Pin_13
#define TRIGGER_TD_RCC_APB2Periph			RCC_APB2Periph_GPIOD


#define TRIGGER_TE_Port						GPIOD
#define TRIGGER_TE_Pin						GPIO_Pin_12
#define TRIGGER_TE_RCC_APB2Periph			RCC_APB2Periph_GPIOD


#define TRIGGER_TF_Port						GPIOD
#define TRIGGER_TF_Pin						GPIO_Pin_11
#define TRIGGER_TF_RCC_APB2Periph			RCC_APB2Periph_GPIOD


#define TRIGGER_HD_Port						GPIOD
#define TRIGGER_HD_Pin						GPIO_Pin_10
#define TRIGGER_HD_RCC_APB2Periph			RCC_APB2Periph_GPIOD

#define TRIGGER_HE_Port						GPIOD
#define TRIGGER_HE_Pin						GPIO_Pin_9
#define TRIGGER_HE_RCC_APB2Periph			RCC_APB2Periph_GPIOD

#define TRIGGER_HF_Port						GPIOD
#define TRIGGER_HF_Pin						GPIO_Pin_8
#define TRIGGER_HF_RCC_APB2Periph			RCC_APB2Periph_GPIOD


void Led(void);
 
extern u8 USART1_TX_Finish;
extern u8 USART1_DMA_Buf1[512];
extern u8 USART1_DMA_Buf2[512];

extern u8 USART3_TX_Finish;
extern u8 USART3_DMA_Buf1[512];
extern u8 USART3_DMA_Buf2[512];
extern u8	UART4_TX_Finish;
extern uint8_t  Flag_u;

extern u8 time_stop_flag;
extern u8 time_start_flag;
extern int  time_count_ms; 
extern int Time_show;
//extern int Qianwei;//time_count_msǧλ
//extern int Baiwei;//time_count_ms��λ
//extern int Shiwei;//time_count_msʮλ
//extern int Gewei;//time_count_ms��λ

extern bool Buf_Ok;	//BUF�Ƿ��Ѿ�����
extern BUF_NO Free_Buf_Now;	//���е�BUF��
extern DMA_InitTypeDef DMA_InitStructure;
extern uint8_t TxBuffer1[12];
extern uint8_t TxBuffer2[12];
extern uint8_t TxBuffer3[12];
extern uint8_t TxBuffer4[12];
extern uint8_t Tx_Return[7];
extern uint8_t Tx_Tips[7];
extern uint8_t Tx_Cancle[8];
extern uint8_t TA[8];
extern uint8_t TB[8];
extern uint8_t TC[8];
extern uint8_t TD[8];
extern uint8_t TE[8];
extern uint8_t TF[8];
extern uint8_t HA[8];
extern uint8_t HB[8];
extern uint8_t HC[8];
extern uint8_t HD[8];
extern uint8_t HE[8];
extern uint8_t HF[8];

extern uint8_t  TH_2;			 //ABC�����־ 1����������� 0���������
extern uint8_t  TH_3;			 //DEF�����־ 1����������� 0���������
extern uint8_t  TH_4;			 //DEF�����־ 1����������� 0���������
extern uint8_t  TH_5;			 //DEF�����־ 1����������� 0���������
extern uint8_t  TH_6;			 //DEF�����־ 1����������� 0���������


extern uint16_t Current_T;
extern uint16_t Current_H;
extern uint16_t Rad;
extern Send_Series_Data(uint8_t*TxBuffer,uint8_t NbrOfDataToSend);
extern CurrentT_Operation(uint8_t Num);
extern CurrentH_Operation( uint8_t Num);
extern Rad_Operation( uint8_t Num);
extern u8 Relay_Status[18];
extern uint16_t Time_T[6];
extern uint16_t Time_H[6];
extern uint8_t TimeT_Correct[6];
extern uint8_t TimeH_Correct[6];
extern u8 Start;

void TIM5_IRQHandler(void);
//void Send_Series_Qianwei(uint8_t Qianwei);
//void Send_Series_Baiwei(uint8_t Baiwei);
//void Send_Series_Shiwei(uint8_t Shiwei);
//void Send_Series_Gewei(uint8_t Gewei);
	
//extern	uint8_t MODE=0;
//extern	uint8_t flag_mode=0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
//    SysTick->CTRL&=0XFFFFFFFE;         //�رռ�����
//    SysTick->VAL=0X00000000;           //��ռ����� 
//	Menu_Operation();
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	u16 DATA_LEN;
	u16 i;
	i=i;
 	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)   //�����ж�(���յ������ݱ����� 0x0d 0x0a ��β)
    {
	 
		DMA_Cmd(DMA1_Channel5, DISABLE);//�ر�DMA,��ֹ�������������
		//USART_RX_STA = USART1->SR;//�ȶ�SR��Ȼ���DR�������
        //USART_RX_STA = USART1->DR;
  		DATA_LEN=512-DMA_GetCurrDataCounter(DMA1_Channel5); 
		if(DATA_LEN > 0)
        {			
			if(Free_Buf_Now==BUF_NO1) //���BUF1���У���DMA�������ݸ�ֵ��BUF1
		    {	
			    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf1;
			    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
			    Free_Buf_Now=BUF_NO2;
		    }
		    else  //���BUF2���У���DMA�������ݸ�ֵ��BUF2
		    {
			    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf2;
			    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
			    Free_Buf_Now=BUF_NO1;
		    }
		    Buf_Ok=TRUE;
			
		}
		DMA_ClearFlag(DMA1_FLAG_GL5 | DMA1_FLAG_TC5 | DMA1_FLAG_TE5 | DMA1_FLAG_HT5);//���־
		DMA1_Channel5->CNDTR = 512;//��װ��
		DMA_Cmd(DMA1_Channel5, ENABLE);//������,�ؿ�DMA
		//��SR���DR���Idle
		i = USART1->SR;
		i = USART1->DR;
	}
	if(USART_GetITStatus(USART1, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//����
	{
		USART_ClearITPendingBit(USART1, USART_IT_PE | USART_IT_FE | USART_IT_NE);
	}
  	USART_ClearITPendingBit(USART1, USART_IT_TC);
  	USART_ClearITPendingBit(USART1, USART_IT_IDLE);
		Flag_u=1;
}


//void USART3_IRQHandler(void)
//{
//	u16 DATA_LEN;
//	u16 i;
//	i=i;
// 	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
//    {
//		DMA_Cmd(DMA1_Channel3, DISABLE);//�ر�DMA,��ֹ�������������
//		//USART_RX_STA = USART1->SR;//�ȶ�SR��Ȼ���DR�������
//        //USART_RX_STA = USART1->DR;
//  		DATA_LEN=512-DMA_GetCurrDataCounter(DMA1_Channel3); 
//		if(DATA_LEN > 0)
//        {			
//			if(Free_Buf_Now==BUF_NO1) //���BUF1���У���DMA�������ݸ�ֵ��BUF1
//		    {	
//			    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf1;
//			    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
//			    Free_Buf_Now=BUF_NO2;
//		    }
//		    else  //���BUF2���У���DMA�������ݸ�ֵ��BUF2
//		    {
//			    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf2;
//			    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
//			    Free_Buf_Now=BUF_NO1;
//		    }
//		    Buf_Ok=TRUE;
//			
//		}
//		DMA_ClearFlag(DMA1_FLAG_GL3 | DMA1_FLAG_TC3 | DMA1_FLAG_TE3 | DMA1_FLAG_HT3);//���־
//		DMA1_Channel3->CNDTR = 512;//��װ��
//		DMA_Cmd(DMA1_Channel3, ENABLE);//������,�ؿ�DMA
//		//��SR���DR���Idle
//		i = USART3->SR;
//		i = USART3->DR;
//	}
//	if(USART_GetITStatus(USART3, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//����
//	{
//		USART_ClearITPendingBit(USART3, USART_IT_PE | USART_IT_FE | USART_IT_NE);
//	}
//  	USART_ClearITPendingBit(USART3, USART_IT_TC);
//  	USART_ClearITPendingBit(USART3, USART_IT_IDLE);
//		Flag_u=2;
//}

void UART4_IRQHandler(void)
{
	u16 DATA_LEN;
	u16 i;
	i=i;
 	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)
    {
		DMA_Cmd(DMA2_Channel2, DISABLE);//�ر�DMA,��ֹ�������������
		//USART_RX_STA = USART1->SR;//�ȶ�SR��Ȼ���DR�������
        //USART_RX_STA = USART1->DR;
  		DATA_LEN=512-DMA_GetCurrDataCounter(DMA2_Channel2); 
		if(DATA_LEN > 0)
        {			
			if(Free_Buf_Now==BUF_NO1) //���BUF1���У���DMA�������ݸ�ֵ��BUF1
		    {	
			    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf1;
			    DMA_Init(DMA2_Channel2, &DMA_InitStructure);
			    Free_Buf_Now=BUF_NO2;
		    }
		    else  //���BUF2���У���DMA�������ݸ�ֵ��BUF2
		    {
			    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf2;
			    DMA_Init(DMA2_Channel2, &DMA_InitStructure);
			    Free_Buf_Now=BUF_NO1;
		    }
		    Buf_Ok=TRUE;
			
		}
		DMA_ClearFlag(DMA2_FLAG_GL2 | DMA2_FLAG_TC2 | DMA2_FLAG_TE2 | DMA2_FLAG_HT2);//���־
		DMA2_Channel2->CNDTR = 512;//��װ��
		DMA_Cmd(DMA2_Channel2, ENABLE);//������,�ؿ�DMA
		//��SR���DR���Idle
		i = UART4->SR;
		i = UART4->DR;
	}
	if(USART_GetITStatus(USART3, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//����
	{
		USART_ClearITPendingBit(USART3, USART_IT_PE | USART_IT_FE | USART_IT_NE);
	}
  	USART_ClearITPendingBit(UART4, USART_IT_TC);
  	USART_ClearITPendingBit(UART4, USART_IT_IDLE);
		Flag_u=2;
}


void DMA1_Channel5_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA1_IT_TC5);
  DMA_ClearITPendingBit(DMA1_IT_TE5);
  DMA_Cmd(DMA1_Channel5, DISABLE);//�ر�DMA,��ֹ�������������
  DMA1_Channel5->CNDTR = 580;//��װ��
  DMA_Cmd(DMA1_Channel5, ENABLE);//������,�ؿ�DMA
}
void DMA1_Channel4_IRQHandler(void)
{
  USART1_TX_Finish=1;
  DMA_ClearITPendingBit(DMA1_IT_TC4);
  DMA_ClearITPendingBit(DMA1_IT_TE4);
  DMA_Cmd(DMA1_Channel4, DISABLE);//�ر�DMA
}
//void DMA1_Channel3_IRQHandler(void)
//{
//  DMA_ClearITPendingBit(DMA1_IT_TC3);
//  DMA_ClearITPendingBit(DMA1_IT_TE3);
//  DMA_Cmd(DMA1_Channel3, DISABLE);//�ر�DMA,��ֹ�������������
//  DMA1_Channel3->CNDTR = 580;//��װ��
//  DMA_Cmd(DMA1_Channel3, ENABLE);//������,�ؿ�DMA
//}
//void DMA1_Channel2_IRQHandler(void)
//{
//  USART3_TX_Finish=1;
//  DMA_ClearITPendingBit(DMA1_IT_TC2);
//  DMA_ClearITPendingBit(DMA1_IT_TE2);
//  DMA_Cmd(DMA1_Channel2, DISABLE);//�ر�DMA
//}

//void DMA2_Channel3_IRQHandler(void)
//{
//  DMA_ClearITPendingBit(DMA2_IT_TC3);
//  DMA_ClearITPendingBit(DMA2_IT_TE3);
//  DMA_Cmd(DMA2_Channel3, DISABLE);//�ر�DMA,��ֹ�������������
//  DMA2_Channel3->CNDTR = 580;//��װ��
//  DMA_Cmd(DMA2_Channel3, ENABLE);//������,�ؿ�DMA
//}
void DMA2_Channel2_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA2_IT_TC2);
  DMA_ClearITPendingBit(DMA2_IT_TE2);
  DMA_Cmd(DMA2_Channel2, DISABLE);//�ر�DMA,��ֹ�������������
  DMA2_Channel2->CNDTR = 580;//��װ��
  DMA_Cmd(DMA2_Channel2, ENABLE);//������,�ؿ�DMA
}
void DMA2_Channel5_IRQHandler(void)
{
  UART4_TX_Finish=1;
  DMA_ClearITPendingBit(DMA2_IT_TC5);
  DMA_ClearITPendingBit(DMA2_IT_TE5);
  DMA_Cmd(DMA2_Channel5, DISABLE);//�ر�DMA
}
void EXTI0_IRQHandler(void)
{
  uint8_t i=0;
	i=i;
  /*C���բ*/
  if(EXTI_GetFlagStatus(EXTI_Line0)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line0);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_HC_Port,TRIGGER_HC_Pin)==0)
	  {
		Delay_ms(2);		  
		   if(GPIO_ReadInputDataBit(TRIGGER_HC_Port,TRIGGER_HC_Pin)==0)
		   {
		 	 if(!TH_5)
	         {				 				 							 
					 Time_H[2]=Time_H[2]-TimeH_Correct[2];
					 Delay_ms(Time_H[2]);
					 Time_H[2]=Time_H[2]+TimeH_Correct[2];
               if(TH_2)  		 //ABC�������
	           {					    				  									
			        Send_Series_Data(&TxBuffer1[0],12);
			        GPIOD->BSRR =0x0007;
					  Relay_Status[7]=1;
					  Relay_Status[9]=1;
					  Relay_Status[11]=1;	
					  		   
             }
               else				//ABC����C����
	           {				 
			     Send_Series_Data(&HC[0],8);
			     GPIOD->BSRR =0x0004;
					  Relay_Status[11]=1;
				    
	           }
	         }
	         else
	         {
			      Send_Series_Data(&Tx_Tips[0],7);
			      TH_6=1;
	         }
		   }
	 }
  }
}
void EXTI1_IRQHandler(void)
{
  uint8_t i=0;
	i=i;
  /*B���բ*/
  if(EXTI_GetFlagStatus(EXTI_Line1)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line1);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_HB_Port,TRIGGER_HB_Pin)==0)
	 {
		 Delay_ms(2);
		 if(GPIO_ReadInputDataBit(TRIGGER_HB_Port,TRIGGER_HB_Pin)==0)
		 {
		  	  if(!TH_5)
	          {
						time_stop_flag=1;		
						Time_H[1]=Time_H[1]-TimeH_Correct[1];
		        Delay_ms(Time_H[1]);
						Time_H[1]=Time_H[1]+TimeH_Correct[1];
                if(TH_2)  			//ABC�������
	            {					    				  									
			      Send_Series_Data(&TxBuffer1[0],12); 
			      GPIOD->BSRR =0x0007;
					  Relay_Status[7]=1;
					  Relay_Status[9]=1;
					  Relay_Status[11]=1;
                }
                else					//ABC����B����
	            {				 
			      Send_Series_Data(&HB[0],8);
			      GPIOD->BSRR =0x0002;
					  Relay_Status[9]=1;
	            }
	         }
	         else
	         {
			   Send_Series_Data(&Tx_Tips[0],7); 
			   TH_6=1;
	         }
		}
	}
  }
}
void EXTI2_IRQHandler(void)
{
  /*A���բ*/
  if(EXTI_GetFlagStatus(EXTI_Line2)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line2);
     Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_HA_Port,TRIGGER_HA_Pin)==0)
	 {
		Delay_ms(2);
		   if(GPIO_ReadInputDataBit(TRIGGER_HA_Port,TRIGGER_HA_Pin)==0)
		   {
		    if(!TH_5)
			{
				  
				 Time_H[0]=Time_H[0]-TimeH_Correct[0];
		     Delay_ms(Time_H[0]);
				 Time_H[0]=Time_H[0]+TimeH_Correct[0];
              if(TH_2)  			 //ABC�������
	          {					    				  									
			    Send_Series_Data(&TxBuffer1[0],12);
			    GPIOD->BSRR =0x0007;
					  Relay_Status[7]=1;
					  Relay_Status[9]=1;
					  Relay_Status[11]=1;
              }
              else						//ABC����A����
	          {				 
			    Send_Series_Data(&HA[0],8);
			    GPIOD->BSRR =0x0001;
					  Relay_Status[7]=1;
	          }			
			
		   }
		   else
		   {
			  Send_Series_Data(&Tx_Tips[0],7); 
		      TH_6=1;		   		   
		   }
		 }
	}
  }
}
void EXTI3_IRQHandler(void)
{
  /*C����բ*/
  if(EXTI_GetFlagStatus(EXTI_Line3)==SET)
 {
     EXTI_ClearITPendingBit(EXTI_Line3);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_TC_Port,TRIGGER_TC_Pin)==0)
	 {
	    Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_TC_Port,TRIGGER_TC_Pin)==0)
		{
			if(!TH_5)
			{		
			    Time_T[2]=Time_T[2]-TimeT_Correct[2];
		      Delay_ms(Time_T[2]);
			    Time_T[2]=Time_T[2]+TimeT_Correct[2];
              if(TH_2)  //ABC�������
	          {	
			    if(TH_4)			//ABC�������,˫��
				{
				  if(TH_3)		 	//ABC�������,˫����DEF˫�����
				  {
 			        Send_Series_Data(&TxBuffer3[0],12);
					Send_Series_Data(&TxBuffer4[0],12);	
			        GPIOD->BRR =0x003F;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;
					  Relay_Status[17]=0;																  
				  }
				  else				//ABC�������,˫����DEF�������
				  {
			        Send_Series_Data(&TxBuffer3[0],12);
			        Send_Series_Data(&TF[0],8);
			        GPIOD->BRR =0x0027;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;	
					  Relay_Status[17]=0;															  				  
				  }								
				}
				else		//ABC�������,����
				{
			      Send_Series_Data(&TxBuffer3[0],12);
			      GPIOD->BRR =0x0007;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;														
				}				    				  									
             }
             else
	         {	
			    if(TH_4) //C���������˫��
				{
				  if(TH_3)	 //C���������˫����DEF�������
				  {
				    Send_Series_Data(&TxBuffer4[0],12);
                    GPIOD->BRR=0x002C;
					  Relay_Status[11]=0;	
					  Relay_Status[13]=0;	
					  Relay_Status[15]=0;	
					  Relay_Status[17]=0;																																  
				  }
				  else		 //C���������˫����DEF�������
				  {
			        Send_Series_Data(&TC[0],8);
			        Send_Series_Data(&TF[0],8);						
                    GPIOD->BRR=0x0024;
																
					  Relay_Status[11]=0;
					  Relay_Status[17]=0;																											  				  
				  }				
				}
				else		//C�������������
				{
			      Send_Series_Data(&TC[0],8);
			      GPIOD->BRR =0x0004;	
					  Relay_Status[11]=0;									
				}
	        }			
		  }
		   else
		   {
			  Send_Series_Data(&Tx_Tips[0],7); 
		      TH_6=1;		   		   
		   }
		}
	 }	   							
  }
}
void EXTI4_IRQHandler(void)
{
  /*B����բ*/
   if(EXTI_GetFlagStatus(EXTI_Line4)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line4);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_TC_Port,TRIGGER_TC_Pin)==0)
	 {
		Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_TC_Port,TRIGGER_TC_Pin)==0)
		{
			if(!TH_5)
			{
				  Time_T[1]=Time_T[1]-TimeT_Correct[1];
			    Delay_ms(Time_T[1]);
				  Time_T[1]=Time_T[1]+TimeT_Correct[1];
                if(TH_2)  	//ABC�������
	            {	
			      if(TH_4)				 //ABC���������բ��˫��
				  {
				    if(TH_3)				//ABC���������բ��˫����DEF�������
					{
			          Send_Series_Data(&TxBuffer3[0],12);				  
				  	  Send_Series_Data(&TxBuffer4[0],12);	
			          GPIOD->BRR =0x003F;
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;	
					  Relay_Status[13]=0;	
					  Relay_Status[15]=0;	
					  Relay_Status[17]=0;										
												
					}
					else				//ABC���������բ��˫����DEF�������
					{
			          Send_Series_Data(&TxBuffer3[0],12);				
			          Send_Series_Data(&TE[0],8);
				      GPIOD->BRR =0x0017;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;	
					  Relay_Status[15]=0;																							
					}			
				  }
				  else			 //ABC���������բ������
				  {
			        Send_Series_Data(&TxBuffer3[0],12);
			        GPIOD->BRR =0x0007;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;															
				  }							    				  									
                }
                else			//ABC�������
	            {	
			      if(TH_4)			//ABC���������˫��
				  { 
				    if(TH_3)		 //ABC���������˫����DEF�������
					{
				      Send_Series_Data(&TxBuffer4[0],8);
                      GPIOD->BRR=0x003A;		
					  Relay_Status[9]=0;
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;
					  Relay_Status[17]=0;																										
					}
					else			 //ABC���������˫����DEF�������
					{
			          Send_Series_Data(&TB[0],8);
			          Send_Series_Data(&TE[0],8);		
                      GPIOD->BRR=0x0012;
					  Relay_Status[9]=0;	
					  Relay_Status[15]=0;																					
					} 				
				  }
				  else	 //ABC�������������
				  { 
				    Send_Series_Data(&TB[0],8);
			        GPIOD->BRR =0x0002;	
					  Relay_Status[9]=0;														
				  }
	           }					
		   }
		   else
		   {
			  Send_Series_Data(&Tx_Tips[0],7);
		      TH_6=1;		   		   
		   }
		}
	 }	
  }
}
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetFlagStatus(EXTI_Line5)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line5);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_TC_Port,TRIGGER_TC_Pin)==0)
	 {
	   Delay_ms(2);
	   if(GPIO_ReadInputDataBit(TRIGGER_TC_Port,TRIGGER_TC_Pin)==0)
	   {
	       if(!TH_5)
	       {
					Time_T[0]=Time_T[0]-TimeT_Correct[0];
		      Delay_ms(Time_T[0]);
					Time_T[0]=Time_T[0]+TimeT_Correct[0];
            if(TH_2)  		//ABC�������
	        {	
			    if(TH_4)			 	//ABC���������˫��
				{
				  if(TH_3)				//ABC���������˫����	DEF�������
				  {
			        Send_Series_Data(&TxBuffer3[0],12);	
			        Send_Series_Data(&TxBuffer4[0],12);	
			        GPIOD->BRR =0x003F;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;
					  Relay_Status[17]=0;												  
				  }
				  else				//ABC���������˫����	DEF�������
				  {
			        Send_Series_Data(&TxBuffer3[0],12);
			        Send_Series_Data(&TD[0],8);
			        GPIOD->BRR =0x000F;		
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;
					  Relay_Status[13]=0;									  				  
				  }				
				}
				else		 	//ABC�������������
				{
			      Send_Series_Data(&TxBuffer3[0],12);
			      GPIOD->BRR =0x0007;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;													
				}							    				  									
            }
            else			//ABC A�������
	        {	
			    if(TH_4)	 //ABC A���������˫��
				{
				  if(TH_3)	 //ABC A���������˫����DEF�������
				  {
				   	Send_Series_Data(&TxBuffer4[0],12);	
				    GPIOD->BRR =0x0039;	
					  Relay_Status[7]=0;
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;	
					  Relay_Status[17]=0;																										  
				  }
				  else			 //ABC A���������˫����DEF�������
				  {
                    Send_Series_Data(&TA[0],8);				  
			        Send_Series_Data(&TD[0],8);
				    GPIOD->BRR =0x0009;	
					  Relay_Status[7]=0;
					  Relay_Status[13]=0;									  				  
				  }				
				}
				else			//ABC A�������������
				{
				  Send_Series_Data(&TA[0],8);
			      GPIOD->BRR =0x0001;	
					  Relay_Status[7]=0;													
				}
	        }	 
	 
	      }
	      else
	      {
	 	  	  Send_Series_Data(&Tx_Tips[0],7);
		      TH_6=1;
	 
	      }
	   }
	}	
  }
    if(EXTI_GetFlagStatus(EXTI_Line8)==SET)
  {
        EXTI_ClearITPendingBit(EXTI_Line8);
		Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_HF_Port,TRIGGER_HF_Pin)==0)
		{
		  Delay_ms(2);
		  if(GPIO_ReadInputDataBit(TRIGGER_HF_Port,TRIGGER_HF_Pin)==0)
		  {
		     if(!TH_5)
		     {
					 Time_H[5]= Time_H[5]-TimeH_Correct[5];
		       Delay_ms(Time_H[5]);
 					 Time_H[5]= Time_H[5]+TimeH_Correct[5];
               if(TH_3)  	 	//DEF���������բ
	           {				    				  									
			     Send_Series_Data(&TxBuffer2[0],12);
			     GPIOD->BSRR =0x0038;
					  Relay_Status[13]=1;
					  Relay_Status[15]=1;	
					  Relay_Status[17]=1;	
               }
               else				//DEF F���������բ
	           {	 
			     Send_Series_Data(&HF[0],8);
			     GPIOD->BSRR =0x0020;
					  Relay_Status[17]=1;	
	           }				
		     }
		     else
		     {
	 	  	    Send_Series_Data(&Tx_Tips[0],7);
		        TH_6=1;				
		     }
		  }
	   }

  }
    if(EXTI_GetFlagStatus(EXTI_Line9)==SET)
   {
     EXTI_ClearITPendingBit(EXTI_Line9);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_HE_Port,TRIGGER_HE_Pin)==0)
	 {
		Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_HE_Port,TRIGGER_HE_Pin)==0)
		{
	       if(!TH_5)
	       {
						Time_H[4]= Time_H[4]-TimeH_Correct[4];
		        Delay_ms(Time_H[4]);
						Time_H[4]= Time_H[4]+TimeH_Correct[4];
            if(TH_3)  	 	//DEF���������բ
	        {					    				  									
			    Send_Series_Data(&TxBuffer2[0],12);
			    GPIOD->BSRR =0x0038;
					  Relay_Status[13]=1;
					  Relay_Status[15]=1;	
					  Relay_Status[17]=1;	
            }
            else			//DEF E���������բ
	        {	 
			    Send_Series_Data(&HE[0],8);
			    GPIOD->BSRR =0x0010;
					  Relay_Status[15]=1;	
	        }	 	 
	       }
		   else
		   {
	 	  	  Send_Series_Data(&Tx_Tips[0],7);
		      TH_6=1;				
		   }
		}
	 }
   }
}
void EXTI15_10_IRQHandler(void)
{
//		 uint8_t i=0;
    if(EXTI_GetFlagStatus(EXTI_Line10)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line10);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_HD_Port,TRIGGER_HD_Pin)==0)
	 {
		Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_HD_Port,TRIGGER_HD_Pin)==0)
		{
	      if(!TH_5)
	      {
				Time_H[3]=Time_H[3]-TimeH_Correct[3];
		    Delay_ms(Time_H[3]);
				Time_H[3]=Time_H[3]+TimeH_Correct[3];
            if(TH_3)  							 	//DEF���������բ
	        {					    				  									
			    Send_Series_Data(&TxBuffer2[0],12);  
			    GPIOD->BSRR =0x0038;
					  Relay_Status[13]=1;
					  Relay_Status[15]=1;	
					  Relay_Status[17]=1;	
            }
            else										 //DEF D�������բ
	        {	  
			    Send_Series_Data(&HD[0],8);
			    GPIOD->BSRR =0x0008;
					  Relay_Status[13]=1;
	        }	 	 
	      }
	      else
	      {
	 	  	  Send_Series_Data(&Tx_Tips[0],7);
		      TH_6=1;	 
	 
	      }
	   }
	 }
 }
	
  if(EXTI_GetFlagStatus(EXTI_Line11)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line11);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_TF_Port,TRIGGER_TF_Pin)==0)
	 {
	    Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_TF_Port,TRIGGER_TF_Pin)==0)
		{
	     if(!TH_5)
	     {
				Time_T[5]=Time_T[5]-TimeT_Correct[5];
		    Delay_ms(Time_T[5]);
				Time_T[5]=Time_T[5]+TimeT_Correct[5];
            if(TH_3)  					//DEF�������
	        {	
                if(TH_4)		 //DEF���������˫��
				{
				  if(TH_2)				//DEF���������˫����ABC�������
				  {
			        Send_Series_Data(&TxBuffer3[0],12);	
			        Send_Series_Data(&TxBuffer4[0],12);
			        GPIOD->BRR =0x003F;
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;	
					  Relay_Status[11]=0;								
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;	
					  Relay_Status[17]=0;										  
				  }
				  else				 //DEF���������˫����ABC�������
				  {
			        Send_Series_Data(&TxBuffer4[0],12);
			        Send_Series_Data(&TC[0],8);
			        GPIOD->BRR =0x003C;	
					  Relay_Status[11]=0;								
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;	
					  Relay_Status[17]=0;										  
				  }				
				}
				else	 //DEF�������������
				{
			      Send_Series_Data(&TxBuffer4[0],12);
			      GPIOD->BRR =0x0038;	
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;	
					  Relay_Status[17]=0;														
				}							    				  									
            }
            else	 //DEF�������
	        {	
                if(TH_4)	 //DEF������� ˫��
				{ 
				  if(TH_2)				 //DEF������� ˫��		ABC˫��
				  {
			        Send_Series_Data(&TxBuffer3[0],12);
                    GPIOD->BRR=0x0027;
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;
					  Relay_Status[17]=0;															  
				  }
				  else						//DEF������� ˫��		ABC����
				  {
			        Send_Series_Data(&TF[0],8);
			        Send_Series_Data(&TC[0],8);			
                    GPIOD->BRR=0x0024;	
					    Relay_Status[17]=0;	
					   Relay_Status[11]=0;																				  
				  
				  }								
				}
				else			 //DEF������� ����
				{  
			      Send_Series_Data(&TF[0],8);
			      GPIOD->BRR =0x0020;	
					    Relay_Status[17]=0;													
				}
	        }	 	 
	      }
	      else
	      {
	 	  	  Send_Series_Data(&Tx_Tips[0],7);
		      TH_6=1;	 
	 
	      }
		}
	 }	
  }
    if(EXTI_GetFlagStatus(EXTI_Line12)==SET)
   {
     EXTI_ClearITPendingBit(EXTI_Line12);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_TE_Port,TRIGGER_TE_Pin)==0)
	 {
	    Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_TE_Port,TRIGGER_TE_Pin)==0)
		{
	      if(!TH_5)
	      {					 
        Time_T[4]=Time_T[4]-TimeT_Correct[4];
		    Delay_ms(Time_T[4]);
        Time_T[4]=Time_T[4]+TimeT_Correct[4];
            if(TH_3)  	 //DEF�������
	        {	
			    if(TH_4)			 //DEF���������˫��
				{								  //DEF���������˫����ABC�������
				  if(TH_2)
				  {
				  	Send_Series_Data(&TxBuffer4[0],12);
			        Send_Series_Data(&TxBuffer3[0],12);
					  GPIOD->BRR =0x003F;	
					  Relay_Status[7]=0;
					  Relay_Status[9]=0;
					  Relay_Status[11]=0;
					  Relay_Status[13]=0;
					  Relay_Status[15]=0;	
					  Relay_Status[17]=0;									  
				  
				  }
				  else		 //DEF���������˫����ABC�������
				  {
			        Send_Series_Data(&TxBuffer4[0],12);
			        Send_Series_Data(&TB[0],8);
			        GPIOD->BRR =0x003A;	
					    Relay_Status[9]=0;
					    Relay_Status[13]=0;
					    Relay_Status[15]=0;	
					    Relay_Status[17]=0;																	  
				  }				
				}
				else		//DEF�������������
				{
			      Send_Series_Data(&TxBuffer4[0],12);
			      GPIOD->BRR =0x0038;		
					    Relay_Status[13]=0;
					    Relay_Status[15]=0;	
					    Relay_Status[17]=0;									
				}				    				  									
            }
            else		//DEF�������
	        {	
			    if(TH_4)	 //DEF���������˫��
				{ 
				  if(TH_2)	//DEF���������˫����ABC����
				  {
			        Send_Series_Data(&TxBuffer3[0],12);
			        GPIOD->BRR =0x0017;		
					    Relay_Status[15]=0;										  
					    Relay_Status[7]=0;	
					    Relay_Status[9]=0;	
					    Relay_Status[11]=0;																			  
				  }
				  else		 //DEF���������˫����ABC����
				  {
			        Send_Series_Data(&TE[0],8);			      
				    Send_Series_Data(&TB[0],8);
			        GPIOD->BRR =0x0012;	
					    Relay_Status[15]=0;	
					    Relay_Status[9]=0;																	  				  
				  }				
				}
				else			  //DEF�������������
				{
			      Send_Series_Data(&TE[0],8);
			      GPIOD->BRR =0x0010;	
					    Relay_Status[15]=0;									
				}
	        }	 	 
	       }
	       else
	       {
	 	  	  Send_Series_Data(&Tx_Tips[0],7);
		      TH_6=1;	 
	 
	       }
		}
	 }	
  }
    if(EXTI_GetFlagStatus(EXTI_Line13)==SET)
  {
     EXTI_ClearITPendingBit(EXTI_Line13);
	 Delay_ms(2);
	 if(GPIO_ReadInputDataBit(TRIGGER_TD_Port,TRIGGER_TD_Pin)==0)
	 {
	    Delay_ms(2);
		if(GPIO_ReadInputDataBit(TRIGGER_TD_Port,TRIGGER_TD_Pin)==0)
		{
	     if(!TH_5)
	     {
				Time_T[3]=Time_T[3]-TimeT_Correct[3];
		    Delay_ms(Time_T[3]);
				Time_T[3]=Time_T[3]+TimeT_Correct[3];
            if(TH_3)  			//DEF�������
	        {	
			    if(TH_4)				 //DEF���������˫��
				{
				  if(TH_2)				 //DEF���������˫����ABC�������
				  {
			        Send_Series_Data(&TxBuffer3[0],12);	
			        Send_Series_Data(&TxBuffer4[0],12);
			        GPIOD->BRR =0x003F;										  
					    Relay_Status[7]=0;	
					    Relay_Status[9]=0;	
					    Relay_Status[11]=0;
 					    Relay_Status[13]=0;	
					    Relay_Status[15]=0;
					    Relay_Status[17]=0;												  
				  }
				  else					 //DEF���������˫����ABC�������
				  {
			        Send_Series_Data(&TxBuffer4[0],12);				
			        Send_Series_Data(&TA[0],8);
			        GPIOD->BRR =0x0039;	
					    Relay_Status[7]=0;								
 					    Relay_Status[13]=0;	
					    Relay_Status[15]=0;
					    Relay_Status[17]=0;									  				  
				  }
								
				}
				else		//DEF�������������
				{
			      Send_Series_Data(&TxBuffer4[0],12);
			      GPIOD->BRR =0x0038;	
 					    Relay_Status[13]=0;	
					    Relay_Status[15]=0;
					    Relay_Status[17]=0;													
				}				    				  									
            }
            else				 	//DEF�������
	        {	
			    if(TH_4)			 	//DEF���������˫��
				{ 
				  if(TH_2)				//DEF���������˫����ABC�������
				  {
			        Send_Series_Data(&TxBuffer3[0],12);				  
				    GPIOD->BRR=0x000F;	
 					    Relay_Status[13]=0;	
					    Relay_Status[7]=0;	
					    Relay_Status[9]=0;	
					    Relay_Status[11]=0;															  
				  }
				  else						//DEF���������˫����ABC�������
				  {
  				    Send_Series_Data(&TD[0],8);
			        Send_Series_Data(&TA[0],8);
                    GPIOD->BRR=0x0009;	
 					    Relay_Status[13]=0;		
					    Relay_Status[7]=0;																			  				  
				  }
								
				}
				else				 	//DEF�������������
				{  
			      Send_Series_Data(&TD[0],8);
			      GPIOD->BRR =0x0008;	
					    Relay_Status[13]=0;														
				}			    
	       }	 
	 
	 
	     }
	     else
	     {
	 	  	  Send_Series_Data(&Tx_Tips[0],7); 
		      TH_6=1;	 	 
	     }
	  }
	}	 		
  }
}
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM_Cmd(TIM2, DISABLE);
    /* ʱ�䵽�ж��Ƿ���Ҫ�����ѯ״̬ */
//	  if(Start==0)
//		{
//      Start = 3;				//�����ѯ״̬				
//		}	
//	  if(Start==3)
//		{
//      Start = 1;				//�����Զ�״̬				
//		}						 
  }
}
void TIM3_IRQHandler(void)
{

  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {	
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    TIM_Cmd(TIM3, DISABLE);	
	  	/* ʱ�䵽�ж��Ƿ���Ҫ�����ѯ״̬ */  
	  if(Start==0)
		{
      Start = 3;				//�����ѯ״̬				
		}	
	  if(Start==3)
		{
      Start = 1;				//�����Զ�״̬				
		}
  }			 
}
void TIM4_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    TIM_Cmd(TIM4, DISABLE);						 	  
  }
}
void TIM5_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	  //û��HA�ⲿ�ж�
   if(time_stop_flag==0)	  
	{
		 time_count_ms++;	//1ms
	  if(time_count_ms==2000)  //2s 
	  {
		time_count_ms=0;
	  }		  
	}	
	//����HA�ⲿ�жϺ�
	if(time_start_flag==0)
	{
	   time_count_ms=0;
	}
	
	 Time_show=time_count_ms;

  }
}
void TIM6_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    TIM_Cmd(TIM6, DISABLE);		
  }
}
void TIM7_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
    TIM_Cmd(TIM7, DISABLE);					 
  }
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
