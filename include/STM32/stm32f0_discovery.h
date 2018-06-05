/**
 *
 * @defgroup clock Clock
 * @ingroup stm32
 *
 * @defgroup gpio GPIO
 * @ingroup stm32
 *
 * @defgroup uart UART
 * @brief Serial, and RS485/MODBUS
 * @ingroup stm32
 *
 * @defgroup led LED
 * @brief LEDs
 * @ingroup stm32
 *
 * @defgroup button Buttons
 * @brief Buttons
 * @ingroup stm32
 *
 *
 * */

/**
  ******************************************************************************
  * @file    stm32f0_discovery.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   This file contains definitions for STM32F0-Discovery's Leds, push-
  *          buttons hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0_DISCOVERY_H
#define __STM32F0_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32F0_DISCOVERY
  * @{
  */
      
/** @addtogroup STM32F0_DISCOVERY_LOW_LEVEL
  * @{
  */ 

/** @defgroup STM32F0_DISCOVERY_LOW_LEVEL_Exported_Types Exported_Types
  * @{
  */
/// Led_TypeDef
/// @ingroup led
typedef enum 
{
  LED3 = 0,
  LED4 = 1
} Led_TypeDef;

/// Button_TypeDef
/// @ingroup button
typedef enum 
{
  BUTTON_USER = 0,
} Button_TypeDef;

/// ButtonMode_TypeDef
/// @ingroup button
typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;
  
/**
  * @}
  */ 

/** @defgroup STM32F0_DISCOVERY_LOW_LEVEL_Exported_Constants Exported_Constants
  * @{
  */ 

/** @addtogroup STM32F0_DISCOVERY_LOW_LEVEL_LED
  * @{
  */

/// @ingroup led
/// @{

/// number of LEDs
#define LEDn                             2

/// LED3 pin
#define LED3_PIN                         GPIO_PIN_9
/// LED3 port C
#define LED3_GPIO_PORT                   GPIOC
/// LED3 port clock
#define LED3_GPIO_CLK                    RCC_AHBPeriph_GPIOC
  
/// LED4 pin
#define LED4_PIN                         GPIO_PIN_8
/// LED4 port C
#define LED4_GPIO_PORT                   GPIOC
/// LED4 port clock
#define LED4_GPIO_CLK                    RCC_AHBPeriph_GPIOC

/// @}

/**
  * @}
  */ 

/** @addtogroup SSTM32F0_DISCOVERY_LOW_LEVEL_BUTTON BUTTON
  * @{
  */  

/// @ingroup button
/// @{

/// one button
#define BUTTONn                          1

/**
 * @brief USER push-button
 */

/// button pin 0
#define USER_BUTTON_PIN                GPIO_PIN_0
/// button port A
#define USER_BUTTON_GPIO_PORT          GPIOA
/// GPIO clock
#define USER_BUTTON_GPIO_CLK           RCC_AHBPeriph_GPIOA
/// line0
#define USER_BUTTON_EXTI_LINE          EXTI_Line0
/// port source
#define USER_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
/// pin source
#define USER_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource0
/// pin IRQ
#define USER_BUTTON_EXTI_IRQn          EXTI0_1_IRQn

/// @}

/**
  * @}
  */ 
  
/// @ingroup uart
/// @{

/// USART1_TX
#define PA9								GPIO_PIN_9
#define USART1_TX_PIN					PA9
/// USART1 RX
#define PA10							GPIO_PIN_10
#define USART1_RX_PIN					PA10
/// USART1 PORT
#define USART1_PORT						GPIOA

/// USART1 Baud
#define USART1_RX_BAUD					115200

/// @}

/** @defgroup STM32F0_DISCOVERY_LOW_LEVEL_Exported_Macros Exported_Macros
  * @{
  */  
/**
  * @}
  */ 

/** @defgroup STM32F0_DISCOVERY_LOW_LEVEL_Exported_Functions Exported_Functions
  * @{
  */

/// @ingroup led
/// @{

/// initialize LEDs
void STM_EVAL_LEDInit(Led_TypeDef Led);
/// switch on
void STM_EVAL_LEDOn(Led_TypeDef Led);
/// switch off
void STM_EVAL_LEDOff(Led_TypeDef Led);
/// toggle LED
void STM_EVAL_LEDToggle(Led_TypeDef Led);

/// @}

/// @ingroup button
/// @{

/// initialize button
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
/// get button state
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);

/// }

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F0_DISCOVERY_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/// @}
/// @}
