#include <SoftwareSerial.h>
SoftwareSerial xbee(7,8); // RX, TX
volatile byte half_revolutions;
unsigned int rpm;
unsigned long timeold;
int led=13;
int autobrake_on;
int statusPin=10; //button switch
int switchval;
int previous=LOW;
long t = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers
int magnetPin = 12;
int stopsign_idx;
void setup()  {
   Serial.begin(9600);
   xbee.begin(9600);
   pinMode(led, OUTPUT);
   digitalWrite(led, LOW);
   pinMode(12, OUTPUT);
   pinMode(statusPin, INPUT);
   attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
   half_revolutions = 0;
   rpm = 0;
   timeold = 0;
   autobrake_on = 1; //enable
}

void loop()  {
  //read button switch status
  switchval=digitalRead(statusPin);

  if (switchval==HIGH && previous==LOW && millis() - t > debounce){
    autobrake_on=1-autobrake_on;
    t=millis();
  }
  previous=switchval;
  if(autobrake_on==0){
    //disable the autobrake system, do nothing
    digitalWrite(led, HIGH); //inidicating disable
    digitalWrite(magnetPin, LOW);
    //keep serial port and xbee port clean
    if(Serial.available()){
      Serial.read();
    }
    if(xbee.available()){
      xbee.read();
    }
    return;
  }
  digitalWrite(led, LOW); //indicating enable

  //read from PI
  if (Serial.available())
  { 
    stopsign_idx = Serial.read();
//    Serial.println(stopsign_idx);
    if(stopsign_idx>='1' && stopsign_idx<='8'){ // stop sign idx (1~8)
      xbee.write('F');
      if (stopsign_idx>='4' && rpm>3){
        // too close, brake!
        digitalWrite(magnetPin, HIGH);
      }
    }
  }
  if (rpm<=3){
    digitalWrite(magnetPin, LOW);
  }

  //speed calculation
  if (half_revolutions >= 2) { 
     rpm = 30*1000/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
//     Serial.println(rpm,DEC);
   }

  
}

 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   half_revolutions++;
//   Serial.println("detect");
 }
