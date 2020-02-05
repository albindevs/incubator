#ifndef __INCUBATOR_H
#define __INCUBATOR_H
#include "real_time_clock.h"


// EEPROM
#define ADDRESS_INCUBATION_PROCESS_STATUS 	0x1E
#define ADDRESS_EGG_TYPE				 	0x1F

#define ADDRESS_INCUBATION_DAYS 			0x20


#define ADDRESS_TIME_TO_SPIN 				0x21
#define ADDRESS_SPINNING_DURATION			0x22

#define ADDRESS_DATE_TO_FINISH				0x23
#define ADDRESS_MONTH_TO_FINISH				0x24
#define ADDRESS_YEAR_TO_FINISH				0x25
#define ADDRESS_HOUR_TO_FINISH				0x26



// EGGS TYPE
#define CHICKEN_EGG 1

// PARAMETERS BY TYPE
#define CHICK_EGG_INCUBATION_DAYS 21
#define CHICK_EGG_TEMPERATURE 378  //37.8c , DHT SENDS READINGS LIKE 378
#define CHICK_EGG_RELATIVE_HUMIDITY 870
#define CHICK_EGG_RELATIVE_HUMIDITY_LAST_3_DAYS 900

#define TIME_TO_SPIN_IN_HOURS 6
#define SPINNIG_DURATION_IN_MINUTES 36

typedef struct
{
	char incubation_days;
	int normal_temperature;
	int normal_humidity;
	int normal_humidity_last_3_days;
} IncubationParameters;

IncubationParameters get_incubation_parameters_by_egg_type(char n);

void incubation_program();

void run_incubator();

#endif