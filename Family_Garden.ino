#include <SoftwareSerial.h>
 
int pinTx = 5;
int pinRx = 3;
bool swit = true;
 
SoftwareSerial bluetooth(pinTx,pinRx);
 

void setup()
{
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(9600);  
  bluetooth.begin(9600);
}
 
 
void loop()
{ 
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
  if (bluetooth.available()) {
    //Serial.println(bluetooth.read());
    int ch = bluetooth.read();
    Serial.println(ch);
    if (ch==49){
      analogWrite(11,0);
      analogWrite(10,128);
      analogWrite(9,128);
    } else {
      analogWrite(11,0);
      analogWrite(10,30);
      analogWrite(9,0);
    }
  }
}
