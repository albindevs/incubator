#include <xc.h>
#include "buttons.h"
#include "visualization.h"
#include "real_time_clock.h"
#include "time.h"
#include "incubator.h"

char selector;
char incubation_process_status = 0;
DateTime current_date, final_date;
IncubationParameters incubation_parameters;

char egg_type;
char incubation_days;
int normal_temperature;
int normal_humidity;
int normal_humidity_last_3_days;
char time_to_spin_in_hours;
char spinnig_duration_in_minutes;

void incubation_program(){
	incubation_process_status = Read_b_eep(ADDRESS_INCUBATION_PROCESS_STATUS);
    Busy_eep();

    if (incubation_process_status == 1){
    	run_incubator();
    }else{
		display_incubator_selection();

		while(1){
			if (UP_BUTTON == 1){
		        __delay_ms(WAIT_TIME_MS);
		        if (UP_BUTTON == 1);
		    }
		    if (DOWN_BUTTON == 1){
		        __delay_ms(WAIT_TIME_MS);
		        if (DOWN_BUTTON == 1);
		    }
		    if (OK_BUTTON == 1){
		        __delay_ms(WAIT_TIME_MS);
		        if (OK_BUTTON == 1){
		        	incubation_parameters = get_incubation_parameters_by_egg_type(CHICKEN_EGG);
		        	Write_b_eep(ADDRESS_EGG_TYPE, CHICKEN_EGG);
    				Busy_eep();

		        	Write_b_eep(ADDRESS_INCUBATION_DAYS, incubation_parameters.incubation_days);
    				Busy_eep();
		        	Write_b_eep(ADDRESS_TIME_TO_SPIN, TIME_TO_SPIN_IN_HOURS);
    				Busy_eep();
		        	Write_b_eep(ADDRESS_SPINNING_DURATION, SPINNIG_DURATION_IN_MINUTES);
    				Busy_eep();

    				current_date = rtc_get_datetime();
    				final_date = calculate_date_when_n_days_passed(current_date, incubation_parameters.incubation_days);
    				Write_b_eep(ADDRESS_DATE_TO_FINISH, final_date.date);
    				Busy_eep();
    				Write_b_eep(ADDRESS_MONTH_TO_FINISH, final_date.month);
    				Busy_eep();
    				Write_b_eep(ADDRESS_YEAR_TO_FINISH, final_date.year);
    				Busy_eep();
    				Write_b_eep(ADDRESS_HOUR_TO_FINISH, final_date.hours);
    				Busy_eep();

					run_incubator();
					break;
		        }
		    }

		    if (BACK_BUTTON == 1){
		        __delay_ms(WAIT_TIME_MS);
		        if (BACK_BUTTON == 1){
		        	break;
		        }
		    }
		}
    }
}

void run_incubator(){
	Write_b_eep(ADDRESS_INCUBATION_PROCESS_STATUS, 1);
    Busy_eep();
    incubation_process_status = Read_b_eep(ADDRESS_INCUBATION_PROCESS_STATUS);
    Busy_eep();

    egg_type = Read_b_eep(ADDRESS_EGG_TYPE);
    Busy_eep();
    incubation_parameters = get_incubation_parameters_by_egg_type(egg_type);
    normal_temperature = incubation_parameters.normal_temperature;
    normal_humidity = incubation_parameters.normal_humidity;
    normal_humidity_last_3_days = incubation_parameters.normal_humidity_last_3_days;

    incubation_days = Read_b_eep(ADDRESS_INCUBATION_DAYS);
    Busy_eep();
    time_to_spin_in_hours = Read_b_eep(ADDRESS_TIME_TO_SPIN);
    Busy_eep();
    spinnig_duration_in_minutes = Read_b_eep(ADDRESS_SPINNING_DURATION);
    Busy_eep();

    final_date.date = Read_b_eep(ADDRESS_DATE_TO_FINISH);
	Busy_eep();
	final_date.month = Read_b_eep(ADDRESS_MONTH_TO_FINISH);
	Busy_eep();
	final_date.year = Read_b_eep(ADDRESS_YEAR_TO_FINISH);
	Busy_eep();
	final_date.hours = Read_b_eep(ADDRESS_HOUR_TO_FINISH);
	Busy_eep();



    while(incubation_process_status){
    	display_incubator_interface(incubation_days);

	    if (BACK_BUTTON == 1){
	        __delay_ms(WAIT_TIME_MS);
	        if (BACK_BUTTON == 1){
	        	display_incubator_canceling_confirmation();
	        	while(1){
				    if (OK_BUTTON == 1){
				        __delay_ms(WAIT_TIME_MS);
				        if (OK_BUTTON == 1){
				        	Write_b_eep(ADDRESS_INCUBATION_PROCESS_STATUS, 0);
    						Busy_eep();
    						incubation_process_status = Read_b_eep(ADDRESS_INCUBATION_PROCESS_STATUS);
    						Busy_eep();
							break;
				        }
				    }

				    if (BACK_BUTTON == 1){
				        __delay_ms(WAIT_TIME_MS);
				        if (BACK_BUTTON == 1){
				        	break;
				        }
				    }
				}
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