/*
 * commands.c
 *
 *  Created on: 8 kwi 2021
 *      Author: polch
 */

#include "commands.h"

extern UART_HandleTypeDef huart2;

uint8_t input, output[OUTPUT_MAX_LENGTH];
size_t output_len;
uint8_t mode;
char command[COMMAND_MAX_LENGTH];


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		analyze((char) input);
		HAL_UART_Receive_IT(&huart2, &input, 1);
	}
} //end of void HAL_UART_RxCpltCallback()

void analyze(char input)
{

	if (input == '/') {
		mode = 1; // command mode
	} else if (input == 8) { // backspace
		//mode = 2; // remove character
	} else if (input == 13) { // enter
		mode = 3; // execute command
	}

	if (mode == 1) {
		strncat(command,&input,1);
	} else if (mode == 2) { // WIP
		char temp[COMMAND_MAX_LENGTH];
		strncpy(temp,command,strlen(command)-1);
		strncpy(command,temp,strlen(temp));
	} else if (command[0] == '/' && mode == 3) {
		check_command(command);
		memset(command,0,COMMAND_MAX_LENGTH);
		mode = 0;
	} else {
		output_len = sprintf((char*) output, "%c", input);
		HAL_UART_Transmit_IT(&huart2, output, output_len);
	}
}

void check_command(char* command)
{
	if (strcmp(command,"/help") == 0) {
		output_len = sprintf((char*) output, "-----help-----\n- /test -  show test\n");
	} else if (strcmp(command,"/test") == 0) {
		output_len = sprintf((char*) output, "test\n");
	} else {
		output_len = sprintf((char*) output, "'%s' is wrong command!\n", command);
	}
	HAL_UART_Transmit_IT(&huart2, output, output_len);
}
