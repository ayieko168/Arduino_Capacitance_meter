#include <Wire.h>

#define analogPin      0
#define chargePin      13
#define dischargePin   8
#define resistorValue  10000.0F  //Remember, we've used a 10K resistor to charge the capacitor

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;

void setup() {

  Serial.begin(9600);
  
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);
}

void loop() {
  digitalWrite(chargePin, HIGH);
  startTime = micros();
  while (analogRead(analogPin) < 648) {
  }

  elapsedTime = micros() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) ;



  if (microFarads > 1) {

    Serial.print("SCALE:  0.1uF-4F  ");
    Serial.print(microFarads / 2.0);
    Serial.print(" uF");
    delay(500);
  }

  else {
    nanoFarads = microFarads * 1000.0;
    Serial.print("SCALE:  0.1uF-4F  ");
    Serial.print(nanoFarads / 2.0);
    Serial.print(" nF");
    delay(500);
  }


  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);     //discharging the capacitor
  while (analogRead(analogPin) > 0) {
  }//This while waits till the capaccitor is discharged

  pinMode(dischargePin, INPUT);      //this sets the pin to high impedance

  Serial.println(" ");


}
