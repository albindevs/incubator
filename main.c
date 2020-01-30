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
#include "buttons.h"
#include "lcd.h"
#include "visualization.h"
#include "sensor_temp_humidity_dht.h"
#include "real_time_clock.h"
#include "time.h"



#define _XTAL_FREQ 8000000

#define Break_point_LED PORTBbits.RB2


DateTime datetime;
AmbientVariables ambient_variables;

char screen_selector = 0;



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
    TRISC   = 0x0E;
    PORTC   = 0;
    T1CON   = 0x10; // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
    TMR1H   = 0;           
    TMR1L   = 0;
}

void data_display(){
    while(1){
        ambient_variables = dht_get_ambient_vars();
        datetime = rtc_get_datetime();
        display_interface(ambient_variables, datetime);

        __delay_ms(1000);
        if (BACK_BUTTON == 1){
            __delay_ms(WAIT_TIME_MS);
            if (BACK_BUTTON == 1){
                break;
            }
        }
        __delay_ms(1000); // dht device needs a 2 seconds wait for new reading
        if (BACK_BUTTON == 1){
            __delay_ms(WAIT_TIME_MS);
            if (BACK_BUTTON == 1){
                break;
            }
        }
    }
}


void program(){
    display_menu(screen_selector);

    if (UP_BUTTON == 1){
        __delay_ms(WAIT_TIME_MS);
        if (UP_BUTTON == 1) screen_selector = 0;
    }

    if (DOWN_BUTTON == 1){
        __delay_ms(WAIT_TIME_MS);
        if (DOWN_BUTTON == 1) screen_selector = 1;
    }

    if (OK_BUTTON == 1){
        __delay_ms(WAIT_TIME_MS);
        if (OK_BUTTON == 1){

            if(screen_selector == 0) data_display();
            if(screen_selector == 1) set_datetime();
        }
    }

}

void main(void) {
    ports_configuration();
    OpenXLCD(FOUR_BIT & LINES_5X7);
    LCD_cursor_off();
    rtc_start();
    __delay_ms(1000);

    while (1) {
        program();
    } 
}
