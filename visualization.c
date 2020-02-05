#include <xc.h>
#include "lcd.h"
#include "sensor_temp_humidity_dht.h"
#include "visualization.h"

char Menu_selection_1[] 			= " Incubadora     ";
char Menu_selection_2[]				= " Config fecha   ";

char Incubator_selection_line_1[]	= "> Huevos de     ";
char Incubator_selection_line_2[]  	= "   Gallina      ";

char Incubator_interface_cancel_confirmation_line_1[]	= "  �cancelar?    ";
char Incubator_interface_cancel_confirmation_line_2[]  	= "  OK     Atras  ";


char DateTime_str[]    				= "  /  /     :    ";


char Ambient_variables_status[]		= "T 00.0  HR 00.0%";
char Incubation_days_left[]			= "    dias rest   ";
char Incubation_hours_left[]		= "Term a las   :00";



void display_menu(char selector){
	if (selector == 0)
	{
		Menu_selection_1[0] = '>';
		Menu_selection_2[0] = ' ';
	}
	if (selector == 1)
	{
		Menu_selection_1[0] = ' ';
		Menu_selection_2[0] = '>';
	}
	LCD_out(1,0, Menu_selection_1);
	LCD_out(2,0, Menu_selection_2);

}

void display_incubator_selection(){
	LCD_out(1,0,Incubator_selection_line_1);
    LCD_out(2,0,Incubator_selection_line_2);
}

void display_Ambient_variables_in_first_line(AmbientVariables av){
	format_temp_and_RH(av);
	LCD_out(1,0,Ambient_variables_status);
}

void display_days_left_in_second_line(char days, char hours){
	if(days == 0){
		Incubation_hours_left[11] = (hours / 10) % 10 + '0';
		Incubation_hours_left[12] = (hours % 10) + '0';
		LCD_out(2, 0, Incubation_hours_left);
	}else {
		Incubation_days_left[1] = (days / 10) % 10  + '0';
		Incubation_days_left[2] = (days % 10) + '0';
		LCD_out(2,0,Incubation_days_left);
	}
	
}

void display_incubator_canceling_confirmation(){
	LCD_out(1,0,Incubator_interface_cancel_confirmation_line_1);
    LCD_out(2,0,Incubator_interface_cancel_confirmation_line_2);
}


void display_incubation_ready(){
	LCD_out(1,0,"     PROCESO    ");
	LCD_out(2,0,"    TERMINADO   ");
}



void display_datetime_setting(DateTime datetime, char position){
	char selector_str[]    	= "               ";
	selector_str[position] = '^';
	format_datetime(datetime);
	LCD_out(1,0,DateTime_str);
	LCD_out(2,0,selector_str);
}

void format_temp_and_RH(AmbientVariables av){
	if (av.temperature > 0X8000)
	{                         // if temperature < 0
	  Ambient_variables_status[1] = '-';   // put minus sign '-'
	  av.temperature = av.temperature & 0X7FFF;
	}else {
	  Ambient_variables_status[1] = ' ';  // put space ' '
	  Ambient_variables_status[2]  = (av.temperature / 100) % 10  + '0';
	  Ambient_variables_status[3]  = (av.temperature / 10) % 10   + '0';
	  Ambient_variables_status[5] =  av.temperature % 10  + '0';
	  Ambient_variables_status[6] = 223;    // put degree symbol (°)
	}

	if(av.relative_humidity == 1000) {
	  Ambient_variables_status[10]  = 1 + '0';   // put 1 of hundreds
	}else {
	  Ambient_variables_status[10]  = ' ';       // put space ' '
	  Ambient_variables_status[11]  = (av.relative_humidity / 100) % 10 + '0';
	  Ambient_variables_status[12]  = (av.relative_humidity / 10) % 10  + '0';
	  Ambient_variables_status[14] = av.relative_humidity % 10 + '0';
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


