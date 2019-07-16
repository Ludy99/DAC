#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "key.h"
#include "adc.h"
#include "dac.h" 
#include "usmart.h" 	
#include "stm32f10x_conf.h"
//ALIENTEKս��STM32������ ʵ��20
//DAC ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  




#define  DL (32)//���Ҳ������
uint16_t DualSine12bit[DL]; 
/******DAC�Ĵ�����ַ����*******/  
#define DAC_DHR12R1    (u32)&(DAC->DHR12R1)   //DACͨ��1�����ַ
#define DAC_DHR12R2    (u32)&(DAC->DHR12R2)   //DACͨ��2�����ַ

float  V=0.0; /*���Ҳ���ֵ����������ʼֵ*/
#define Um (0.0) /*���Ҳ���ʼ��ֵ*/
#define PI 3.1415926
float radian=90;//���Ҳ�ƽ�ƻ��ȣ�radian��ȡֵ��Χ��0~360

void Sys_Soft_Reset(void);
void USART_handler();

// 	void SineWave_Data( u16 cycle ,u16 *D)
//{
//	u16 i;
//	   
//    for( i=0;i<cycle;i++)
//    {
//        D[i]=(u16)(((Um+V)*sin(( 1.0*i/cycle-1)*2*PI+radian*0.017453)+(Um+V))*4095/3.3);	
//    }
//}

 /*************************************************************
Function  :  set_Sine12bit
Description : �������������
Input  :   MAX(�����ֵ) MIN(�����ֵ)
return  :  none
*************************************************************/ 
 void Set_Sine12bit(float MAX,float MIN)
{
	int i;
	float jiaodu=0;

	float MID=(MAX+MIN)/2.0;                        //�м��ֵ

	if(MAX>3.3) MAX=3.3;

	else if(MAX<=MIN) MIN=0;
	for(i=0;i<256;i++)
	{
		jiaodu=i*0.0247369;      //��i =127ʱ,��ʾΪ180��,����sin()�ǻ�����,������Ҫת��
		DualSine12bit[i]=  ((float)sin(jiaodu)*(MAX-MID)+MID)*1241.212;     //1241.212�Ǳ���,����4096/3.3            
	}  
}

 

