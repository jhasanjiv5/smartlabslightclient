
#include "MQ135.h"

#define ArrayLenth  40
#define samplingInterval 20
#define Offset 0.00
#define SensorPin A3
#define printInterval 800
MQ135 gasSensor = MQ135(0);
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex = 0;
//#define RZERO 76.63


void setup()
{

  Serial.begin(9600);
  //Set serial baud rate to 9600 bps
}

void loop()
{
  delay(printInterval);
  
  float CO;
  float turbidity;
  float ph;
  float rzero = gasSensor.getRZero();
  float CO2 = (gasSensor.getPPM()*(1024/5)-rzero)/10;
  //val=analogRead(0);//Read Gas value from analog 0

  CO = analogRead(1)/10;


  int turbiditysensorvalue = analogRead(2);
  turbidity = turbiditysensorvalue * (5.0 / 1024.0);


  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue, voltage;
  if (millis() - samplingTime > samplingInterval)
  {
    pHArray[pHArrayIndex++] = analogRead(SensorPin);
    if (pHArrayIndex == ArrayLenth)pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
    pHValue = 3.5 * voltage + Offset;
    samplingTime = millis();
  }
  if (millis() - printTime > printInterval)  //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {

    Serial.println(CO2);
    //Print the analog value to serial port
    Serial.println(CO);

    Serial.println(turbidity);
    Serial.println(pHValue);


    printTime = millis();
  }



}
double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;      //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;  //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}
