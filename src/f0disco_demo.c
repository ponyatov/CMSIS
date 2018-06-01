/** @file
 * @brief `f0discovery` demo program

 - @ref STM32F051R8 microcontroller featuring
 - 64 KB Flash memory, 8 KB RAM
 - in an LQFP64 package

 * */

#include "stm32f0_discovery.h"
#include "stm32f0xx_hal.h"

void SystemClock_Config(void){

	// setup oscillator source

	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_OscInitStruct.OscillatorType	= RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState			= RCC_HSI_ON;				// 8 MHz
	RCC_OscInitStruct.HSEState			= RCC_HSE_OFF;
	RCC_OscInitStruct.LSIState			= RCC_LSI_OFF;				// 40000
	RCC_OscInitStruct.LSEState			= RCC_LSE_OFF;				// 32768
	RCC_OscInitStruct.PLL.PLLState		= RCC_PLL_OFF;				// no mult
	RCC_OscInitStruct.PLL.PLLSource		= RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PREDIV		= RCC_PREDIV_DIV1;
	RCC_OscInitStruct.PLL.PLLMUL		= RCC_PLL_MUL2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) while(1);

	// setup bus clocks

	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_ClkInitStruct.ClockType			= \
		RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource		= RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider		= RCC_SYSCLK_DIV1;		// 8max slow
	RCC_ClkInitStruct.APB1CLKDivider	= RCC_HCLK_DIV1;		// 8max poke
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!=HAL_OK) while(1);

	// peripheral clocks

	RCC_PeriphCLKInitTypeDef PeriphCLKInitStruct = { 0 };

}

void init_core(void) {
	HAL_Init();
	SystemClock_Config();
}

void init_buttons(void) {

	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin		= USER_BUTTON_PIN;
	GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;			// pulls done in scheme
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

void init_LEDs(void) {

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	GPIO_InitStruct.Pin		= LED3_PIN|LED4_PIN;	// LEDs
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;	// push/pull
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED4_GPIO_PORT, LED4_PIN, GPIO_PIN_SET);
}

#define OSCILL_PIN GPIO_PIN_9
#define OSCILL_PORT GPIOA
void init_oscill() {

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin		= OSCILL_PIN;
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(OSCILL_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(OSCILL_PORT, OSCILL_PIN, GPIO_PIN_SET);

}

void init(void) {
	init_core();
	init_buttons();
	init_oscill();
	init_LEDs();
}

void loop(void) {
//	HAL_Delay(1000);
	HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED4_PIN);
	HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
	HAL_GPIO_TogglePin(OSCILL_PORT, OSCILL_PIN);
//	register uint8_t button =
//				HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN);
//	if (button)	HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
//	else		HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_RESET);
}

void main(void) {
	init();
	for(;;) loop;
}
