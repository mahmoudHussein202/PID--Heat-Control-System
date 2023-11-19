/*****    Logic Preprocessor    *****/
#define RELAY_ON 1
#define RELAY_OFF 0

/**********    MAX6675    **********/
#define MAX6675_SO  8
#define MAX6675_CS  9
#define MAX6675_SCK 10
/*******   LAMP&FAN Pinout ********/
#define LAMP  3
#define FAN  2
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
/***************************************/
#include "max6675.h"
#include <PID_v1.h>
/*
 * MAX6675_SCK: Serial Clock
 * MAX6675_CS:  Chip Select
 * MAX6675_SO:  Serial output  
 * TH-: Negative side input
 * TH+: Positive side input
 *  
 */
MAX6675 thermoCouple (MAX6675_SCK,MAX6675_CS,MAX6675_SO);
/*
 * Input: The variable we're trying to control (double)
 * Output: The variable that will be adjusted by the pid (double) 
 * Setpoint: The value we want to Input to maintain (double) 
 * Kp, Ki, Kd  >0 
 * 
 */
PID myPID(&ThermoCoupleReading,&LampControl,&global_u8setPoint, Kp, Ki, Kd, DIRECT);

void setup() {
  /*  Serial INIT */
  Serial.begin(9600);
  delay(2);
  /*  Init Vars.  */
  global_windowStartTime = global_u32TimeNow = global_u32ActualTime = ThermoCoupleReading =  LampControl = 0; 
  /*  MAX6675 INIT. */

  /*  LAMP&FAN INIT */
  pinMode(LAMP, OUTPUT);
  pinMode(FAN, OUTPUT);
  /*  PID INIT  */
  PID_voidIntialization(WINDOW_SIZE,&myPID);
  
}

void loop() {
  
  // Take input of PID
  ThermoCoupleReading = thermoCouple.readCelsius();
  global_boolCheckCompute = myPID.Compute();
  delay(100);
  if(global_boolCheckCompute == 1)
  {
     global_u32TimeNow = millis();
     global_u32ActualTime = global_u32TimeNow - global_windowStartTime ; 
     if(global_u32ActualTime > WINDOW_SIZE ) 
     {
      global_windowStartTime += WINDOW_SIZE; 
     }
     
    if (LampControl > global_u32TimeNow - global_windowStartTime)
    {
    //  Serial.println("Lamp On");
      digitalWrite(LAMP,LOW);
      digitalWrite(FAN,HIGH);
     /* voidLampControl(RELAY_ON);
      voidFanControl (RELAY_OFF);*/
    
    }
    else 
    {
    
    digitalWrite(LAMP,HIGH);
    digitalWrite(FAN , LOW);
    }
  }
  else
  {
    // ReCompute
    Serial.println("Fail to compute PID algo");
  }  
Serial.println (ThermoCoupleReading);
delay (200);
}
void voidLampControl(char copy_charState)
{
  switch(copy_charState)
  {
    case RELAY_ON:
      digitalWrite(LAMP, RELAY_ON); 
      break ;
    case RELAY_OFF: 
      digitalWrite(LAMP, RELAY_OFF);
      break ;
    default: break;
  }
}
void voidFanControl(char copy_charState)
{
  switch(copy_charState)
  {
    case RELAY_ON:
      digitalWrite(FAN, RELAY_ON); 
      break ;
    case RELAY_OFF: 
      digitalWrite(FAN, RELAY_OFF);
      break ;
    default: break;
  }
}
void PID_voidIntialization(int copy_u16WindowSize, PID *myPID  )
{
  //start calc time
  global_windowStartTime = millis();
  // set limits from 0 to WindowSize instead of 0 to 255 PWM
  myPID->SetOutputLimits(0, copy_u16WindowSize);  
  //turn the PID on
  myPID->SetMode(AUTOMATIC);
}
