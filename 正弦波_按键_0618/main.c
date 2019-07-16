/**
  ******************************************************************************
  **说明：创新ST_VC开发板 LED 测试程序
  **功能：板载4个LED轮流闪烁
  **作者：王云飞
  **日期：2011.5.20
  **Email:yunfei7370@gmail.com						
  **QQ：  534512025
  ******************************************************************************
**/ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "dac.h"
#include "key.h"
#include "DMA.h"
#include "time.h"
#include "delay.h"


/* Private functions ---------------------------------------------------------*/

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
	delay_init(72);
    key_init();	
	GPIO_Configuration();
	TIM2_Configuration();	
	DAC_Configuration();
	MDA_Configuration();
	led_init();	
	TIM_Cmd(TIM2, ENABLE);    
//	TIM2_Configuration();
//	GPIO_Configuration();    
//	DAC_Configuration();
  /* Infinite loop */
	while (1)
	{
//		delay_init(72);
	 key_test();
//	 DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
	}
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
