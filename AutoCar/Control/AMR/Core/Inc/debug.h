/*
 * debug.h
 *
 *  Created on: Mar 12, 2022
 *      Author: sees1
 */

#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int _write(int file, char *p, int len);
void User_Printf(const char *fmt, ...);
void vprint(const char *fmt, va_list argp);
void MotorTest();

#endif /* INC_DEBUG_H_ */
