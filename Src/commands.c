/*
 * commands.c
 *
 *  Created on: 8 kwi 2021
 *      Author: polch
 */

#include "commands.h"

uint8_t input, output[40];
uint16_t output_len;

char temp[50];

void analyze()
{
	if(huart->Instance == USART2)
		{
			if(input == 'h')
			{
				output_len = sprintf((char *)output, "'e' - DIODA ON\n'd' - DIODA OFF\n");

			}
			else if(input == 'e')
			{
				HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
				output_len = sprintf((char *)output, "DIODA ON\n");
			}
			else if(input == 'd')
			{
				HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
				output_len = sprintf((char *)output, "DIODA OFF\n");
			}
			else
			{
				output_len = sprintf((char *)output, "ZLY ZNAK\n");
			}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

		HAL_UART_Transmit_IT(&huart2, output, output_len);
		HAL_UART_Receive_IT(&huart2, &input, 1);
	}
}
