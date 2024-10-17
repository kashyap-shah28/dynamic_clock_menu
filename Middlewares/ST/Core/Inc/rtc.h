/*
 * rtc.h
 *
 *  Created on: Jun 7, 2024
 *      Author: ADMIN
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#define Time_Value RTC->TR
#define Date_Value RTC->DR
#define RTC_WRITE_PROTECTION_ENABLE_1 ((uint8_t)0xCAU)
#define RTC_WRITE_PROTECTION_ENABLE_2 ((uint8_t)0x53U)

typedef struct
{
  char Month;
  char Date;
  char Year;
} Date_Struct;

typedef struct
{
	char Hours;
	char Minutes;
	char Seconds;
} Time_Struct;

void rtc_get_time(void);
void rtc_get_date(void);
void rtc_get_time_and_date(void);
void rtc_update_time (char hr,char min,char sec);
void rtc_update_date (char dd,char mm,char yy);
char rtc_bcd2bin(char value);
char rtc_bin2bcd(char value);
void rtc_enable_write(void);
void rtc_disable_write(void);
#endif /* INC_RTC_H_ */
