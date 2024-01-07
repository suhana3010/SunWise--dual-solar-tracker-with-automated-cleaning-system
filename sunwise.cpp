# SunWise--dual-solar-tracker-with-automated-cleaning-system
Arduino Code 
#include <Servo.h>
#include <Wire.h>
#include <BH1750.h> // Library for BH1750 light sensor

BH1750 lightSensor;

const int buzzerPin = 8; // Define the pin to which the buzzer is connected

//defining Servos
Servo servohori;
int servoh = 90;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 90; 
int servovLimitHigh = 160;
int servovLimitLow = 20;
//Assigning LDRs
int ldrtopl = A2; //top left LDR green
int ldrtopr = A3; //top right LDR yellow
int ldrbotl = A1; // bottom left LDR blue
int ldrbotr = A0; // bottom right LDR orange

 void setup () 
 {
  servohori.attach(10);
  servohori.write(90);
  servoverti.attach(9);
  servoverti.write(90);
  delay(1000);

pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
Wire.begin();
  // Initialize the BH1750 sensor
  lightSensor.begin();
 }

void loop()
{

 // Read the light level from the BH1750 sensor
  float lightLevel = lightSensor.readLightLevel();
  
  // Print the light level to the serial monitor
  Serial.print("Light Level: ");
  Serial.print(lightLevel);
  Serial.println(" lux");

  // Define a threshold for the light level (adjust as needed)
  float threshold = 50.0; // Change this value to set your desired threshold
  
  // Check if the light level is below the threshold
  if (lightLevel < threshold) {
    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  delay(1000); // Delay to avoid rapid triggering


  //printf(1);
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(100);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(100);
}
