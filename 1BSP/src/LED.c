/**
  ******************************************************************************
  * @file    IO_Toggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
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
#include "led.h"
/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}
void LED_Tog(unsigned char ledno)
{
	switch(ledno)
	{
		case(LED0):
			GPIO_ToggleBits(LED0_PORT, LED0_PIN);
//			GPIO_WriteBit(LED0_PORT, LED0_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN)));
			break;
		case(LED1):
			GPIO_WriteBit(LED1_PORT, LED1_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(LED1_PORT, LED1_PIN)));
			break;
		case(LED2):
			GPIO_WriteBit(LED2_PORT, LED2_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(LED2_PORT, LED2_PIN)));
			break;
		case(LED3):
			GPIO_WriteBit(LED3_PORT, LED3_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(LED3_PORT, LED3_PIN)));
			break;
		default:
			break;
	}
}

void LED_Off(unsigned char ledno)
{
	switch(ledno)
	{
		case(LED0):
			GPIO_SetBits(LED0_PORT, LED0_PIN);
			break;
		case(LED1):
			GPIO_SetBits(LED1_PORT, LED1_PIN);
			break;
		case(LED2):
			GPIO_SetBits(LED2_PORT, LED2_PIN);
			break;
		case(LED3):
			GPIO_SetBits(LED3_PORT, LED3_PIN);
			break;
		default:
			break;
	}
}
void LED_On(unsigned char ledno)
{
	switch(ledno)
	{
		case(LED0):
			GPIO_ResetBits(LED0_PORT, LED0_PIN);
			break;
		case(LED1):
			GPIO_ResetBits(LED1_PORT, LED1_PIN);
			break;
		case(LED2):
			GPIO_ResetBits(LED2_PORT, LED2_PIN);
			break;
		case(LED3):
			GPIO_ResetBits(LED3_PORT, LED3_PIN);
			break;
		default:
			break;
	}
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
