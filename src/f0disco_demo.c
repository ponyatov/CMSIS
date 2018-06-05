/** @file
 * @brief `f0discovery` demo program

 - @ref STM32F051R8 microcontroller featuring
 - 64 KB Flash memory, 8 KB RAM
 - in an LQFP64 package

 * */

#include "f0discovery.h"

/// @brief initialize system: user level
/// @ingroup cmsis
void init(void) {
}

/// @brief user systick
void systick(void) {
	HAL_GPIO_TogglePin(OSCILL_PORT, OSCILL_PIN);
}

/// @brief user loop
/// @ingroup cmsis
void loop(void) {
//	demo_blink();
//	demo_button();
	HAL_Delay(500);
}