int main(void)
{		 	
	u16 adcx;
	float temp;
 	u8 t=0;	 
	u8 key;
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	usmart_dev.init(72);	//��ʼ��USMART	
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	KEY_Init();				//������ʼ��		 	
 	LCD_Init();				//��ʼ��LCD
	Adc_Init(); 			//adc��ʼ��	
	Dac1_Init();		 	//DACͨ��1��ʼ��	   
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
	LCD_ShowString(30,130,200,16,16,"KEY_UP:+  KEY1:-");	
	//��ʾ��ʾ��Ϣ											      
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(30,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V");	    
	DAC->DHR12R1=(Um+V);//��ʼֵΪ1.0	   
	USART_handler();
    
	while(1)
	{
//		t++;
//		key=KEY_Scan(0);			
//	   if(key==KEY0_PRES)	//�������Ҳ�1.0
//		{ 
//		  V=0.0;
//		  SineWave_Data( DL ,DualSine12bit);     //����������Ҳ��Ĳ��α�	
//		  DAC->DHR12R1=(Um+V);		//���	
//		}
//		 else if(key==WKUP_PRES)//Um����
//		{			
//			V+=0.05;
//		    SineWave_Data( DL ,DualSine12bit);     //����������Ҳ��Ĳ��α�	
//			DAC->DHR12R1=(Um+V);		//���	
//		}
//		else if(key==KEY1_PRES)	//Um��С
//		{
//			V-=0.05;
//		    SineWave_Data( DL ,DualSine12bit);     //����������Ҳ��Ĳ��α�	
//		    DAC->DHR12R1=(Um+V);		//���	
//		}	 
//		else if(key==KEY2_PRES)	//ֹͣ���Ҳ�
//		{
//		    V=0.0;
//			SineWave_Data( DL ,DualSine12bit);     //����������Ҳ��Ĳ��α�	
//			DAC->DHR12R1=(Um+V);		//���	
//		}
		
		if(t==10||key==KEY1_PRES||key==WKUP_PRES) 	//WKUP/KEY1������,���߶�ʱʱ�䵽��
		{	  
 			adcx=DAC->DHR12R1;
			LCD_ShowxNum(94,150,adcx,4,16,0);     	//��ʾDAC�Ĵ���ֵ
			temp=(float)adcx*(3.3/4096);			//�õ�DAC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,170,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,170,temp,3,16,0X80); 	//��ʾ��ѹֵ��С������
 			adcx=Get_Adc_Average(ADC_CH1,10);		//�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,190,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,190,temp,3,16,0X80); 	//��ʾ��ѹֵ��С������
			LED1=0;	   
			t=0;
		}	    
		delay_ms(10);	

	}
}

void USART_handler()
{  
       u8 len;
       u32 hz;                //��ȡHZƵ��
       float dac_max,dac_min; //��ȡDAC��ֵ     

       if(USART_RX_STA&0x8000)
       { 
              len=USART_RX_STA&0x2F;
              USART_RX_BUF[len]=0;
              sscanf((char *)USART_RX_BUF,"%d,%f,%f",&hz,&dac_max,&dac_min);
              printf("SET  HZ = %d, MAX = %f,MIN = %f\r\n", hz,dac_max,dac_min);

              Set_Sine12bit(dac_max,dac_min);        //���ķ�ֵ
          //    Set_Period( hz);                       //����Ƶ��
			SineWave1_Init(50);//���Ҳ���ʼ��������Ϊ50Hz	
              USART_RX_STA=0;
       }
}

//20190508
    void SineWave_DMA_Config(void)
{
DMA_InitTypeDef DMA_InitStructure;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//��ʼ��DMA2��ʱ��

DMA_DeInit(DMA2_Channel3); //��DMA���ó�Ĭ��ֵ
DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1;//ָ��DMA2ͨ��3��Ŀ���ַΪDAC1_DHR12R1
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DualSine12bit;//ָ��DMA��Դ��ַΪ����Sine12bit
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//������Ϊ���ݴ����Ŀ�ĵ�
DMA_InitStructure.DMA_BufferSize = sizeof(DualSine12bit)/2;//DMA��������С
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�������ַ��������
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݿ��Ϊ����
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�ڴ����ݿ��Ϊ����
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//������ѭ������ģʽ�����ݴ�����Ϊ0ʱ���Զ��ָ����ó�ֵ
DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//�ǳ������ȼ�
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//ͨ��δ�����ó��ڴ浽�ڴ�ģʽ����ѭ��ģʽ���
DMA_Init(DMA2_Channel3, &DMA_InitStructure);//��ʼ��DMA

DMA_DeInit(DMA2_Channel4);
DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2;//ָ��DMA2ͨ��3��Ŀ���ַΪDAC2_DHR12R2
DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
DMA_Init(DMA2_Channel4, &DMA_InitStructure);

DMA_Cmd(DMA2_Channel3, ENABLE); //ʹ��DMA��channel3
DMA_Cmd(DMA2_Channel4, ENABLE); //ʹ��DMA��channel4
}
	
//��ʱ������
/*********��ʱ����ʼ��************/
void SineWave_TIM_Config(u32 Wave1_Fre)
{
    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//��ʱ��
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;     //��Ԥ��Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //����Ƶ<br>����TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseStructure.TIM_Period = Wave1_Fre;//�������Ƶ��
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//����TIME�������Ϊ����ģʽ
}


	
void SineWave1_Init(u16 Wave1_Fre)
{
       
	u16 f1=(u16)(72000000/sizeof(DualSine12bit)*2/Wave1_Fre);//����Ƶ��
    SineWave_GPIO_Config();             //��ʼ��io
    SineWave_TIM_Config(f1);            //��ʼ����ʱ��
    SineWave_DAC_Config();              //����DAC
	SineWave_DMA_Config();
    TIM_Cmd(TIM2, ENABLE);             //������ʱ��
}

