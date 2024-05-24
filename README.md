<p align="center">
  <strong>DETAILS OF THE PROJECT</strong>
</p>


# Microcontroller Project

The goals of this project are to use it for an IoT system by reading data from a DHT11 temperature and humidity sensor in any environment with an MSP430, then transmitting the data to an ESP8266 WiFi module via UART, and from there to a cloud service provided by ThingSpeak. This project focuses on temperature and humidity control.

It can be connected to any project requiring temperature and humidity control, enabling actions based on the temperature and humidity values. For example, in smart home systems, it can automatically adjust the operation of an air conditioner or air purifier, trigger a cooling system for an electronic component at high temperatures, or provide data to maintain the required temperature values in a refrigerator. These are just a few of the many potential applications.




For my microcontrollers lesson, I have prepared this project using the following components:

1) **MSP430G2553**
<p align="center">

   <img src="https://github.com/Rahmetullahgonul/msp430-dht11-esp8266/assets/137273597/3023f64d-fa26-450a-82be-392d9ce36276" width="300">
   
2) **DHT11 Sensor**

<p align="center">
<p align="center">
   <img src="https://github.com/Rahmetullahgonul/msp430-dht11-esp8266/assets/137273597/a31463ca-8c74-4fd1-b135-5498a4d263c4" width="300">
   
3) **ESP8266 WiFi Module**

<p align="center">
   <img src="https://github.com/Rahmetullahgonul/msp430-dht11-esp8266/assets/137273597/801eb8a1-1978-4b2b-84d7-1dcfd5778a23" width="300">
   
4) **9V Battery**

5) **Two Resistors (10k, 47k)**

6) **Two Capacitors (10uF and 0.1mF)**

7) **LM1117 3.3V Voltage Regulator**


**NOTE:** I used the MSP430G2553 MCU in this project. Here are the pinouts:

  <p align="center"><img src="https://github.com/Rahmetullahgonul/msp430-dht11-esp8266/assets/137273597/eefe703a-099e-4070-bae2-e1e7291f7bc5" width="500"> ,<p align="center"><img src="https://github.com/Rahmetullahgonul/msp430-dht11-esp8266/assets/137273597/59c0a7da-976a-4a7e-91aa-45fb5b7b45ba" width="300">


## Schematic of Circuit

<p align="center">
  <img src="https://github.com/Rahmetullahgonul/msp430-dht11-esp8266/assets/137273597/7caa8a98-3785-45c6-add9-91ef95e10dc6" alt="Schematic of Circuit">
</p>


## Conclusion

This project successfully reads data from the DHT11 temperature and humidity sensor using the MSP430G2553 microcontroller and sends it to the ThingSpeak platform via the ESP8266 WiFi module. This data transmission forms a foundation for various IoT applications requiring temperature and humidity control. The project offers practical solutions for smart home systems, automatic control systems, and various industrial applications.

<p align="center">
  <img src="https://github.com/Rahmetullahgonul/msp430-dht11-esp8266/assets/137273597/81dac750-9003-4e0e-9b36-c2ea4aa398b8" alt="ThingSpeak Data">
</p>

## References

1. **MSP430G2553** - [Texas Instruments](https://www.ti.com/product/MSP430G2553)
2. **DHT11 Sensor** - [Adafruit](https://www.adafruit.com/product/386)
3. **ESP8266 WiFi Module** - [Espressif Systems](https://www.espressif.com/en/products/socs/esp8266)
4. **ThingSpeak** - [ThingSpeak](https://thingspeak.com/)
5. **LM1117 3.3V Voltage Regulator** - [ON Semiconductor](https://www.onsemi.com/products/power-management/linear-regulators-ldo/lm1117)

