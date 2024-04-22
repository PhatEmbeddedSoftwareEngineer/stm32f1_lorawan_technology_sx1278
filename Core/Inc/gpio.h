/*
 * gpio.h
 *
 *  Created on: Mar 20, 2024
 *      Author: phat
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#define MODE_Pin GPIO_PIN_13
#define MODE_GPIO_Port GPIOC
#define NSS_Pin GPIO_PIN_4
#define NSS_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define DIO0_Pin GPIO_PIN_0
#define DIO0_GPIO_Port GPIOB
#define RESET_Pin GPIO_PIN_1
#define RESET_GPIO_Port GPIOB


#include "main.h"
extern SPI_HandleTypeDef hspi2;
void MX_GPIO_Init(void);


#endif /* INC_GPIO_H_ */
