#include <xc.h>
#include "buttons.h"
#include "lcd.h"
#include "visualization.h"
#include "real_time_clock.h"

void set_datetime(){
	char position = 1;
	DateTime datetime;
	datetime  = rtc_get_datetime();
	
	while(1){
		if (UP_BUTTON == 1){
            __delay_ms(WAIT_TIME_MS);
            if (UP_BUTTON == 1){

            	if (position == 1){
            		if(datetime.date < 31){
            			datetime.date++;
            		}else{
            			datetime.date = 1;
            		}
            	}

            	if (position == 4){
            		if(datetime.month < 12){
            			datetime.month++;
            		}else{
            			datetime.month = 1;
            		}
            	}

            	if (position == 7){
            		if(datetime.year < 99){
            			datetime.year++;
            		}else{
            			datetime.year = 0;
            		}
            	}

            	if (position == 10){
            		if(datetime.hours < 23){
            			datetime.hours++;
            		}else{
            			datetime.hours = 0;
            		}
            	}

            	if (position == 13){
            		if(datetime.minutes < 59){
            			datetime.minutes++;
            		}else{
            			datetime.minutes = 0;
            		}
            	}
                __delay_ms(WAIT_TIME_MS);
            }
        }

        if (DOWN_BUTTON == 1){
            __delay_ms(WAIT_TIME_MS);
            if (DOWN_BUTTON == 1){

                if (position == 1){
            		if(datetime.date > 1){
            			datetime.date--;
            		}else{
            			datetime.date = 31;
            		}
            	}

            	if (position == 4){
            		if(datetime.month > 1){
            			datetime.month--;
            		}else{
            			datetime.month = 12;
            		}
            	}

            	if (position == 7){
            		if(datetime.year > 0){
            			datetime.year--;
            		}else{
            			datetime.year = 99;
            		}
            	}

            	if (position == 10){
            		if(datetime.hours > 0){
            			datetime.hours--;
            		}else{
            			datetime.hours = 23;
            		}
            	}

            	if (position == 13){
            		if(datetime.minutes > 0){
            			datetime.minutes--;
            		}else{
            			datetime.minutes = 59;
            		}
            	}
                __delay_ms(WAIT_TIME_MS);
            }
        }

        if (OK_BUTTON == 1){
            __delay_ms(WAIT_TIME_MS);
            if (OK_BUTTON == 1){

            	rtc_set_datetime(datetime);
            	position = position + 3;
            	if (position > 15) break;
            }
        }

        if (BACK_BUTTON == 1){
            __delay_ms(WAIT_TIME_MS);
            if (BACK_BUTTON == 1){
                break;
            }
        }

        display_datetime_setting(datetime, position);
	}	
}