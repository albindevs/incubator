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
#include <plib/timers.h>
#include "conf(8MHzINT2550).h"
#include "buttons.h"
#include "lcd.h"
#include "visualization.h"
#include "incubator.h"
#include "time.h"

#define _XTAL_FREQ 8000000
#define Break_point_LED PORTBbits.RB2

unsigned char screen_selector = 0;

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
    TRISC   = 0b01110011;
    PORTC   = 0;
    T1CON   = 0x10; // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
    TMR1H   = 0;           
    TMR1L   = 0;
}

void PWM1_Init()
{
    CCP1CON = 0b00001100;   // Enable PWM on CCP1
    T2CON = 0b00000111;     // Enable TMR2 with prescaler = 1
    PR2 = 0b01111100;       // PWM period = (PR2+1) * prescaler * Tcy = 1ms
    CCPR1L = 25; // pulse width = CCPR1L * prescaler * Tcy = 100us     /* Timer ON for start counting*/
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

            if(screen_selector == 0) incubation_program();
            if(screen_selector == 1) interface_set_datetime();
        }
    }

}

void main(void) {
    ports_configuration();
    OpenXLCD(FOUR_BIT & LINES_5X7);
    LCD_cursor_off();
    rtc_start();
    PWM1_Init();
    __delay_ms(1000);

    while (1) {
        program();
    } 
}
