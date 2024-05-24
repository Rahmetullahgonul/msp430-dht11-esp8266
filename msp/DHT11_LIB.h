#ifndef DHT11_LIB_H_
#define DHT11_LIB_H_

#include <stdint.h> 

typedef struct {
    uint8_t temperature;
    uint8_t humidity;
} DHT11_Data;

#define TST(x,y)    (x & (y))
#define SET(x,y)    (x|= (y))
#define CLR(x,y)    (x &= ~(y))
#define TOG(x,y)    (x ^= (y))

#define DPIN BIT0 

extern unsigned char volatile TOUT;

void start_Signal(void);
unsigned char check_Response(void);
unsigned char read_Byte(void);
unsigned char read_Packet(unsigned char *);        
unsigned char check_Checksum(unsigned char *);    

#endif /* DHT11_LIB_H_ */