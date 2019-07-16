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
//ALIENTEK战舰STM32开发板 实验20
//DAC 实验 
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  




#define  DL (32)//正弦波描点数
uint16_t DualSine12bit[DL]; 
/******DAC寄存器地址声明*******/  
#define DAC_DHR12R1    (u32)&(DAC->DHR12R1)   //DAC通道1输出地址
#define DAC_DHR12R2    (u32)&(DAC->DHR12R2)   //DAC通道2输出地址

float  V=0.0; /*正弦波幅值增减变量初始值*/
#define Um (0.0) /*正弦波初始幅值*/
#define PI 3.1415926
float radian=90;//正弦波平移弧度，radian的取值范围是0~360

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
Description : 设置正玄波码表
Input  :   MAX(正峰峰值) MIN(负峰峰值)
return  :  none
*************************************************************/ 
 void Set_Sine12bit(float MAX,float MIN)
{
	int i;
	float jiaodu=0;

	float MID=(MAX+MIN)/2.0;                        //中间峰值

	if(MAX>3.3) MAX=3.3;

	else if(MAX<=MIN) MIN=0;
	for(i=0;i<256;i++)
	{
		jiaodu=i*0.0247369;      //当i =127时,表示为180度,由于sin()是弧度制,所以需要转换
		DualSine12bit[i]=  ((float)sin(jiaodu)*(MAX-MID)+MID)*1241.212;     //1241.212是比例,等于4096/3.3            
	}  
}

 

int main(void)
{		 	
	u16 adcx;
	float temp;
 	u8 t=0;	 
	u8 key;
  	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	usmart_dev.init(72);	//初始化USMART	
	LED_Init();		  		//初始化与LED连接的硬件接口
 	KEY_Init();				//按键初始化		 	
 	LCD_Init();				//初始化LCD
	Adc_Init(); 			//adc初始化	
	Dac1_Init();		 	//DAC通道1初始化	   
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
	LCD_ShowString(30,130,200,16,16,"KEY_UP:+  KEY1:-");	
	//显示提示信息											      
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(30,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V");	    
	DAC->DHR12R1=(Um+V);//初始值为1.0	   
	USART_handler();
    
	while(1)
	{
//		t++;
//		key=KEY_Scan(0);			
//	   if(key==KEY0_PRES)	//发送正弦波1.0
//		{ 
//		  V=0.0;
//		  SineWave_Data( DL ,DualSine12bit);     //生成输出正弦波的波形表	
//		  DAC->DHR12R1=(Um+V);		//输出	
//		}
//		 else if(key==WKUP_PRES)//Um增大
//		{			
//			V+=0.05;
//		    SineWave_Data( DL ,DualSine12bit);     //生成输出正弦波的波形表	
//			DAC->DHR12R1=(Um+V);		//输出	
//		}
//		else if(key==KEY1_PRES)	//Um减小
//		{
//			V-=0.05;
//		    SineWave_Data( DL ,DualSine12bit);     //生成输出正弦波的波形表	
//		    DAC->DHR12R1=(Um+V);		//输出	
//		}	 
//		else if(key==KEY2_PRES)	//停止正弦波
//		{
//		    V=0.0;
//			SineWave_Data( DL ,DualSine12bit);     //生成输出正弦波的波形表	
//			DAC->DHR12R1=(Um+V);		//输出	
//		}
		
		if(t==10||key==KEY1_PRES||key==WKUP_PRES) 	//WKUP/KEY1按下了,或者定时时间到了
		{	  
 			adcx=DAC->DHR12R1;
			LCD_ShowxNum(94,150,adcx,4,16,0);     	//显示DAC寄存器值
			temp=(float)adcx*(3.3/4096);			//得到DAC电压值
			adcx=temp;
 			LCD_ShowxNum(94,170,temp,1,16,0);     	//显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,170,temp,3,16,0X80); 	//显示电压值的小数部分
 			adcx=Get_Adc_Average(ADC_CH1,10);		//得到ADC转换值	  
			temp=(float)adcx*(3.3/4096);			//得到ADC电压值
			adcx=temp;
 			LCD_ShowxNum(94,190,temp,1,16,0);     	//显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,190,temp,3,16,0X80); 	//显示电压值的小数部分
			LED1=0;	   
			t=0;
		}	    
		delay_ms(10);	

	}
}

void USART_handler()
{  
       u8 len;
       u32 hz;                //获取HZ频率
       float dac_max,dac_min; //获取DAC峰值     

       if(USART_RX_STA&0x8000)
       { 
              len=USART_RX_STA&0x2F;
              USART_RX_BUF[len]=0;
              sscanf((char *)USART_RX_BUF,"%d,%f,%f",&hz,&dac_max,&dac_min);
              printf("SET  HZ = %d, MAX = %f,MIN = %f\r\n", hz,dac_max,dac_min);

              Set_Sine12bit(dac_max,dac_min);        //更改峰值
          //    Set_Period( hz);                       //更改频率
			SineWave1_Init(50);//正弦波初始化，参数为50Hz	
              USART_RX_STA=0;
       }
}

//20190508
    void SineWave_DMA_Config(void)
{
DMA_InitTypeDef DMA_InitStructure;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//初始化DMA2的时钟

DMA_DeInit(DMA2_Channel3); //将DMA配置成默认值
DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1;//指定DMA2通道3的目标地址为DAC1_DHR12R1
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DualSine12bit;//指定DMA的源地址为数组Sine12bit
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//外设作为数据传输的目的地
DMA_InitStructure.DMA_BufferSize = sizeof(DualSine12bit)/2;//DMA缓冲区大小
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设机地址存器不变
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据宽度为半字
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//内存数据宽度为半字
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//工作在循环缓存模式，数据传输数为0时，自动恢复配置初值
DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//非常高优先级
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//通道未被设置成内存到内存模式，与循环模式相对
DMA_Init(DMA2_Channel3, &DMA_InitStructure);//初始化DMA

DMA_DeInit(DMA2_Channel4);
DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2;//指定DMA2通道3的目标地址为DAC2_DHR12R2
DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
DMA_Init(DMA2_Channel4, &DMA_InitStructure);

DMA_Cmd(DMA2_Channel3, ENABLE); //使能DMA的channel3
DMA_Cmd(DMA2_Channel4, ENABLE); //使能DMA的channel4
}
	
//定时器配置
/*********定时器初始化************/
void SineWave_TIM_Config(u32 Wave1_Fre)
{
    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//开时钟
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;     //不预分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //不分频<br>　　TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseStructure.TIM_Period = Wave1_Fre;//设置输出频率
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//设置TIME输出触发为更新模式
}


	
void SineWave1_Init(u16 Wave1_Fre)
{
       
	u16 f1=(u16)(72000000/sizeof(DualSine12bit)*2/Wave1_Fre);//计算频率
    SineWave_GPIO_Config();             //初始化io
    SineWave_TIM_Config(f1);            //初始化定时器
    SineWave_DAC_Config();              //配置DAC
	SineWave_DMA_Config();
    TIM_Cmd(TIM2, ENABLE);             //开启定时器
}

