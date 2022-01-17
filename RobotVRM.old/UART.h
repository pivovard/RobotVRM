/*
 * UART.h
 *
 *  Created on: 19. 5. 2020
 *      Author: pivov
 */

#ifndef UART_H_
#define UART_H_

#include "includes.h"

extern int command;

unsigned char buffer[9];

void UART_Init();

#endif /* UART_H_ */
