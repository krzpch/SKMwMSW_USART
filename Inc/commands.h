/*
 * commands.h
 *
 *  Created on: 8 kwi 2021
 *      Author: polch
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#include "stm32l4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

#define COMMAND_MAX_LENGTH 50
#define OUTPUT_MAX_LENGTH 100

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void analyze(char input);
void check_command(char* command);

#endif /* INC_COMMANDS_H_ */
