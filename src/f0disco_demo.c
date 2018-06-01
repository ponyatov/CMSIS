/** @file
 * @brief `f0discovery` demo program

 - @ref STM32F051R8 microcontroller featuring
 - 64 KB Flash memory, 8 KB RAM
 - in an LQFP64 package

 * */

#include "stm32f0_discovery.h"
#include "stm32f0xx_hal.h"

void SystemClock_Config(void){}

void init_core(void) { 	HAL_Init(); SystemClock_Config(); }

void init_buttons(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin		= USER_BUTTON_PIN;
	GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;			// pulls done in scheme
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

void init_LEDs(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin		= LED3_PIN|LED4_PIN;	// LEDs
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;	// push/pull
	GPIO_InitStruct.Pull	= GPIO_PULLUP;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
	for(;;);
}

void init(void) { init_core();
	init_buttons();
	init_LEDs();
}

void loop(void) {
	uint8_t button = HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN);
	if (button)	HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
	else		HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_RESET);
}

void main(void) {
	init();
	for(;;) loop;
}
