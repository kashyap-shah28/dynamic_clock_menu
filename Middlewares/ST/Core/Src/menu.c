/*
 * menu.c
 *
 *  Created on: Jun 11, 2024
 *      Author: kashy
 */

#include "menu.h"
#include "rtc.h"
#include "lcd.h"
#include <string.h>
#include <stdio.h>



extern char key_stored;
extern char date[];
extern char time[];


char* menu_display_string[4] = {"F1-> Get Date",
		"F2-> Get Time",
		"F3-> Set Date",
		"F4-> Set Time"};

PageFunction_t page_functions[] = {
    {HOME_PAGE, home_page_screen, home_page_key_handler},
    {MENU_PAGE, menu_screen, menu_key_handler},
    {F1_PAGE, f1_page_screen, f1_page_key_handler},
    {F2_PAGE, f2_page_screen, f2_page_key_handler},
    {F3_PAGE, set_date_screen, set_date_key_handler},
    {F4_PAGE, set_hour_screen, set_hour_key_handler},
};
static PageId_t page_menu_id = HOME_PAGE;
static F3MenuIndex_t f3_menu_index = SET_DATE;
static F4MenuIndex_t f4_menu_index = SET_HOUR;

static char menu_index =0;
static int day, month, year;
static int hour, minute, second;
static char user_input[3];

static int date_valid = 0;
static int time_valid = 0;

void user_input_append(char key) {
    int len = strlen(user_input);
    if (len < sizeof(user_input) - 1) {
        user_input[len] = key;
        user_input[len + 1] = '\0';
        LCD_SendData(key);
        printf("%c", key);
    }
}

void user_input_clear(void) {
    memset(user_input, 0, sizeof(user_input));
}

int validate_full_date(int day, int month, int year) {
    if (day < 1) return 0;

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return day <= 31;
        case 4: case 6: case 9: case 11:
            return day <= 30;
        case 2:
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
                return day <= 29; // Leap year
            } else {
                return day <= 28;
            }
        default:
            return 0;
    }
}

void handle_key_press(char key) {
    page_functions[page_menu_id].key_fn(key);
}

void home_page_screen(void) {
    LCD_Clear();
    LCD_DisplayString(Line_1, "Home Page");
    LCD_DisplayString(Line_2, "Press Enter");
    printf("Home Page\nPress Enter\n");
}

void home_page_key_handler(char key) {
    if (key == '\n') { // Enter key
        page_menu_id = MENU_PAGE;
        page_functions[page_menu_id].page_fn();
    }
}

void menu_screen(void) {
    LCD_Clear();
    if(menu_index>=0 && menu_index<=2){
    LCD_DisplayString(Line_1, menu_display_string[menu_index]);
    LCD_DisplayString(Line_2, menu_display_string[menu_index+1]);
    printf("%s\n%s",menu_display_string[menu_index],menu_display_string[menu_index+1]);
    }


}
void menu_key_handler(char key) {
	if (key == 'v') { // Down key
		menu_index++;
        page_functions[page_menu_id].page_fn();
	} else if (key == '^') { // Up key
		menu_index--;
        page_functions[page_menu_id].page_fn();
	} else if (key == '!') { // F1 key
		page_menu_id = F1_PAGE;
        page_functions[page_menu_id].page_fn();
    } else if (key == '@') { // F2 key
        page_menu_id = F2_PAGE;
        page_functions[page_menu_id].page_fn();
    } else if (key == '#') { // F3 key
        page_menu_id = F3_PAGE;
        f3_menu_index = SET_DATE;
        page_functions[page_menu_id].page_fn();
    } else if (key == '$') { // F4 key
        page_menu_id = F4_PAGE;
        f4_menu_index = SET_HOUR;
        page_functions[page_menu_id].page_fn();
    } else if (key == '~') { // Escape key
        page_menu_id = HOME_PAGE;
        page_functions[page_menu_id].page_fn();
    }
}

void f1_page_screen(void) {
    rtc_get_date();
    LCD_Clear();
    LCD_DisplayString(Line_1, "Date:");
    LCD_DisplayString(Line_2, date);
    printf("Date:\n%s\n", date);
}

void f1_page_key_handler(char key) {
    if (key == '\n') { // Enter key
        page_menu_id = MENU_PAGE;
        page_functions[page_menu_id].page_fn();
    } else if (key == '~') { // Escape key
        page_menu_id = HOME_PAGE;
        page_functions[page_menu_id].page_fn();
    }
}

void f2_page_screen(void) {
    rtc_get_time();
    LCD_Clear();
    LCD_DisplayString(Line_1, "Time:");
    LCD_DisplayString(Line_2, time);
    printf("Time:\n%s\n", time);
}

void f2_page_key_handler(char key) {
    if (key == '\n') { // Enter key
        page_menu_id = MENU_PAGE;
        page_functions[page_menu_id].page_fn();
    } else if (key == '~') { // Escape key
        page_menu_id = HOME_PAGE;
        page_functions[page_menu_id].page_fn();
    }
}

void set_date_screen(void) {
    LCD_Clear();
    LCD_DisplayString(Line_1, "Set Date (1-31):");
    LCD_DisplayString(Line_2, user_input);
    printf("Set Date (1-31):\n%s\n", user_input);
}

