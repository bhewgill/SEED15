// EMPI Usage Monitoring
// Blake Hewgill, University of Vermont
// Capstone Design, Spring 2017
boolean testMode = true;

#include <EEPROM.h>
#include <SPI.h>
#include <lib_aci.h>
#include <aci_setup.h>
#include "services.h"

int buttonPin = 1; // pin for sync button
int LED1 = 2; // Status lights
int LED2 = 3;
int LED3 = 4;
int sensorPin1 = A0;    // select the input pin for channel 1
int sensorPin2 = A1;    // select the input pin for channel 2
int sensorValue = 0;  // variable to store the value coming from the sensor
int sampleNum = 0;  // Sample number
int sampleArray[140]; // Should be 90 samples in an hour long session (one each 40 seconds). Extras to be safe.
long arrayTot = 0; // A running sum of the contents of sampleArray to be divided by sampleNum for averaging
float arrayAvg = 0; // A running avg of the above
int sampleArray2[140]; // Should be 90 samples in an hour long session (one each 40 seconds). Extras to be safe.
long arrayTot2 = 0; // A running sum of the contents of sampleArray to be divided by sampleNum for averaging
float arrayAvg2 = 0; // A running avg of the above
byte sessionCount;


void setup(){
 // Initialize what we need in here 
 sessionCount = EEPROM.read(0);
 // UPLOAD EEPROM SHITE
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT);
 if (testMode){ //start serial com
   Serial.begin(9600);
   Serial.print("SessionCount = ");
   Serial.println(sessionCount);
 }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
  ArrayAdd(IntensityMap(ChannelSample()), sampleNum);
  
  ButtonInterrupt();
  
  if (testMode){
    Serial.println("TEST MODE ACTIVE");
    Serial.print("EEPROM address 0 = ");
    Serial.println(EEPROM.read(0),HEX);
    Serial.println(EEPROM.read(0));
    Serial.print("SampleNumber = "); Serial.println(sampleNum);
    Serial.println("------------Loop Complete-------------");
    delay(500);
  }
  CheckSession();
}

