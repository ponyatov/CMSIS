/** @file
 * @brief `f0discovery` demo program

 - @ref STM32F051R8 microcontroller featuring
 - 64 KB Flash memory, 8 KB RAM
 - in an LQFP64 package

 * */

#include "stm32f0_discovery.h"
#include "stm32f0xx_hal.h"

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

	// Initializes the CPU clock, AHB and APB peripheral busses clocks

    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    RCC_ClkInitStruct.ClockType			= \
    	RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource		= RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider		= RCC_SYSCLK_DIV16;	// HSI:16max slow
    RCC_ClkInitStruct.APB1CLKDivider	= RCC_HCLK_DIV16;			// poke

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    	_Error_Handler(__FILE__, __LINE__);

    // SysTick

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);			// interrupt time
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);	// clock
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);				// IRQ

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

	__HAL_RCC_GPIOA_CLK_ENABLE();	// USER_BUTTON_GPIO_PORT			GPIOA

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* Configure USER_BUTTON */
	GPIO_InitStruct.Pin		= B1_Pin;
	GPIO_InitStruct.Mode	= GPIO_MODE_EVT_RISING;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

}

/// init LEDs
void init_LEDs(void) {

	__HAL_RCC_GPIOC_CLK_ENABLE();	// LED3_GPIO_PORT LED4_GPIO_PORT	GPIOC

	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, LD3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LD4_Pin, GPIO_PIN_SET);

	/*Configure LED3_GPIO LED4_GPIO */
	GPIO_InitStruct.Pin		= LD4_Pin|LD3_Pin;
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

	/* LED3_GPIO LED4_GPIO */
	GPIO_InitStruct.Pin		= LD4_Pin|LD3_Pin;
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}

/// oscilloscope connection pin
#define OSCILL_PIN		GPIO_PIN_9
/// oscilloscope connection port
#define OSCILL_PORT		GPIOA

/// init oscilloscope output
void init_oscill() {

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	/* OSCILL_PIN */
	GPIO_InitStruct.Pin		= OSCILL_PIN;
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(OSCILL_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(OSCILL_PORT, OSCILL_PIN, GPIO_PIN_RESET);

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

	init_buttons();
	init_oscill();
	init_LEDs();

}

void SysTick_Handler(void)
{
	HAL_IncTick(); HAL_SYSTICK_IRQHandler();		// don't delete (!)
	HAL_GPIO_TogglePin(OSCILL_PORT, OSCILL_PIN);
}

/// LED3 blink demo
void demo_blink(void) {
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LD3_Pin);
}

/// button -> LED3 copy demo
void demo_button(void) {
	register uint8_t button = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
	if (button)	HAL_GPIO_WritePin(LED_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	else		HAL_GPIO_WritePin(LED_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}

/// event loop
void loop(void) {
//	demo_blink();
//	demo_button();
	HAL_Delay(500);
}

/// firmware entry point
void main(void) {
	init_core(); init_GPIO(); init_UARTs();		// don't delete
	init();										// user init()
	for(;;) loop();								// user loop()
}
