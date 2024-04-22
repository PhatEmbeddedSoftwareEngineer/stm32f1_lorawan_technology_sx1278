/*
 * gpio.c
 *
 *  Created on: Mar 20, 2024
 *      Author: phat
 */


#include "gpio.h"

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */



	/*cau hinh nut nhan chan so pc13*/
	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = MODE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(MODE_GPIO_Port, &GPIO_InitStruct);

	/*cau hinh chan cs va chan led la output*/

	/*Configure GPIO pins : PAPin PAPin */
	GPIO_InitStruct.Pin = NSS_Pin|LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	/*cau hinh chan D0 la chan input*/

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = DIO0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DIO0_GPIO_Port, &GPIO_InitStruct);


	/*cau hinh chan reset la chan output*/

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RESET_GPIO_Port, &GPIO_InitStruct);


	/*dat chan cs cua stm32 len muc cao*/
	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);


	/*dat chan reset len muc cao*/
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);



}
