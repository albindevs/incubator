#include "buttons.h"

__bit check_ok_button(){
	if (OK_BUTTON == 1){
		__delay_ms(WAIT_TIME_MS);
		if (OK_BUTTON == 1){
			return 1;
		}
		return 0;
	}
}

__bit check_back_button(){
	if (BACK_BUTTON == 1){
		__delay_ms(WAIT_TIME_MS);
		if (BACK_BUTTON == 1){
			return 1;
		}
		return 0;
	}
}

__bit check_up_button(){
	if (UP_BUTTON == 1){
		__delay_ms(WAIT_TIME_MS);
		if (UP_BUTTON == 1){
			return 1;
		}
		return 0;
	}
}

__bit check_down_button(){
	if (DOWN_BUTTON == 1){
		__delay_ms(WAIT_TIME_MS);
		if (DOWN_BUTTON == 1){
			return 1;
		}
		return 0;
	}
}