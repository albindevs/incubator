#ifndef __INCUBATOR_H
#define __INCUBATOR_H
#include "real_time_clock.h"

#define CHICK_EGG_INCUBATION_DAYS 21
#define CHICK_EGG_TEMPERATURE 378  //37.8c , DHT SENDS READINGS LIKE 378
#define CHICK_EGG_RELATIVE_HUMIDITY 87
#define CHICK_EGG_RELATIVE_HUMIDITY_LAST_3_DAYS 90

#define TIME_TO_SPINNG_IN_HOURS 6
#define SPINNIG_DURATION_IN_MINUTES 36

typedef struct
{
	char incubation_days;
	char normal_temperature;
	char normal_humidity;
	char normal_humidity_last_3_days;
} IncubationParameters;

IncubationParameters get_incubation_parameters_by_egg_type(char n);

void run_incubator();

#endif