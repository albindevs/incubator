#include <xc.h>
#include "lcd.h"
#include "sensor_temp_humidity_dht.h"
#include "visualization.h"



void print_interface(AmbientVariables ambient_vars){
	format_temp_and_RH(ambient_vars);
	LCD_out(1,1,Temperature);
    LCD_out(2,1,Humidity);
}

void format_temp_and_RH(AmbientVariables ambient_vars){
	if (ambient_vars.temperature > 0X8000)
	{                         // if temperature < 0
	  Temperature[6] = '-';   // put minus sign '-'
	  ambient_vars.temperature = ambient_vars.temperature & 0X7FFF;
	}else {
	  Temperature[6] = ' ';  // put space ' '
	  Temperature[7]  = (ambient_vars.temperature / 100) % 10  + '0';
	  Temperature[8]  = (ambient_vars.temperature / 10) % 10   + '0';
	  Temperature[10] =  ambient_vars.temperature % 10  + '0';
	  Temperature[11] = 223;    // put degree symbol (°)
	}

	if(ambient_vars.relative_humidity == 1000) {
	  Humidity[6]  = 1 + '0';   // put 1 of hundreds
	}else {
	  Humidity[6]  = ' ';       // put space ' '
	  Humidity[7]  = (ambient_vars.relative_humidity / 100) % 10 + '0';
	  Humidity[8]  = (ambient_vars.relative_humidity / 10) % 10  + '0';
	  Humidity[10] = ambient_vars.relative_humidity % 10 + '0';
	}
}

