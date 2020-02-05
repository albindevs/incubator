#ifndef __VISUALIZATION_H
#define __VISUALIZATION_H

#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif

#include "lcd.h"
#include "sensor_temp_humidity_dht.h"
#include "real_time_clock.h"


void display_menu(char selector);

void display_interface(AmbientVariables av, DateTime datetime);

void display_incubator_selection();

void display_Ambient_variables_in_first_line(AmbientVariables av);
void display_days_left_in_second_line(char days, char hours);

void display_incubator_canceling_confirmation();
void display_incubation_ready();

void display_datetime_setting(DateTime datetime, char position);


void format_temp_and_RH(AmbientVariables av);
void format_datetime(DateTime datetime);

#endif
