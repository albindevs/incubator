#include <xc.h>
#include "buttons.h"
#include "visualization.h"
#include "real_time_clock.h"

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