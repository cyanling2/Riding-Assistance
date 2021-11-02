#include <SoftwareSerial.h>
SoftwareSerial xbee(2,8); // RX, TX
//int led=13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("begin:");
  xbee.begin(9600);
//  pinMode(led, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("a");
  if (xbee.available()>0){
//    byte c=xbee.read();
    Serial.println(xbee.read());
    delay(2000);
//    if(c=='s'){
////      Serial.println(c);
////      delay(3000);
//      digitalWrite(led, HIGH);
//      delay(1000);
//      digitalWrite(led, LOW);
//      delay(1000);
//      digitalWrite(led, HIGH);
//      delay(1000);
//      digitalWrite(led, LOW);
//    }
  }

}
