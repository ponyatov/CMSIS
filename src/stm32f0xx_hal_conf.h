/** @file
 * @brief HAL configurator for STM32F0 samples
 * */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_HAL_CONF_H
#define __STM32F0xx_HAL_CONF_H

#include "stm32f0xx_hal_def.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED


/* ########################## Includes Selection ############################## */

#ifdef HAL_GPIO_MODULE_ENABLED
 #include "stm32f0xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_CONF_H */
