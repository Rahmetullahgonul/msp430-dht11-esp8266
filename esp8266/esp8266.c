#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

//wiFi settings
const char* ssid = "*****";//SSID  your WiFi network
const char* password = "*****";//password your WiFi network


//thingSpeak settings
unsigned long myChannelNumber =1234567;//thingSpeak channel id
const char* myWriteAPIKey ="**********";//thingSpeak channel write API key


WiFiClient client;

void setup(){
  Serial.begin(9600);//start serial communication at 9600 baud rate
  WiFi.begin(ssid,password);

  while (WiFi.status()!=WL_CONNECTED){//wait until esp8266 is connected to WiFi
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");//Print a message wiFi is connected
  ThingSpeak.begin(client);//start thingSpeak with the wiFi client
}



void loop(){
  if(Serial.available()>=5) { // Check 5 bytes of dht11 sensor
    unsigned char RH_byte1=Serial.read();//read the first relative humidity byte
    unsigned char RH_byte2=Serial.read();//read the second relative humidity byte
    unsigned char T_byte1=Serial.read();//read the first temperature byte
    unsigned char T_byte2=Serial.read();//read the second temperature byte
    unsigned char checksum=Serial.read();//read the checksum byte


    unsigned char calculatedChecksum =RH_byte1+RH_byte2+T_byte1+T_byte2;//calculate the checksum

    if (calculatedChecksum==checksum){ //If the calculated checksum matches the other one
      //Calculate temperature and humidity convert to float and send to thingSpeak
      ThingSpeak.setField(1,static_cast<float>(T_byte1)+static_cast<float>(T_byte2)/10.0f);//convert to float and set temperature
      ThingSpeak.setField(2,static_cast<float>(RH_byte1)+static_cast<float>(RH_byte2)/10.0f);//convert tý float and set humidity

      if(ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey)==200){//try sending data to ThingSpeak
        Serial.println("Data send to ThingSpeak successfully.");//success message
      }else{
        Serial.println("Failed to update ThingSpeak.");//fail message
      }
    }else{
        Serial.println("checksum error.");//print error message if checksum does not match
    }
  }
}
