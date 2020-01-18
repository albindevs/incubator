#ifndef __SENSOR_TEMP_HUMIDITY_DHT_H
#define __SENSOR_TEMP_HUMIDITY_DHT_H

#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif

#define DHT22_PIN      PORTCbits.RC0	
#define DHT22_PIN_LAT  LATCbits.LATC0
#define DHT22_PIN_DIR  TRISCbits.RC0

unsigned char T_Byte1, T_Byte2, RH_Byte1, RH_Byte2, CheckSum ;
unsigned int Temp, RH;

typedef struct {
	int temperature;
	int relative_humidity; 
} AmbientVariables;


AmbientVariables dht_get_ambient_vars();


void start_Signal(void);

__bit Check_Response();

__bit Read_Data(unsigned char* dht_data);

__bit check_valid_results();

AmbientVariables get_converted_results();


#endif
