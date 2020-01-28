#ifndef __REAL_TIME_CLOCK_H
#define __REAL_TIME_CLOCK_H

#define SSPADD_VALUE 19

#define SECONDS_ADDRESS 0x00
#define MINUTES_ADDRESS 0x01
#define HOURS_ADDRESS 	0x02
#define DAY_ADDRESS 	0x03
#define DATE_ADDRESS 	0x04
#define MONTH_ADDRESS 	0x05
#define YEAR_ADDRESS 	0x06

typedef struct
{
	char minutes;
	char hours;
	char day;
	char date;
	char month;
	char year;
} DateTime;


void rtc_start();


DateTime rtc_get_datetime();

char rtc_get_minutes();
char rtc_get_hours();
char rtc_get_day();
char rtc_get_date();
char rtc_get_month();
char rtc_get_year();

char convert_bdc_to_bin(char data_byte);

char rtc_read(char address);


void rtc_set_minutes(char minutes);
void rtc_set_hours(char hours);
void rtc_set_day(char day);
void rtc_set_date(char date);
void rtc_set_month(char month);
void rtc_set_year(char year);

char convert_byte_to_bcd(char data_byte);

void rtc_write(char address, char data_byte);





#endif