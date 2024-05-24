#include <msp430.h>
#include "DHT11_LIB.h"//Include the dht11 custom library

//global variables for sensor data
unsigned char RH_byte1,RH_byte2;//variables for humidity bytes
unsigned char T_byte1,T_byte2;//variables for temperature bytes
unsigned char checksum;//variable for checksum
unsigned char Packet[5];//array to store the 5 byte data packet from the dht11

void init(void);


//variable for counting seconds
unsigned char volatile SECOND_TIMER=0;


//Timer0 A0

#pragma vector=TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void{
    SECOND_TIMER++;//second counter
    TOUT=1;
    TOG(P1OUT, 0x01);//toggle P1.0 LED
    CLR(TACCTL0, CCIFG);//clear interrupt flag
}



//function to send UART

void uart_init(void){
    P1SEL|=BIT2+BIT1;//set P1.2 and P1.1 to UART mode
    P1SEL2|=BIT2 + BIT1;//set P1.2 and P1.1 to UART mode
    UCA0CTL1|=UCSSEL_2; // use SMCLK for UART
    UCA0BR0=104;//set baud rate to 9600 (1MHz clock)
    UCA0BR1=0;//set baud rate to 9600 (1MHz clock)
    UCA0MCTL=UCBRS0;
    UCA0CTL1&=~UCSWRST;
}



//function to send a byte with UART
void uart_send_byte(unsigned char byte){
    while(!(UCA0TXIFG&IFG2));//wait until tx buffer is ready
    UCA0TXBUF=byte;//send byte
}




void main(void) {
    init();
    uart_init();//for UART communication

    while(1){
        if(SECOND_TIMER>=5){//check for 5 sec.
            read_Packet(Packet);//read data from the dht11 sensor
            RH_byte1=Packet[0];
            RH_byte2=Packet[1];
            T_byte1=Packet[2];
            T_byte2=Packet[3];
            checksum=Packet[4];


            if (check_Checksum(Packet)) {//Check checksum is correct
                //send values with UART
                uart_send_byte(RH_byte1);
                uart_send_byte(RH_byte2);
                uart_send_byte(T_byte1);
                uart_send_byte(T_byte2);
                uart_send_byte(checksum);

            }


            SET(TACTL,TACLR);//clear the timer
            SET(TA0CTL,0x10);// reset the timer
            TACCR0=50000;//reset the timer 5Hz
            SECOND_TIMER=0;//reset the second counter

        }
    }
}



void init(){
    WDTCTL=WDTPW+WDTHOLD;//Stop the watchdog timer

    P1OUT=0x00;//Set all P1 output low
    P1DIR=0x41;//Set P1.0 output for led

    BCSCTL1=CALBC1_1MHZ;
    DCOCTL=CALDCO_1MHZ;

    TACCR0=50000;
    TACCTL0=CCIE;

    TA0CTL=TASSEL_2+ID_2+MC_1+TACLR;
    _BIS_SR(GIE);

}
