#include <xc.h>
#include <delays.h>
#include <plib/timers.h>
#include "buttons.h"
#include "lcd.h"

#define _XTAL_FREQ 8000000

unsigned char pwm_value = 50;

// void PWM1_setDC(unsigned int dutycycle)
// {
//     CCPR1L = dutycycle >> 2;              //  PWM duty cycle - first 8-bits (MSb)
//     CCP1CON &= 0xCF;                      //  5,4 bits zeroed (DC1B1:DC1B0 = 00)
//     CCP1CON |= ((dutycycle << 4) & 0x30); //  PWM duty cycle - last 2-bits (LSb) in CCP1CON 5,4 bits
// }

void regulate_temperature(int temperature , int normal_temperature){

    if (temperature > normal_temperature && pwm_value > 10)
    {
        pwm_value--;
        CCPR1L = pwm_value;
    }

    if (temperature < normal_temperature && pwm_value < 110)
    {
        pwm_value++;
        CCPR1L = pwm_value;
    }

    if(temperature > 450 || temperature < 320){
        BUZZER = 1;
        LCD_clr();
        LCD_out(1,0," RANGO DE TEMP  ");
        LCD_out(2,0,"    EXCEDIDO    ");
        __delay_ms(100);
    }else {
        BUZZER = 0;
    }
    
    
}
