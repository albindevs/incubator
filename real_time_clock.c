#include <xc.h>
#include <plib\i2c.h>
#include "real_time_clock.h"

void rtc_start(){
	OpenI2C(MASTER, SLEW_OFF);
	SSPADD = SSPADD_VALUE;
}

