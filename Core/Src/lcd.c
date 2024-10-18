/*
 * lcd.c
 *
 *  Created on: Jun 4, 2024
 *      Author: ADMIN
 */
#include"lcd.h"
#include"stm32f4xx.h"

void LCD_Init(void)
{
		EN_High;
		Delay(36750);//0
		EN_Low;
		LCD_SendCommand(0x03);
		LCD_SendCommand(0x03);
		Delay(205);//0
		LCD_SendCommand(0x03);
		LCD_SendCommand(0x02);
		LCD_SendCommand(0x04 | 0x08);
	  LCD_SendCommand(0x04 | 0x08);
	  Delay(205);//1
	  LCD_SendCommand(0x38);
	  //LCD_SendCommand(0x28);
	  Delay(205);//1
	  LCD_SendCommand(0x0E);
	  Delay(205);//1
	  LCD_SendCommand(0x0D);
	  Delay(205);//1
	  LCD_Clear();
	  LCD_SendCommand(0x06);
	  LCD_SendCommand(0x80);
	  Delay(1000);//None

//	  LCD_SendCommand(0x03);
//	  Delayms(5);//1
//	  Delayms(5);//1
//
//	  LCD_SendCommand(0x38);
//	  Delayms(5);//1
//
//	  LCD_SendCommand(0x06);
//	  Delayms(5);//1
//
//	  LCD_SendCommand(0x0D);
//	  Delayms(5);//1
//	  LCD_SendCommand(0x01);
//	  Delayms(5);//1

}
void LCD_SendCommand(int8_t command)
{
	RS_Low;
	Delay(6);//0

	EN_High;
	Delay(6);//0
	D_Port->ODR &= ~0xFF;
	D_Port->ODR |= (command & 0xFF);
	EN_Low;
	Delay(105);//1
	Delay(0x7FF);

}
void LCD_SendData(int8_t data)
{
	RS_High;
	Delay(6);//0

	EN_High;
	Delay(6);//0
	D_Port->ODR &= ~0xFF;
	D_Port->ODR |= (data & 0xFF);
	EN_Low;
	Delay(105);//1
}
void LCD_Clear(void)
{
	LCD_SendCommand(0x01);
	Delay(8033);//2
}
void LCD_WriteString(char* string)
{

	while(*string)
	{
		LCD_SendData(*string++);
		Delay(5);//1
	}
	LCD_SendCommand(0x0C);
	}

void LCD_DisplayString(char loc, char* string)
{
	if(loc == Line_1)
	{
		LCD_SendCommand(Line_1);
	}
	else if(loc == Line_2)
	{
		LCD_SendCommand(Line_2);
	}
	LCD_WriteString(string);
}
void Delay(int units)
{
	uint32_t counter = units * 0x0F;

	     while(counter--)
	    {
	        /* Delay Loop   */
	        //NOP();
	    }
}

void DelayMs(int units)
{
	for(;units > 0; units--)
		for(int i = 0; i<6000;i++);
}

void LCD_SecondLine(void)
{
	LCD_SendCommand(0xC0);
	Delay(5);//1
	}

int _write(int le, char *ptr, int len)
{
int DataIdx;
for(DataIdx = 0; DataIdx < len; DataIdx++)
{
	ITM_SendChar(*ptr++);
}
return len;
}
void LCD_FirstLine(void)
{
	LCD_SendCommand(0x80);
	Delay(5);//1
}
