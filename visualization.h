#ifndef __VISUALIZATION_H
#define __VISUALIZATION_H

#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif

// #include <xc.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include "xlcd.h"
// #include "dht.h"

char Temperature[] = "Temp = 00.0 C  ";
char Humidity[]    = "RH   = 00.0 %  ";

void format_temp_and_RH();

void print_interface();


#endif
