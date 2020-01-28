#include <xc.h>
#include "lcd.h"
#include "sensor_temp_humidity_dht.h"
#include "visualization.h"


char Temperature_str[]      = "Temp = 00.0 C  ";
char Humidity_str[]         = "RH   = 00.0 %  ";
char DateTime_str[]    	= "  /  /     :   ";

void display_interface(char temperature, char relative_humidity, DateTime datetime){
	format_temp_and_RH(temperature, relative_humidity);
	format_datetime(datetime);
	LCD_out(1,1,Temperature_str);
    LCD_out(2,1,DateTime_str);
}

void format_temp_and_RH(char temperature, char relative_humidity){
	if (temperature > 0X8000)
	{                         // if temperature < 0
	  Temperature_str[6] = '-';   // put minus sign '-'
	  temperature = temperature & 0X7FFF;
	}else {
	  Temperature_str[6] = ' ';  // put space ' '
	  Temperature_str[7]  = (temperature / 100) % 10  + '0';
	  Temperature_str[8]  = (temperature / 10) % 10   + '0';
	  Temperature_str[10] =  temperature % 10  + '0';
	  Temperature_str[11] = 223;    // put degree symbol (°)
	}

	if(relative_humidity == 1000) {
	  Humidity_str[6]  = 1 + '0';   // put 1 of hundreds
	}else {
	  Humidity_str[6]  = ' ';       // put space ' '
	  Humidity_str[7]  = (relative_humidity / 100) % 10 + '0';
	  Humidity_str[8]  = (relative_humidity / 10) % 10  + '0';
	  Humidity_str[10] = relative_humidity % 10 + '0';
	}
}

void format_datetime(DateTime datetime){
	//day
	DateTime_str[0] = (datetime.date / 10) % 10  + '0';
	DateTime_str[1] = (datetime.date % 10) + '0';

	//month
	DateTime_str[3] = (datetime.month / 10) % 10  + '0';
	DateTime_str[4] = (datetime.month % 10) + '0';

	//year
	DateTime_str[6] = (datetime.year / 10) % 10  + '0';
	DateTime_str[7] = (datetime.year % 10) + '0';

	//hours
	DateTime_str[9] = (datetime.hours / 10) % 10  + '0';
	DateTime_str[10] = (datetime.hours % 10) + '0';

	//minutes
	DateTime_str[12] = (datetime.minutes / 10) % 10  + '0';
	DateTime_str[13] = (datetime.minutes % 10) + '0';
}

