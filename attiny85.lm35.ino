// bitelxux@gmail.com 2019

#include <SoftwareSerial.h>

// https://zeroohm.com/blogs/tutorials/how-to-setup-arduino-with-room-temperature-monitoring-using-lm36-sensor

#define RX 2
#define TX 1

bool alert = false;

bool ledState = false;
unsigned long previousLedMillis = 0;

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
  delay(1000);
}

float getVoltage(int pin){
  //return (analogRead(pin)*0.004882814);
  return ((analogRead(pin)/1024.0)*5000); // 5Volts VCC
}

void aliveIndicator()
{
   ledState = true;
   digitalWrite(pin0, HIGH);
   delay(20);
   digitalWrite(pin0, LOW);
   ledState = false;
}

void toggleLed()
{
   ledState = !ledState;
   if (ledState) digitalWrite(pin0, HIGH);
   if (!ledState) digitalWrite(pin0, LOW);
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

   MySerial.print("mVolts: ");
   MySerial.print(voltage);

   MySerial.print(" ");
   MySerial.print("Temp: ");
   MySerial.print(avTemp);

   MySerial.print("\n");
}

void loop() {

   unsigned long currentMillis = millis();

   // No temperature alert. Regular low comsuption alive blink
   if (!alert and (currentMillis - previousLedMillis >= 3000)){
      aliveIndicator();
      previousLedMillis = millis();
   }

   // Alert blink
   if (alert and (currentMillis - previousLedMillis >= 300)){
      toggleLed();
      previousLedMillis = millis();
   }

   if (currentMillis - previousReadMillis >= readInterval){
    readData();
    previousReadMillis = millis();
   }

}