//////////////////////////////////////////////////////////////////////////////////////////
void ButtonInterrupt(){
  if (digitalRead(buttonPin)){
    // BLUETOOTH CODE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void CheckSession(){
  if (sampleNum>90){
    RehabComplete();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void RehabComplete(){
  Serial.println("RehabCompleteNotWritten");
  sessionCount++;
  EEPROM.put(0,sessionCount);
}
//////////////////////////////////////////////////////////////////////////////////////////
void PartialEEPROM(){
  
}
//////////////////////////////////////////////////////////////////////////////////////////
void ArrayAdd(float intensityValue, int sampleNum){
  sampleArray[sampleNum] = intensityValue;
  sampleArray2[sampleNum] = intensityValue;
  sampleNum++;
  arrayTot = arrayTot + intensityValue;
  arrayTot2 = arrayTot2 + intensityValue;
  arrayAvg = arrayTot/(sampleNum+1);
  arrayAvg2 = arrayTot2/(sampleNum+1);
}
//////////////////////////////////////////////////////////////////////////////////////////
int ChannelSample(){ // Return the highest analog input value
  int maxVolt = 0;
  int maxVolt2 = 0;
  if (testMode && analogRead(sensorPin1) < 5){
    Serial.println("Nothing to be read");
  }
  while (analogRead(sensorPin1)>5 || analogRead(sensorPin2)>5){
    if (analogRead(sensorPin1)>maxVolt){
      maxVolt = analogRead(sensorPin1);
    }
    if (analogRead(sensorPin2)>maxVolt2){
      maxVolt2 = analogRead(sensorPin2);
    }
  }
    return maxVolt;
}
///////////////////////////////////////////////////////////////////////////////////////////
float IntensityMap(int sensorValue){
  float intensity;
  // Nested if’s/elseif reduce processor load and speed up the cycle time
  if (sensorValue < 683)
{
	if (sensorValue < 393) 
	{
		if (sensorValue < 203)
		{
                    if (sensorValue < 101)
                    {
	            if (sensorValue < 50)
	            {
	            intensity = .5;
	            }
                    else if (sensorValue >= 50)
                    {
                    intensity = 1.0;
                  }
          }
else if (sensorValue >= 101)
{
	if (sensorValue < 151)
	{
	intensity = 1.5;
	}
	else if (sensorValue >= 151)
	{
	intensity = 2.0;
	}
}
		}
		else if (sensorValue >= 203)
		{
			if (sensorValue < 299)
			{
				if (sensorValue < 251)
				{
				intensity = 2.5;
				}
				else if (sensorValue >= 251)
				{
				intensity = 3.0;
				}
			}
			else if (sensorValue >= 299)
			{
				if (sensorValue < 345)
				{
				intensity = 3.5;
				}
				else if (sensorValue >= 345)
				{
				intensity = 4.0;
				}
			}
		}
	}
	else if (sensorValue >= 393)
	{
		if (sensorValue < 594)
		{
			if (sensorValue < 479)
			{
				if (sensorValue < 438)
				{
				intensity = 4.5;
				}
				else if (sensorValue >= 438)
				{
				intensity = 5.0;
				}
			}
			else if (sensorValue >= 479)
			{
				if (sensorValue < 538)
				{
				intensity = 5.5;
				}
				else if (sensorValue >= 538)
				{
				intensity = 6.0;
				}
				
			}
		}
		else if (sensorValue >= 594)
		{
			if (sensorValue < 658)
			{
				if (sensorValue < 627)
				{
				intensity = 6.5;
				}
				else if (sensorValue >= 627)
				{
				intensity = 7.0;
				}
			}
			else if (sensorValue >= 658)
			{
			intensity = 7.5;
			}
		}
	}
}
else if (sensorValue >= 683)
{
	if (sensorValue < 876)
	{
		if (sensorValue < 786)
		{
			if (sensorValue < 737)
			{
				if (sensorValue < 706)
				{
				intensity = 8.0;
				}
				else if (sensorValue >= 706)
				{
					if (sensorValue < 724)
					{
					intensity = 8.5;
					}
					else if (sensorValue >= 724)
					{
					intensity = 9.0;
					}
				}
			}
			else if (sensorValue >= 737)
			{
				if (sensorValue < 758)
				{
				intensity = 9.5;
				}
				else if (sensorValue >= 758)
				{
                                intensity = 10.0;
				}
			}
		}
		else if (sensorValue >= 786)
		{
			if (sensorValue < 816)
			{
			intensity = 11.0;
			}
			else if (sensorValue >= 816)
			{
				if (sensorValue < 847)
				{
				intensity = 12.0;
				}
				else if (sensorValue >= 847)
				{
				intensity = 13.0;
				}
			}
		}
	}
	else if (sensorValue >= 876)
	{
		if (sensorValue < 961)
		{
			if (sensorValue < 933)
			{
				if (sensorValue < 905)
				{
				intensity = 14.0;
				}
				else if (sensorValue >= 905)
				{
				intensity = 15.0;
				}
			}
			else if (sensorValue >= 933)
			{
			intensity = 16.0;
			}
		}
		else if (sensorValue >= 961)
		{
			if (sensorValue < 1010)
			{
				if (sensorValue < 989)
				{
				intensity = 17.0;
				}
				else if (sensorValue >= 989)
				{
				intensity = 18.0;
				}
			}
			else if (sensorValue >= 1010)
			{
				if (sensorValue < 1020)
				{
				intensity = 19.0;
				}
				else if (sensorValue >= 1020)
				{
				intensity = 20.0;
				}
			}
		}		

	}
}
intensity = (intensity*4);
if (testMode){
  Serial.print("Intensity = ");
  Serial.println(intensity);
}
return intensity;
}
