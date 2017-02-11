#include <EngduinoLEDs.h>
#include <EngduinoButton.h>
#include <EngduinoThermistor.h>
#include <EngduinoLight.h>
#include <EngduinoAccelerometer.h>
#include <EngduinoMagnetometer.h>
#include <Wire.h>
#include <Wire.h>
#include <stdlib.h>
int state=0;
String h;
long lastCall;

void setup() {
  // put your setup code here, to run once:
  EngduinoLEDs.begin();
  EngduinoButton.begin();
  EngduinoThermistor.begin();
  EngduinoLight.begin();
  EngduinoAccelerometer.begin();
  EngduinoMagnetometer.begin();
  firstContact();
  lastCall = millis();
}

void getInput()
{
  int from=0,to=0,i=0;

  if (Serial.available() > 0)
  {
    int *values=(int*)malloc(sizeof(int)*6);
    // If data is available to read,
    h = Serial.readString(); // read it and store it in val
    while(i<6)
    {
     from=to;
      while(h.charAt(to)!=','&&to<h.length())
      {
         to++;
      }
      *(values+i)=(h.substring(from,to)).toInt(); // take the part of string which is between comas and convert it into int
      i+=1;
    to++;//skip the coma
  }
  execute(values);
  free(values);//clean memory
  }
  else if (millis() - lastCall > 200)
  {
    lastCall = millis();
    printFunction();
  }

}
//for more commands
void execute(int *values)
{
   switch(*values)
  {
    case 1: lights(values);
    break;
    default: ;
  }
}

void lights(int *values)
{
  if(*(values+2)==0)
    {
  EngduinoLEDs.setLED(*(values+1),OFF);
  return;  //break
    }
    EngduinoLEDs.setLED(*(values+1),*(values+3),*(values+4),*(values+5));
}

void printFunction()
{
  float accelerations[3];
EngduinoAccelerometer.xyz(accelerations);
float x = accelerations[0];
float y = accelerations[1];
float z = accelerations[2];
Serial.print("1: ");
float a = sqrt(x*x + y*y + z*z);
Serial.println(a);

if(EngduinoButton.wasPressed()) state=!state;
Serial.print("2: ");
Serial.println(state);

Serial.print("3: ");
float f;
f = EngduinoThermistor.temperature(CELSIUS);
Serial.println(f);
float magneticField[3];
EngduinoMagnetometer.xyz(magneticField);
float d = magneticField[0];
float b = magneticField[1];
float c = magneticField[2];
Serial.print("4: ");
Serial.print(d);
Serial.print(" ");
Serial.print(b);
Serial.print(" ");
Serial.println(c);
Serial.print("5: ");
Serial.println((int) 100 * (EngduinoLight.lightLevel() / 1023.0));
}
void firstContact() {
  while (Serial.available() <= 0) {
  printFunction();
  delay(100);
  }
}

void loop() {
   getInput();
}
