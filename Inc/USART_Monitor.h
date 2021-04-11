/*
 * USART_Monitor.h
 *
 *  Created on: 8 kwi 2021
 *      Author: Krzysztof Półchłopek
 */

#ifndef INC_USART_MONITOR_H_
#define INC_USART_MONITOR_H_

#include "stm32l4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

#define COMMAND_MAX_LENGTH 50
#define OUTPUT_MAX_LENGTH 100
#define USED_USART USART2

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void Monitor_Init(void);
void analyze(char input);
void check_command(char* command);

#endif /* INC_USART_MONITOR_H_ */
