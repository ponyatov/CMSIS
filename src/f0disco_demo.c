/** @file
 * @brief `f0discovery` demo program

 - @ref STM32F051R8 microcontroller featuring
 - 64 KB Flash memory, 8 KB RAM
 - in an LQFP64 package

 * */

#include "stm32f0_discovery.h"
#include "stm32f0xx_hal.h"

void init_SysTick(void) {
}

/// @brief System Clock Configuration
void SystemClock_Config(void) {

	// Initializes oscillator sources

	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };

	RCC_OscInitStruct.OscillatorType	= RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState				= RCC_HSI_ON;			// 8 MHz
	RCC_OscInitStruct.HSICalibrationValue	= 0x10;
	RCC_OscInitStruct.HSEState				= RCC_HSE_OFF;			// no xtal
	RCC_OscInitStruct.PLL.PLLState			= RCC_PLL_NONE;			// no mult
//	RCC_OscInitStruct.PLL.PLLSource		= RCC_PLLSOURCE_HSI;
//	RCC_OscInitStruct.PLL.PREDIV		= RCC_PREDIV_DIV1;
//	RCC_OscInitStruct.PLL.PLLMUL		= RCC_PLL_MUL2;
//	RCC_OscInitStruct.LSIState			= RCC_LSI_OFF;				// 40000
//	RCC_OscInitStruct.LSEState			= RCC_LSE_OFF;				// 32768
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		_Error_Handler(__FILE__, __LINE__);

	// Initializes the CPU clock

    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    RCC_ClkInitStruct.ClockType			= \
    	RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource		= RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider		= RCC_SYSCLK_DIV16;	// HSI:16max slow
    RCC_ClkInitStruct.APB1CLKDivider	= RCC_HCLK_DIV16;			// poke

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    	_Error_Handler(__FILE__, __LINE__);

	// Initializes AHB and APB peripheral busses clocks

//	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

    // SysTick
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);			// interrupt time
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);	// clock
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);				// IRQ

    init_SysTick();

}

/// initialize only HAL, core clock and SysTick
void init_core(void) {
	/* Reset of all peripherals, Initializes the Flash interface and Systick */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
}

/// init GPIO
void init_GPIO(void) {

}

// init UART
void init_UARTs(void) {

	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	// USART1 clock

    PeriphClkInit.PeriphClockSelection	= RCC_PERIPHCLK_USART1;		// USART1
	PeriphClkInit.Usart1ClockSelection	= RCC_USART1CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		_Error_Handler(__FILE__, __LINE__);

}

/// init buttons
void init_buttons(void) {

	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin		= USER_BUTTON_PIN;
	GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;			// pulls done in scheme
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

/// init LEDs
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

/// oscilloscope connection pin
#define OSCILL_PIN GPIO_PIN_9
/// oscilloscope connection port
#define OSCILL_PORT GPIOA
/// init oscilloscope output
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

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

/// initizalize system in a whole
void init(void) {
	init_core();
	init_GPIO();
	init_UARTs();

//	init_buttons();
//	init_oscill();
	init_LEDs();
}

/// event loop
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

/// firmware entry point
void main(void) {
	init();
	for(;;) loop;
}
