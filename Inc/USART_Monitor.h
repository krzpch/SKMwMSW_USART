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
#include "usart.h"
#include <stdio.h>
#include <string.h>

#define COMMAND_MAX_LENGTH 50
#define OUTPUT_MAX_LENGTH 300
#define USED_USART huart2 //name of UART_HandleTypeDef structure used in communication

typedef struct
{
	float * f1;
	float * f2;
}USART_data;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void Monitor_Init(USART_data usart_data);
void analyze(char input);
void check_command(char* command);

#endif /* INC_USART_MONITOR_H_ */
