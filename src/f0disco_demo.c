/** @file
 * @brief `f0discovery` demo program

 - @ref STM32F051R8 microcontroller featuring
 - 64 KB Flash memory, 8 KB RAM
 - in an LQFP64 package

 * */

#include "stm32f0_discovery.h"
#include "stm32f0xx_hal.h"


void GPIO_Init(void) {

	HAL_Init();

	GPIO_InitTypeDef GPIO_InitStruct;


}

void main(void) {
	GPIO_Init();
	//RCC_APB2PeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
//	GPIO_StructInit(&GPIO_InitStruct);
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	for(;;);
}
