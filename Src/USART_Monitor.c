/*
 * USART_Monitor.c
 *
 *  Created on: 8 kwi 2021
 *      Author: Krzysztof Półchłopek
 */

#include "USART_Monitor.h"

UART_HandleTypeDef * UsedUSART = &USED_USART;

USART_data data;
uint8_t input, output[OUTPUT_MAX_LENGTH];
size_t output_len;
char command[COMMAND_MAX_LENGTH];
size_t command_len;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UsedUSART->Instance)
	{
		analyze((char) input);
		HAL_UART_Receive_IT(UsedUSART, &input, 1);
	}
} //end of void HAL_UART_RxCpltCallback()

void Monitor_Init(USART_data usart_data) {
	data = usart_data;
	HAL_UART_Receive_IT(UsedUSART, &input, 1);

}
void analyze(char input)
{
	if (input == 13) { // usage of enter
				output_len = sprintf((char*) output, "\n\r");
				if (command[0] == '/') {
					check_command(command);
				}
				memset(command, 0, COMMAND_MAX_LENGTH);
				command_len = 0;
			}
	else if (command_len < COMMAND_MAX_LENGTH) {

		 if (input == 127) { // usage of backspace
			if (command_len > 0) {
				command_len--;
				command[command_len] = 0;
				output_len = sprintf((char*) output, "%c", input);
			}
		} else { // other usages
			output_len = sprintf((char*) output, "%c", input);
			command[command_len++] = input;
		}
	}
	HAL_UART_Transmit_IT(UsedUSART, output, output_len);
}

void check_command(char* command)
{
	if (strcmp(command,"/help") == 0) {
		output_len =
				sprintf((char*) output, "\n\r-------help-------\n\r"
						"- /get_ticks -  show ticks elapsed since startup \n\r"
						"- /diode_on -  turns diode on\n\r"
						"- /diode_off -  turns diode off\n\r"
						"- /get_temp - prints temperature measured by sensor\n\r"
						"- /get_hum - prints humidity measured by sensor\n\r");
	} else if (strcmp(command,"/get_ticks") == 0) {
		output_len = sprintf((char*) output, "\n\rTicks elapsed since startup: %lu\n\r",HAL_GetTick());
	} else if (strcmp(command,"/diode_on") == 0) {
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		output_len = sprintf((char*) output, "\n\rDiode was turned ON\n\r");
	} else if (strcmp(command,"/diode_off") == 0) {
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
		output_len = sprintf((char*) output, "\n\rDiode was turned OFF\n\r");
	} else if (strcmp(command,"/get_temp") == 0) {
		output_len = sprintf((char*) output, "\n\rTemp: %.1f %cC\n\r",*data.f1, (char)176);
	} else if (strcmp(command,"/get_hum") == 0) {
		output_len = sprintf((char*) output, "\n\rHum: %.1f %%RH\n\r",*data.f2);
	} else {
		output_len = sprintf((char*) output, "\n\r'%s' is wrong command!\n\rType '/help' for more info.\n\r", command);
	}
}
