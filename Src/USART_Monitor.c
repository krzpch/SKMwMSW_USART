/*
 * USART_Monitor.c
 *
 *  Created on: 8 kwi 2021
 *      Author: Krzysztof Półchłopek
 */

#include <USART_Monitor.h>

extern UART_HandleTypeDef UsedUSART;

uint8_t input, output[OUTPUT_MAX_LENGTH];
size_t output_len;
char command[COMMAND_MAX_LENGTH];
size_t command_len;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USED_USART)
	{
		analyze((char) input);
		HAL_UART_Receive_IT(&UsedUSART, &input, 1);
	}
} //end of void HAL_UART_RxCpltCallback()

void Monitor_Init(void) {
	HAL_UART_Receive_IT(&UsedUSART, &input, 1);
}
void analyze(char input)
{
	if (command_len < COMMAND_MAX_LENGTH) {

		if (input == 13) { // usage of enter
			output_len = sprintf((char*) output, "\n\r");
			if (command[0] == '/') {
				check_command(command);
			}
			memset(command, 0, COMMAND_MAX_LENGTH);
			command_len = 0;
		} else if (input == 127) { // usage of backspace
			if (command_len > 0) {
				command_len--;
				command[command_len] = 0;
				output_len = sprintf((char*) output, "%c", input);
			}
		} else { // other usages
			output_len = sprintf((char*) output, "%c", input);
			command[command_len++] = input;
		}
		HAL_UART_Transmit_IT(&UsedUSART, output, output_len);
	}
}

void check_command(char* command)
{
	if (strcmp(command,"/help") == 0) {
		output_len = sprintf((char*) output, "\n\r-----help-----\n\r- /test1 -  show test\n\r- /test2 -  show test\n\r");
	} else if (strcmp(command,"/test1") == 0) {
		output_len = sprintf((char*) output, "\n\rCommand: %s\n\r",command);
	} else if (strcmp(command,"/test2") == 0) {
		output_len = sprintf((char*) output, "\n\rtest2\n\r");
	} else {
		output_len = sprintf((char*) output, "\n\r'%s' is wrong command!\n\rType '/help' for more info.\n\r", command);
	}
}
