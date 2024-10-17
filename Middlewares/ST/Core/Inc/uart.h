/*
 * uart.h
 *
 *  Created on: Jun 7, 2024
 *      Author: ADMIN
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include"stm32f4xx.h"

#define Data_Register (UART4->DR)
#define Tx_Ready (UART4->SR & (1<<6))
#define Rx_Ready (UART4->SR & (1<<5))
void UART4_SendChar(char c);
char UART4_GetChar(void);

#endif /* INC_UART_H_ */
