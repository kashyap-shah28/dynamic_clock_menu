/*
 * lcd.h
 *
 *  Created on: Jun 4, 2024
 *      Author: ADMIN
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include"stm32f4xx.h"
#define Set_High 0
#define Set_Low 16
/*ENABLE Pin at PC12*/
#define EN_Pin GPIO_PIN_12
#define EN_Port GPIOC
#define EN_High (EN_Port->BSRR = EN_Pin << Set_High)
#define EN_Low (EN_Port->BSRR = EN_Pin << Set_Low)

/*RS Register Select Pin at PB9 RS=0 -> Command RS=1 -> DATA */
#define RS_Pin GPIO_PIN_9
#define RS_Port GPIOB
#define RS_High (RS_Port->BSRR = RS_Pin << Set_High)
#define RS_Low (RS_Port->BSRR = RS_Pin << Set_Low)

/*DATA Pins at PD0-PD7*/
#define D_Port GPIOD

#define D0_Pin GPIO_PIN_0
#define D1_Pin GPIO_PIN_1
#define D2_Pin GPIO_PIN_2
#define D3_Pin GPIO_PIN_3
#define D4_Pin GPIO_PIN_4
#define D5_Pin GPIO_PIN_5
#define D6_Pin GPIO_PIN_6
#define D7_Pin GPIO_PIN_7

#define Data_Output (D_Port->ODR)

#define Line_1 0x80
#define Line_2 0xC0
//void Set_Mode(char* GPIOx_Port, char* Pin_No, char* Mode);
//void Set_Bit_Value(char* GPIOx_Port, char* Pin_No, uint8_t Bit_Value);

void LCD_Init(void);
void LCD_SendCommand(int8_t command);
void LCD_SendData(int8_t data);
void LCD_Clear(void);
void LCD_WriteString(char* string);
void LCD_FirstLine(void);
void LCD_SecondLine(void);
void LCD_DisplayString(char loc, char* string);
void Delay(int units);
int _write(int le, char *ptr, int len);
#endif /* INC_LCD_H_ */
