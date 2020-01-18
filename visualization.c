#include <xc.h>
#include "lcd.h"
#include "sensor_temp_humidity_dht.h"
#include "visualization.h"



void print_interface(){
	format_temp_and_RH();
	LCD_out(1,1,Temperature);
    LCD_out(2,1,Humidity);
}

void format_temp_and_RH(){
	if (Temp > 0X8000)
	{                         // if temperature < 0
	  Temperature[6] = '-';   // put minus sign '-'
	  Temp = Temp & 0X7FFF;
	}else {
	  Temperature[6] = ' ';  // put space ' '
	  Temperature[7]  = (Temp / 100) % 10  + '0';
	  Temperature[8]  = (Temp / 10) % 10   + '0';
	  Temperature[10] =  Temp % 10  + '0';
	  Temperature[11] = 223;    // put degree symbol (°)
	}

	if(RH == 1000) {
	  Humidity[6]  = 1 + '0';   // put 1 of hundreds
	}else {
	  Humidity[6]  = ' ';       // put space ' '
	  Humidity[7]  = (RH / 100) % 10 + '0';
	  Humidity[8]  = (RH / 10) % 10  + '0';
	  Humidity[10] = RH % 10 + '0';
	}
}

