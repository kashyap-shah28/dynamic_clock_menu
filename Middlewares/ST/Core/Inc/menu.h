#ifndef MENU_H
#define MENU_H

typedef enum {
    HOME_PAGE,
    MENU_PAGE,
    F1_PAGE,
    F2_PAGE,
    F3_PAGE,
    F4_PAGE,
} PageId_t;

typedef enum {
    SET_DATE,
    SET_MONTH,
    SET_YEAR,
    EXIT_MENU
} F3MenuIndex_t;

typedef enum {
    SET_HOUR,
    SET_MINUTE,
    SET_SECOND,
    EXIT_TIME_MENU
} F4MenuIndex_t;

typedef struct {
    PageId_t page_id;
    void (*page_fn)(void);
    void (*key_fn)(char);
} PageFunction_t;


void handle_key_press(char key);

void home_page_screen(void);
void home_page_key_handler(char key);

void menu_screen(void);
void menu_key_handler(char key);

void f1_page_screen(void);
void f1_page_key_handler(char key);

void f2_page_screen(void);
void f2_page_key_handler(char key);

void set_date_screen(void);
void set_date_key_handler(char key);

void set_month_screen(void);
void set_month_key_handler(char key);

void set_year_screen(void);
void set_year_key_handler(char key);

void exit_menu_screen(void);
void exit_menu_key_handler(char key);

void set_hour_screen(void);
void set_hour_key_handler(char key);

void set_minute_screen(void);
void set_minute_key_handler(char key);

void set_second_screen(void);
void set_second_key_handler(char key);

void exit_time_menu_screen(void);
void exit_time_menu_key_handler(char key);

#endif
