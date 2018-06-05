/** @file
 * @brief `f0discovery` BSP

 - @ref STM32F051R8 microcontroller featuring
 - 64 KB Flash memory, 8 KB RAM
 - in an LQFP64 package

 * */

#ifndef _H_F0DISCOVERY_BSP
#define _H_F0DISCOVERY_BSP

#include "stm32f0_discovery.h"
#include "stm32f0xx_hal.h"

/// @brief System Clock Configuration
/// @ingroup clock
void SystemClock_Config(void);

/// @brief initialize only HAL, core clock and SysTick
/// @ingroup cmsis
void init_core(void);

/// @brief init all used GPIO
/// @ingroup cmsis
void init_GPIO(void);

/// @brief firmware entry point
/// @ingroup cmsis
void main(void);

/// @brief init UART
/// @ingroup cmsis
void init_UARTs(void);

/// @brief init buttons
/// @ingroup cmsis
void init_buttons(void);

/// @brief init LEDs
/// @ingroup cmsis
void init_LEDs(void);

/// @brief oscilloscope connection pin
/// @ingroup cmsis
#define OSCILL_PIN		GPIO_PIN_9
/// @brief oscilloscope connection port
/// @ingroup cmsis
#define OSCILL_PORT		GPIOA

/// @brief init oscilloscope output
/// @ingroup cmsis
void init_oscill();

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
/// @ingroup cmsis
void _Error_Handler(char *file, int line);

/// @brief initizalize system: user level
/// @ingroup cmsis
void init(void);

/// @brief SysTick interrupt callback
/// @ingroup clock
void SysTick_Handler(void);

/// @brief user systick
/// @ingroup cmsis
void systick(void);

/// @brief LED3 blink demo
/// @ingroup cmsis
void demo_blink(void);

/// @brief button -> LED3 copy demo
/// @ingroup cmsis
void demo_button(void);

/// @brief event loop
/// @ingroup cmsis
void loop(void);

#endif // _H_F0DISCOVERY_BSP
