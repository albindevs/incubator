#ifndef dht
#define dht

#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif

#define DHT22_PIN      PORTCbits.RC0	
#define DHT22_PIN_LAT  LATCbits.LATC0
#define DHT22_PIN_DIR  TRISCbits.RC0

unsigned char T_Byte1, T_Byte2, RH_Byte1, RH_Byte2, CheckSum ;
unsigned int Temp, RH;

void dht_start_Signal(void);

__bit dht_get_Results();

__bit Check_Response();

__bit Read_Data(unsigned char* dht_data);

__bit check_valid_results();

void format_results();


#endif
