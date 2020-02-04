#ifndef __TIME_H
#define __TIME_H


#include "real_time_clock.h"

char normal_year_days_by_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char leap_year_days_by_month[] = {31,29,31,30,31,30,31,31,30,31,30,31};

char leap_years_until_2050[] = {20,24,28,32,36,40,44,48,52};

void interface_set_datetime();

DateTime calculate_date_when_n_days_passed(DateTime current_datetime, char days);


#endif