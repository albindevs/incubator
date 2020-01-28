#include <xc.h>
#include <plib\i2c.h>
#include "real_time_clock.h"

void rtc_start(){
	OpenI2C(MASTER, SLEW_OFF);
	SSPADD = SSPADD_VALUE;
}


DateTime rtc_get_datetime(){
	DateTime datetime;

	datetime.minutes = rtc_get_minutes();
	datetime.hours = rtc_get_hours();
	datetime.day = rtc_get_day();
	datetime.date = rtc_get_date();
	datetime.month = rtc_get_month();
	datetime.year = rtc_get_year();

	return datetime;
}

char rtc_get_minutes(){
	char minutes_byte = rtc_read(MINUTES_ADDRESS);
	char minutes = convert_bdc_to_bin(minutes_byte);
	return minutes;
}

char rtc_get_hours(){
	char hours_byte = rtc_read(HOURS_ADDRESS);
	char hours = convert_bdc_to_bin(hours_byte);
	return hours;
}

char rtc_get_day(){
	char day_byte = rtc_read(DAY_ADDRESS);
	char day = convert_bdc_to_bin(day_byte);
	return day;
}

char rtc_get_date(){
	char date_byte = rtc_read(DATE_ADDRESS);
	char date = convert_bdc_to_bin(date_byte);
	return date;
}

char rtc_get_month(){
	char month_byte = rtc_read(MONTH_ADDRESS);
	char month = convert_bdc_to_bin(month_byte);
	return month;
}

char rtc_get_year(){
	char year_byte = rtc_read(YEAR_ADDRESS);
	char year = convert_bdc_to_bin(year_byte);
	return year;
}

char convert_bdc_to_bin(char data_byte){
	char upper = data_byte >> 4;
	char lower = data_byte & 0b00001111;
	return upper*10 + lower;
}

char rtc_read(char address){
	char resultI2C;
	StartI2C();
	IdleI2C();
	WriteI2C(0xD0);
	IdleI2C();
	WriteI2C(address);
	IdleI2C();
	StopI2C();

	StartI2C();
	IdleI2C();
	WriteI2C(0xD1);
	IdleI2C();
	resultI2C = ReadI2C();
	IdleI2C();
	NotAckI2C();
	IdleI2C();
	StopI2C();
	return resultI2C;
}


void rtc_set_minutes(char minutes){
	char bcd_minutes = convert_byte_to_bcd(minutes);
	rtc_write(MINUTES_ADDRESS, bcd_minutes);
}

void rtc_set_hours(char hours){
	char bcd_hours = convert_byte_to_bcd(hours);
	rtc_write(HOURS_ADDRESS, bcd_hours);
}

void rtc_set_day(char day){
	rtc_write(DAY_ADDRESS, day);
}

void rtc_set_date(char date){
	char bcd_date = convert_byte_to_bcd(date);
	rtc_write(DATE_ADDRESS, bcd_date);
}

void rtc_set_month(char month){
	char bcd_month = convert_byte_to_bcd(month);
	rtc_write(MONTH_ADDRESS, bcd_month);
}

void rtc_set_year(char year){
	char bcd_year = convert_byte_to_bcd(year);
	rtc_write(YEAR_ADDRESS, bcd_year);
}

char convert_byte_to_bcd(char data_byte){
	char a = data_byte%10;            
	char b = (data_byte/10)%10;
	b << 4; 
	return b|a;       
}

void rtc_write(char address, char data_byte){
	StartI2C();
	IdleI2C();
	WriteI2C(0xD0);
	IdleI2C();
	WriteI2C(address);
	IdleI2C();
	WriteI2C(data_byte);
	IdleI2C();
	StopI2C();
}