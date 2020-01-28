#ifndef __VISUALIZATION_H
#define __VISUALIZATION_H

#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif

#include "sensor_temp_humidity_dht.h"
#include "real_time_clock.h"


void format_temp_and_RH(char temperature, char relative_humidity);
void format_datetime(DateTime datetime);

void display_interface(char temperature, char relative_humidity, DateTime datetime);

#endif
