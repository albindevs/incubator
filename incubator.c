#include <xc.h>
#include "buttons.h"
#include "visualization.h"
#include "real_time_clock.h"
#include "incubator.h"

char selector;

void run_incubator(){
	selector = 0;

	display_incubator_interface();

	while(1){
		if (UP_BUTTON == 1){
	        __delay_ms(WAIT_TIME_MS);
	        if (UP_BUTTON == 1) selector = 0;
	    }

	    if (DOWN_BUTTON == 1){
	        __delay_ms(WAIT_TIME_MS);
	        if (DOWN_BUTTON == 1) selector = 1;
	    }

	    if (OK_BUTTON == 1){
	        __delay_ms(WAIT_TIME_MS);
	        if (OK_BUTTON == 1){

	            if(selector == 0) break;
	            if(selector == 1) break;
	        }
	    }
	}
}

IncubationParameters get_incubation_parameters_by_egg_type(char n){
	IncubationParameters ip;

	if (n == 1)
	{
		ip.incubation_days = CHICK_EGG_INCUBATION_DAYS;
		ip.normal_temperature = CHICK_EGG_TEMPERATURE;
		ip.normal_humidity = CHICK_EGG_RELATIVE_HUMIDITY;
		ip.normal_humidity_last_3_days = CHICK_EGG_RELATIVE_HUMIDITY_LAST_3_DAYS;
	}

	return ip;
}