void set_date_key_handler(char key) {
    if (key == '\n') {
        day = atoi(user_input);
        if (day >= 1 && day <= 31) {
            f3_menu_index = SET_MONTH;
            user_input_clear();
            set_month_screen();

            page_functions[page_menu_id].page_fn();
        } else {
            date_valid = 0;
            f3_menu_index = EXIT_MENU;
            exit_menu_screen();
        }
    } else {
        user_input_append(key);
    }
}

void set_month_screen(void) {
    LCD_Clear();
    LCD_DisplayString(Line_1, "Set Month (1-12):");
    LCD_DisplayString(Line_2, user_input);
    printf("Set Month (1-12):\n%s\n", user_input);
}

void set_month_key_handler(char key) {
    if (key == '\n') {
        month = atoi(user_input);
        if (month >= 1 && month <= 12) {
            f3_menu_index = SET_YEAR;
            user_input_clear();
            set_year_screen();
        } else {
            date_valid = 0;
            f3_menu_index = EXIT_MENU;
            exit_menu_screen();
        }
    } else {
        user_input_append(key);
    }
}

void set_year_screen(void) {
    LCD_Clear();
    LCD_DisplayString(Line_1, "Set Year (00-99):");
    LCD_DisplayString(Line_2, user_input);
    printf("Set Year (00-99):\n%s\n", user_input);
}

void set_year_key_handler(char key) {
    if (key == '\n') {
        year = atoi(user_input) + 2000;
        if (validate_full_date(day, month, year)) {
            date_valid = 1;
            f3_menu_index = EXIT_MENU;
            exit_menu_screen();
        } else {
            date_valid = 0;
            f3_menu_index = EXIT_MENU;
            exit_menu_screen();
        }
        user_input_clear();
    } else {
        user_input_append(key);
    }
}

void exit_menu_screen(void) {
    LCD_Clear();
    if (date_valid) {
        LCD_DisplayString(Line_1, "Date Set");
        LCD_DisplayString(Line_2, "");
        printf("Date Set\n");
    } else {
        LCD_DisplayString(Line_1, "Invalid Date");
        LCD_DisplayString(Line_2, "Try Again");
        printf("Invalid Date\nTry Again\n");
    }
}

void exit_menu_key_handler(char key) {
    if (key == '\n') {
        if (!date_valid) {
            f3_menu_index = SET_DATE;
            set_date_screen();
        } else {
            page_menu_id = MENU_PAGE;
            menu_screen();
        }
    }
}

void set_hour_screen(void) {
    LCD_Clear();
    LCD_DisplayString(Line_1, "Set Hour (0-23):");
    LCD_DisplayString(Line_2, user_input);
    printf("Set Hour (0-23):\n%s\n", user_input);
}

void set_hour_key_handler(char key) {
    if (key == '\n') {
        hour = atoi(user_input);
        if (hour >= 0 && hour <= 23) {
            f4_menu_index = SET_MINUTE;
            user_input_clear();
            set_minute_screen();
        } else {
            time_valid = 0;
            f4_menu_index = EXIT_TIME_MENU;
            exit_time_menu_screen();
        }
    } else {
        user_input_append(key);
    }
}

void set_minute_screen(void) {
    LCD_Clear();
    LCD_DisplayString(Line_1, "Set Minute (0-59):");
    LCD_DisplayString(Line_2, user_input);
    printf("Set Minute (0-59):\n%s\n", user_input);
}

void set_minute_key_handler(char key) {
    if (key == '\n') {
        minute = atoi(user_input);
        if (minute >= 0 && minute <= 59) {
            f4_menu_index = SET_SECOND;
            user_input_clear();
            set_second_screen();
        } else {
            time_valid = 0;
            f4_menu_index = EXIT_TIME_MENU;
            exit_time_menu_screen();
        }
    } else {
        user_input_append(key);
    }
}

void set_second_screen(void) {
    LCD_Clear();
    LCD_DisplayString(Line_1, "Set Second (0-59):");
    LCD_DisplayString(Line_2, user_input);
    printf("Set Second (0-59):\n%s\n", user_input);
}

void set_second_key_handler(char key) {
    if (key == '\n') {
        second = atoi(user_input);
        if (second >= 0 && second <= 59) {
            time_valid = 1;
            f4_menu_index = EXIT_TIME_MENU;
            rtc_update_time(hour, minute, second);
            exit_time_menu_screen();
        } else {
            time_valid = 0;
            f4_menu_index = EXIT_TIME_MENU;
            exit_time_menu_screen();
        }
        user_input_clear();
    } else {
        user_input_append(key);
    }
}

void exit_time_menu_screen(void) {
    LCD_Clear();
    if (time_valid) {
        LCD_DisplayString(Line_1, "Time Set");
        LCD_DisplayString(Line_2, "");
        printf("Time Set\n");
    } else {
        LCD_DisplayString(Line_1, "Invalid Time");
        LCD_DisplayString(Line_2, "Try Again");
        printf("Invalid Time\nTry Again\n");
    }
}

void exit_time_menu_key_handler(char key) {
    if (key == '\n') {
        if (!time_valid) {
            f4_menu_index = SET_HOUR;
            set_hour_screen();
        } else {
            page_menu_id = MENU_PAGE;
            menu_screen();
        }
    }
}
