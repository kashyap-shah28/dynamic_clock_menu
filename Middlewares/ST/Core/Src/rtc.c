/*
 * rtc.c
 *
 *  Created on: Jun 7, 2024
 *      Author: ADMIN
 */

#include"rtc.h"
#include"stm32f4xx.h"
#include<stdio.h>
//#include"main.h"
extern char time[10],date[10];
void rtc_get_time_and_date(void)
{
 Date_Struct Dates;
 Time_Struct Times;

 uint32_t time_register = Time_Value;
 uint32_t date_register = Date_Value;
/* Get the RTC current Time */
 Times.Hours = (time_register & 0x3F0000) >> 16;
 Times.Minutes = (time_register & 0x7F00) >> 8;
 Times.Seconds = (time_register & 0x7F) >> 0;

 Dates.Year = (date_register & 0xFF0000) >> 16;
 Dates.Month = (date_register & 0x1F00) >> 8;
 Dates.Date = (date_register & 0x3F) >> 0;
 // HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
// HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display time Format: hh:mm:ss */
 sprintf((char*)time,"%02d:%02d:%02d",rtc_bcd2bin(Times.Hours),rtc_bcd2bin(Times.Minutes), rtc_bcd2bin(Times.Seconds));
/* Display date Format: dd-mm-yy */
 sprintf((char*)date,"%02d-%02d-%2d",rtc_bcd2bin(Dates.Date), rtc_bcd2bin(Dates.Month), 2000 + rtc_bcd2bin(Dates.Year));
}

void rtc_get_time(void)
{

 Time_Struct Times;

 uint32_t time_register = Time_Value;

/* Get the RTC current Time */
 Times.Hours = (time_register & 0x3F0000) >> 16;
 Times.Minutes = (time_register & 0x7F00) >> 8;
 Times.Seconds = (time_register & 0x7F) >> 0;


 // HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
// HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display time Format: hh:mm:ss */
 sprintf((char*)time,"%02d:%02d:%02d",rtc_bcd2bin(Times.Hours),
rtc_bcd2bin(Times.Minutes), rtc_bcd2bin(Times.Seconds));
}

void rtc_get_date(void)
{
 Date_Struct Dates;


uint32_t date_register = Date_Value;
/* Get the RTC current Time */

 Dates.Year = (date_register & 0xFF0000) >> 16;
 Dates.Month = (date_register & 0x1F00) >> 8;
 Dates.Date = (date_register & 0x3F) >> 0;
 // HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
// HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display date Format: dd-mm-yy */
 sprintf((char*)date,"%02d-%02d-%2d",rtc_bcd2bin(Dates.Date), rtc_bcd2bin(Dates.Month), 2000 + rtc_bcd2bin(Dates.Year));
}

char rtc_bcd2bin(char value)
{
	char tens =  ((value & 0xF0)>> 4)*10;
	return tens + (value & 0x0F);
}

void rtc_update_time (char hr,char min,char sec)
{
  Time_Struct Times;
  uint32_t temp = 0;
  Times.Hours = rtc_bin2bcd(hr); // set hours
  Times.Minutes = rtc_bin2bcd(min); // set minutes
  Times.Seconds = rtc_bin2bcd(sec); // set seconds
  temp = ((Times.Hours << 16) | (Times.Minutes << 8) | (Times.Seconds));
//  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }
  rtc_enable_write();
  Time_Value = temp;
  rtc_disable_write();
}
 void rtc_update_date (char dd,char mm,char yy)
  {
    Date_Struct Dates;
    uint32_t temp = 0;
  Dates.Month = rtc_bin2bcd(mm); // month
  Dates.Date = rtc_bin2bcd(dd); // date
  Dates.Year = rtc_bin2bcd(yy); // year
  temp = (((char)Dates.Year << 16) | ((char)Dates.Month << 8) | ((char)Dates.Date));
//  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }
  //HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // backup register
  rtc_enable_write();
  Date_Value = temp;
    rtc_disable_write();
}

char rtc_bin2bcd(char value)
{
	char tens =  (value/10) << 4;
	return tens | (value%10) ;
}

void rtc_enable_write(void)
{
	/*Enable Backup access to config RTC*/
		PWR->CR |=PWR_CR_DBP;

		/*Disable RTC registers write protection*/
		RTC->WPR = RTC_WRITE_PROTECTION_ENABLE_1;
		RTC->WPR = RTC_WRITE_PROTECTION_ENABLE_2;


		/*Start init mode*/
		RTC->ISR |= RTC_ISR_INIT;

		/*Wait until Initializing mode is active*/
		while((RTC->ISR & RTC_ISR_INITF)!=RTC_ISR_INITF);
}
void rtc_disable_write(void)
{
	/*Exit the initialization mode*/
	RTC->ISR&=~RTC_ISR_INIT;

	/*Wait for sync*/
	while((RTC->ISR &RTC_ISR_INITF)==RTC_ISR_INITF);

	/*Enable RTC registers write protection*/
	RTC->WPR = 0xFF;
}
