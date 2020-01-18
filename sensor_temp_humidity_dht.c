#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "sensor_temp_humidity_dht.h"
#include "lcd.h"



AmbientVariables dht_get_ambient_vars() {
  start_Signal();

  AmbientVariables null_values;
  null_values.temperature = NULL;
  null_values.relative_humidity = NULL;
  
  if (!Check_Response()){          
    LCD_clr();
    LCD_out(1,1,"Sin respuesta");
    LCD_out(2,1,"del sensor.");
    return null_values;
  }

  if (Read_Data(&RH_Byte1) || Read_Data(&RH_Byte2) || Read_Data(&T_Byte1) 
    || Read_Data(&T_Byte2) || Read_Data(&CheckSum)){
    LCD_clr();
    LCD_out(1,1,"Tiempo terminado!");
    return null_values;
  }

  char valid_results = check_valid_results();

  if (!valid_results) {                
    LCD_clr();
    LCD_out(1,1,"Error en Checksum!");
    return null_values;
  }

  AmbientVariables ambient_vars = get_converted_results();
  return ambient_vars;
}

void start_Signal(void) {
  DHT22_PIN = 0;         // clear DHT22_PIN output (logic 0)
  DHT22_PIN_LAT = 0;         // clear DHT22_PIN output (logic 0)
  DHT22_PIN_DIR = 0;     // configure DHT22_PIN as output
 
  __delay_ms(25);        // wait 25 ms
  DHT22_PIN_LAT = 1;         // set DHT22_PIN output (logic 1)
  DHT22_PIN = 1;         // set DHT22_PIN output (logic 1)
 
  __delay_us(30);        // wait 30 us
  DHT22_PIN_DIR = 1;     // configure DHT22_PIN as input
  DHT22_PIN = 0;       
  DHT22_PIN_LAT = 0;      
}

__bit Check_Response() {
  TMR1H = 0;                 // reset Timer1
  TMR1L = 0;
  TMR1ON = 1;                // enable Timer1 module
 
  while(!DHT22_PIN && TMR1L < 100);  // wait until DHT22_PIN becomes high (checking of 80µs low time response)
 
  if(TMR1L > 99){
    return 0;
  }else {
    TMR1H = 0;               // reset Timer1
    TMR1L = 0;
 
    while(DHT22_PIN && TMR1L < 100); // wait until DHT22_PIN becomes low (checking of 80µs high time response)
 
    if(TMR1L > 99){
      return 0; 
    }else{
      return 1;                      // return 1 (response OK)
    }
  }
}

__bit Read_Data(unsigned char* dht_data) {
  *dht_data = 0;
 
  for(char i = 0; i < 8; i++)
  {
    TMR1H = 0;             // reset Timer1
    TMR1L = 0;
 
    while(!DHT22_PIN);     // wait until DHT22_PIN becomes high

    if(TMR1L > 100) {    
      return 1;
    }
 
    TMR1H = 0;             // reset Timer1
    TMR1L = 0;
 
    while(DHT22_PIN);     
    
    if(TMR1L > 100) {    // if high time > 100  ==>  Time out error (Normally it takes 26-28µs for 0 and 70µs for 1)
      return 1;          // return 1 (timeout error)
    }
 
    if(TMR1L > 50){
       *dht_data |= (1 << (7 - i));  // set bit (7 - i)
    }                  
  }
 
  return 0;                          // return 0 (data read OK)
}

__bit check_valid_results(){
  if (CheckSum != ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)) {
    return 0;
  }

  return 1;
}

AmbientVariables get_converted_results(){
  AmbientVariables ambient_vars;
  RH = RH_Byte1;
  RH = (RH << 8) | RH_Byte2;
  Temp = T_Byte1;
  Temp = (Temp << 8) | T_Byte2;

  ambient_vars.temperature = Temp;
  ambient_vars.relative_humidity = RH;
  return ambient_vars;
}
