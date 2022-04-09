/*
 * debug.c
 *
 *  Created on: Mar 12, 2022
 *      Author: sees1
 */


#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "usart.h"
#include "motor.h"
#include "debug.h"

int _write(int file, char *p, int len)
{
	HAL_UART_Transmit(&huart2, p, len, 10);

	return len;
}

void vprint(const char *fmt, va_list argp) {
	char string[200];
	if (0 < vsprintf(string, fmt, argp))
	{
		HAL_UART_Transmit(&huart2, (uint8_t*) string, strlen(string), 0xffffff);
	}
}

void User_Printf(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vprint(fmt, argp);
	va_end(argp);
}

void MotorTest()
{
	MotorOn(GPIOA, BACK_IN_1_Pin, BACK_IN_2_Pin); // bl
	HAL_Delay(5000);
	MotorOn(GPIOC, BACK_IN_3_Pin, BACK_IN_4_Pin); // br
	HAL_Delay(5000);
	MotorOn(GPIOB, FRONT_IN_2_Pin, FRONT_IN_1_Pin); // fr
	HAL_Delay(5000);
	MotorOn(GPIOA, FRONT_IN_3_Pin, FRONT_IN_4_Pin); // fl
	HAL_Delay(5000);

	MotorOff(GPIOA, BACK_IN_1_Pin, BACK_IN_2_Pin);
	MotorOff(GPIOC, BACK_IN_3_Pin, BACK_IN_4_Pin);
	MotorOff(GPIOB, FRONT_IN_2_Pin, FRONT_IN_1_Pin);
	MotorOff(GPIOA, FRONT_IN_3_Pin, FRONT_IN_4_Pin);
	HAL_Delay(2000);


}
