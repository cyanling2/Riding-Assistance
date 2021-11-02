#include <SoftwareSerial.h>
SoftwareSerial xbee(7,8); // RX, TX
int buzzerpin=5;
void setup() {
  // put your setup code here, to run once:
  xbee.begin(9600);
  pinMode(buzzerpin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (xbee.available()){
    if (xbee.read()=='F'){
      //a stop sign is found
      //ring the buzzer
      digitalWrite(LED_BUILTIN, HIGH);
      tone(buzzerpin, 1000, 2000);
      
    }
  }
//  Serial.write('x');
//  delay(1500);
//  digitalWrite(buzzerpin, LOW);
  digitalWrite(LED_BUILTIN, LOW);



}
