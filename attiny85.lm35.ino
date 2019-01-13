// bitelxux@gmail.com 2019

#include <SoftwareSerial.h>

// https://zeroohm.com/blogs/tutorials/how-to-setup-arduino-with-room-temperature-monitoring-using-lm36-sensor

#define RX 2
#define TX 1

float temp;
float voltage;
int pin0 = 0;
int pTemp = 3;

// First attempt, using pin2 on Attiny85 to read lm35 was allways
// giving 1023. Even with nothing connected to the pin ...
// Was the chip I used broken or may be that pin2 can't be used?

SoftwareSerial MySerial(RX,TX);

void setup() {
  // put your setup code here, to run once:

  pinMode(pin0, OUTPUT);
  digitalWrite(pin0, LOW);
  analogReference(DEFAULT);

  MySerial.begin(9600);
  initSequence();

}

float initSequence(){
  for (int i=0; i<3; i++) {
     digitalWrite(pin0, HIGH);
     delay(200);
     digitalWrite(pin0, LOW);
     delay(200);
  }
}

float getVoltage(int pin){
  //return (analogRead(pin)*0.004882814);
  return ((analogRead(pin)/1024.0)*5000); // 5Volts VCC
}

void loop() {

   voltage = getVoltage(pTemp);
   temp = voltage/10;

   MySerial.print("mVolts: ");
   MySerial.print(voltage);

   MySerial.print(" ");
   MySerial.print("Temp: ");
   MySerial.print(temp);

   MySerial.print("\n");

   if (temp < 20) {
     digitalWrite(pin0, HIGH);
     delay(200);
     digitalWrite(pin0, LOW);
     delay(200);
   }
   else {
     digitalWrite(pin0, HIGH);
     delay(20);
     digitalWrite(pin0, LOW);
     delay(2000);
   }

}
