# PID-HeaterControl
Automatic Temperature control using PID concepts                                                                                                                       
## Objectve   
- Construct a closed loop feedback control system for temperature control system.
- The effect of the PID controller parameters on the system performance.
- The effect of the PID controller parameters on the system performance.
So, In version one (V1) this library serves this project in the first place.    
## Block Diagram
  ![N|Solid](https://i.ibb.co/dDmVkLh/Capture.png) 

  
## Description   
- project setup consists of a wooden box that resembles the furnace,the wooden box contains a lamp that represents
the heater and a fan. The box contains a thermocouple of K-type to measure the actual temperature of the system and
acts as feedback.  
- The system has only two states heating (Lamp is ON and Fan is OFF) or cooling (Lamp is OFF and Fan is ON), the
controller will switch between these two states to keep the temperature at the desired set point.  
## Components:
- Ardunio Uno.
- Wooden box.
- Lamp.
- DC Fan.
- Thermocouple K-Type.
- Max 6675 module.
- Relay module for Arduino.

# Software
Using Arduino IDE
### MAX6675    
   [MAX6675 Thermocouple](https://how2electronics.com/industrial-thermometer-max6675-thermocouple-arduino/)  
  ![N|Solid](https://i.ibb.co/61CTTv5/Capture.png) 
```c  
#define MAX6675_SO  8
#define MAX6675_CS  9
#define MAX6675_SCK 10
```
### Two Channel Relay Arduino  
   [Two Channel Relay Arduino](https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/)  
  ![N|Solid](https://i.ibb.co/dGrJRjg/Capture.png) 
  
```c  
#define LAMP  3
#define FAN  2
```

### PID
   Using [PID Arduino Library](https://playground.arduino.cc/Code/PIDLibrary/) using this [Example](https://playground.arduino.cc/Code/PIDLibraryRelayOutputExample/)    Note That --> Set Point in Celsius  
```c  
/********    PID SYSTEM    *******/
#define Kp  800
#define Kd  2
#define Ki  30
//sampling range 
#define WINDOW_SIZE 400
unsigned long global_windowStartTime;
unsigned long global_u32TimeNow;
unsigned long global_u32ActualTime;
//PID input
double ThermoCoupleReading ;
//PID OUTPUT will goto lamp  
double LampControl ;
//PID SET POINT
double global_u8setPoint = 40.00;
bool global_boolCheckCompute = 0 ; 
/**************************************/
```
# Youtube Video  
https://youtu.be/-581kQJC1bE
# Contributing  
Bug reports, feature requests, and so on are always welcome. Feel free to leave a note in the Issues section.
