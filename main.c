/*
******************************************************************************
	File:   main.c
	Titulo: 

	Descripcion:

	Notas:


******************************************************************************
*/

#include <xc.h>
#include <delays.h>
#include "conf(8MHzINT2550).h"
#include "lcd.h"
#include "visualization.h"
#include "sensor_temp_humidity_dht.h"
#include "real_time_clock.h"



#define _XTAL_FREQ 8000000
#define Break_point_LED PORTBbits.RB2

char temperature, relative_humidity;
static DateTime datetime;



void blinkLED() {
    Break_point_LED = 1;
    __delay_ms(500);
    Break_point_LED = 0;
    __delay_ms(500);
}

void ports_configuration(){
    OSCCON  = 0b01110010;// intern oscilator 8MHz
    ADCON1  = 0X0F;
    TRISA   = 0;
    TRISB   = 0;
    TRISC   = 0;
    T1CON   = 0x10; // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
    TMR1H   = 0;           
    TMR1L   = 0;
}




void incubator(){
    datetime  = rtc_get_datetime();

    blinkLED();
    if (dht_get_ambient_vars(&temperature, &relative_humidity) && datetime.minutes) {
      display_interface(temperature, relative_humidity, datetime);
    }
    __delay_ms(1000);
}

void main(void) {
    ports_configuration();
    OpenXLCD(FOUR_BIT & LINES_5X7);
    rtc_start();
    __delay_ms(1000);

    while (1) {
        incubator();
    } 
}
