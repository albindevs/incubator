#ifndef __BUTTONS_H
#define __BUTTONS_H

#include <xc.h>
#include <delays.h>

#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif

#define OK_BUTTON       PORTCbits.RC1
#define OK_BUTTON_DIR   TRISCbits.RC1
#define BACK_BUTTON     PORTCbits.RC2
#define BACK_BUTTON_DIR TRISCbits.RC2
#define UP_BUTTON       PORTCbits.RC4
#define UP_BUTTON_DIR   TRISCbits.RC4
#define DOWN_BUTTON     PORTCbits.RC5
#define DOWN_BUTTON_DIR TRISCbits.RC5

#define WAIT_TIME_MS 150

#endif
