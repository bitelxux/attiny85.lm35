// bitelxux@gmail.com 2019

#include <SoftwareSerial.h>

// https://zeroohm.com/blogs/tutorials/how-to-setup-arduino-with-room-temperature-monitoring-using-lm36-sensor

#define RX 2
#define TX 1

bool state = false;
bool alert = false;
unsigned long interval = 2000;
unsigned long previousMillis;

unsigned long readInterval = 1000;
unsigned long previousReadMillis;

float tempPrev = -100;
float temp;
float avTemp;
float voltage;
int pin0 = 0;
int pTemp = 3;


// First attempt, using pin2 on Attiny85 to read lm35 was allways
// giving 1023. Even with nothing conn ected to the pin ...
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
     toggleLed();
     delay(200);
     toggleLed();
     delay(200);
  }
  delay(2000);
}

float getVoltage(int pin){
  //return (analogRead(pin)*0.004882814);
  return ((analogRead(pin)/1024.0)*5000); // 5Volts VCC
}

void toggleLed()
{
   state = !state;

   if (state){
    digitalWrite(pin0, HIGH);
    if (!alert){
      delay(20);
      state = !state;
     }
   }

   if (!state) digitalWrite(pin0, LOW);
}

void readData(){
   voltage = getVoltage(pTemp);
   temp = voltage/10;

   // Average last readings to minimice errors
   if (tempPrev != -100){
    avTemp = (temp + tempPrev)/2.0;
    tempPrev = temp;
   }
   else {
    tempPrev = temp;
   }

   alert = avTemp < 20;
   interval = alert ? 200 : 2000;

   MySerial.print("mVolts: ");
   MySerial.print(voltage);

   MySerial.print(" ");
   MySerial.print("Temp: ");
   MySerial.print(avTemp);

   MySerial.print("\n");
}

void loop() {

   unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= interval){
    toggleLed();
    previousMillis = millis();
   }

   if (currentMillis - previousReadMillis >= readInterval){
    readData();
    previousReadMillis = millis();
   }

}
