#include <EngduinoLEDs.h>
#include <EngduinoButton.h>
#include <EngduinoThermistor.h> 
#include <EngduinoLight.h>
#include <EngduinoAccelerometer.h>
#include <EngduinoMagnetometer.h>
#include <Wire.h> 
#include <Wire.h> 
int state=0;
char val;
void setup() {
  // put your setup code here, to run once:
EngduinoLEDs.begin(); 
EngduinoButton.begin(); 
EngduinoThermistor.begin();
EngduinoLight.begin();
EngduinoAccelerometer.begin(); 
EngduinoMagnetometer.begin();
}

void getInput()
{
  if (Serial.available() > 0) 
  { // If data is available to read,
    val = Serial.read(); // read it and store it in val
  int led=val-'0';
    if(led>=0&&led<=15) 
    {
      EngduinoLEDs.setAll(OFF);
       EngduinoLEDs.setLED(led,RED);
    }
  } 
    
}

void loop() {
  // put your main code here, to run repeatedly:
getInput();
float accelerations[3];
EngduinoAccelerometer.xyz(accelerations);
float x = accelerations[0];
float y = accelerations[1];
float z = accelerations[2];
Serial.print("1: ");
float a = sqrt(x*x + y*y + z*z); 
Serial.println(a);

Serial.print("2: ");
float magneticField[3]; 
float d = magneticField[0];
float b = magneticField[1];
float c = magneticField[2];
Serial.print(d);
Serial.print(" ");
Serial.print(b);
Serial.print(" ");
Serial.println(c); 
Serial.print("3: ");

float f;
f = EngduinoThermistor.temperature(CELSIUS); 
Serial.println(f);

if(EngduinoButton.wasPressed()) state=!state;
Serial.print("4: ");
Serial.println(state);
delay(100); 
}
