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
#include "visualization.h"
#include "sensor_temp_humidity_dht.h"
#include "real_time_clock.h"



#define _XTAL_FREQ 8000000
#define Break_point_LED PORTBbits.RB2


void blinkLED() {
  Break_point_LED = 1;
  __delay_ms(500);
  Break_point_LED = 0;
  __delay_ms(500);
}

void ports_configuration(){
    OSCCON  = 0b01110010;//oscilador interno a 8MHz
    ADCON1  = 0X0F;
    TRISA   = 0;
    TRISB   = 0;
    TRISC   = 0;
    T1CON  = 0x10; // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
    TMR1H  = 0;           // reset Timer1
    TMR1L  = 0;
}

void main(void) {
  ports_configuration();
  OpenXLCD(FOUR_BIT & LINES_5X7);
  rtc_start();
  __delay_ms(1000);
  
  while (1) {
    blinkLED();

    AmbientVariables ambient_vars = dht_get_ambient_vars();

    if (ambient_vars.temperature) {
      print_interface(ambient_vars);
    }
    
    TMR1ON = 0;
    __delay_ms(1000);
  } 
}
