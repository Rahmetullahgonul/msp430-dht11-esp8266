#include <msp430.h>
#include <DHT11_LIB.h>
unsigned char volatile TOUT;

// Function to read a byte from the DHT11 sensor
unsigned char read_Byte(){
	TOUT = 0;  // Timeout flag clear
	unsigned char num = 0;  // Initialize the byte to be returned
	unsigned char i;
	CLR(TACCTL0, CCIE);  // Disable timer capture/compare interrupt
	for (i=8; i>0; i--){
		while(!(TST(P2IN,DPIN))); // Wait until signal goes high
		SET(TACTL,TACLR);  // Clear the timer
		SET(TA0CTL, 0x10);  // Re-enable the timer
		SET(TACCTL0, CCIE);  // Enable timer interrupt
		while(TST(P2IN,DPIN)); // Wait until signal goes low
		CLR(TA0CTL, 0x30);  // Stop the timer
		if (TAR > 13)  // If time above threshold, consider it a '1'
			num |= 1 << (i-1);
	}
	return num;  // Return the assembled byte
}

// Function to read the entire packet from the DHT11 sensor
unsigned char read_Packet(unsigned char *data){
	start_Signal();  // Initiate the start signal to DHT11
	if (check_Response()){  // Check if DHT11 responds
		data[0] = read_Byte();  // Read first byte
		data[1] = read_Byte();  // Read second byte
		data[2] = read_Byte();  // Read third byte
		data[3] = read_Byte();  // Read fourth byte
		data[4] = read_Byte();  // Read fifth byte
		return 1;  // Return 1 on successful read
	}
	else return 0;  // Return 0 on failure
}

// Function to check if the DHT11 has responded correctly
unsigned char check_Response(){
	TOUT=0;  // Clear timeout flag
	SET(TACTL, TACLR);  // Reset timer
	TACCR0 = 25;  // Set timer to overflow at 100 microseconds
	SET(TACCTL0, CCIE);  // Enable timer interrupt
	while(!(TST(P2IN, DPIN)) && !TOUT);  // Wait for signal to go high or timeout
	if (TOUT)
		return 0;  // Return 0 if timed out (no response)
	else {
		SET(TACTL, TACLR);  // Clear the timer
		SET(TACCTL0, CCIE);  // Re-enable interrupt
		while((TST(P2IN, DPIN)) && !TOUT);  // Wait for signal to go low or timeout
		if(TOUT)
			return 0;  // Return 0 if timed out
		else{
			CLR(TACCTL0, CCIE);  // Disable timer interrupt
			return 1;  // Return 1 if response is valid
		}
	}
}

// Function to initiate the start signal to the DHT11
void start_Signal(){
	SET(P2DIR, DPIN);  // Set data pin as output
	CLR(P2OUT,DPIN);  // Set data pin low
	__delay_cycles(25000);  // Maintain low for at least 18ms
	SET(P2OUT,DPIN);  // Set data pin high
	__delay_cycles(30);  // Maintain high for 20-40us
	CLR(P2DIR,DPIN);  // Set data pin as input
}

// Function to verify the checksum of received data
unsigned char check_Checksum(unsigned char *data){
	if (data[4] != (data[0] + data[1] + data[2] + data[3])){  // Calculate and compare checksum
		return 0;  // Return 0 if checksum does not match
	}
	else return 1;  // Return 1 if checksum matches
}
