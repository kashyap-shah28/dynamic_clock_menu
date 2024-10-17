/*
 * uart.c
 *
 *  Created on: Jun 7, 2024
 *      Author: ADMIN
 */

#include"uart.h"

void UART4_SendChar(char c)
{

	Data_Register = c;   // LOad the Data
	while (!Tx_Ready);  // Wait for TC to SET.. This indicates that the data has been transmitted
}

char UART4_GetChar(void)
{
	char temp;
	while (!Rx_Ready);  // Wait for RXNE to SET.. This indicates that the data has been transmitted

	temp = (char)Data_Register;   // Read the Data
	return temp;
}
