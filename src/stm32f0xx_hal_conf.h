/** @file
 * @brief HAL configurator for STM32F0 samples
 *
 * @defgroup STM32F0_DISCOVERY_HAL_CONFIG
 * @brief `src/stm32f0xx_hal_conf.h`
 * @ingroup STM32F0_DISCOVERY
 * @{
 * */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_HAL_CONF_H
#define __STM32F0xx_HAL_CONF_H

#include "stm32f0xx_hal_def.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED

/* ######################### Oscillator Values adaptation ################### */

 /**
   * @brief Internal High Speed oscillator (HSI) value.
   *        This value is used by the RCC HAL module to compute the system frequency
   *        (when HSI is used as system clock source, directly or through the PLL).
   */
 #if !defined  (HSI_VALUE)
   #define HSI_VALUE            8000000U  /*!< Value of the Internal oscillator in Hz*/
 #endif /* HSI_VALUE */

 /**
   * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
   *        This value is used by the RCC HAL module to compute the system frequency
   *        (when HSE is used as system clock source, directly or through the PLL).
   */
 #if !defined  (HSE_VALUE)
   #define HSE_VALUE            8000000U  /*!< Value of the External oscillator in Hz */
 #endif /* HSE_VALUE */

/**
   * @brief In the following line adjust the External High Speed oscillator (HSE) Startup
   *        Timeout value
   */
 #if !defined  (HSE_STARTUP_TIMEOUT)
   #define HSE_STARTUP_TIMEOUT  100U      /*!< Time out for HSE start up, in ms */
 #endif /* HSE_STARTUP_TIMEOUT */

 /**
   * @brief Time out for LSE start up value in ms.
   */
 #if !defined  (LSE_STARTUP_TIMEOUT)
   #define LSE_STARTUP_TIMEOUT  5000U     /*!< Time out for LSE start up, in ms */
 #endif /* LSE_STARTUP_TIMEOUT */

/* ########################### System Configuration ######################### */

#define  TICK_INT_PRIORITY            ((uint32_t)(1U<<__NVIC_PRIO_BITS) - 1U) /*!< tick interrupt priority (lowest by default)             */

/* ########################## Includes Selection ############################## */

#ifdef HAL_CORTEX_MODULE_ENABLED
 #include "stm32f0xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
 #include "stm32f0xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_RCC_MODULE_ENABLED
 #include "stm32f0xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
 #include "stm32f0xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

 /* ########################## Asserts ############################## */

 #ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((char *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(char* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_CONF_H */

/// @}
