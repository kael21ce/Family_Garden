#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성
int value = 0;    // 각도를 조절할 변수 value

#include <SoftwareSerial.h>

int pinTx = 2;
int pinRx = 3;
const int LED1 = 6;
int i = 0;
//LED변수, MOTER변수 기본값 지정
// <<<<<<< Updated upstream
int valLED = 0;
// =======
int LED = LED1;
// >>>>>>> Stashed changes
int MOTER = 0 ;
 
SoftwareSerial bluetooth(pinTx,pinRx);
 

void setup()
{
  pinMode(7,INPUT); // 스위치와 연결한 핀을 입력핀으로 설정
  //출력 핀 설정
  pinMode(LED,OUTPUT);
  //시리얼 통신 시작
  Serial.begin(9600);
  //블루투스 시리얼 통신 시작  
  bluetooth.begin(9600);
  servo.attach(9);     //servo 서보모터 9번 핀에 연결
  // 이때 ~ 표시가 있는 PWM을 지원하는 디지털 핀에 연결
}
 
 
void loop()
{ 
  //시리얼 통신 가능 시, 블루투스 통해 앱으로 통신
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
  // 스위치 누르기 전엔 아무것도 안하기, 누르면 이거 시작(위에 추가 코드)
  int readValue = digitalRead(7); // 입력핀의 값(스위치)을 읽어 변수에 저장
  //Serial.println(readValue); // 변수의 값을 시리얼 모니터에 출력

  while(readValue == HIGH){//스위치가 아래로 내려가면
    //블루투스 통신 가능 시, 블루투스 통해 하드웨어로 통신
    if (bluetooth.available()) {
      //앱에서 받아온 신호 읽어오기
      //int ch = bluetooth.read();
      int ch = 53;
      //신호 보여주기
      Serial.println(ch);
      //앱에서 받아온 신호가 '1'이면 LED 밝기를 255/3으로 설정->1인데 왜 49라고 써놓음?->아스키코드 전환
      if (ch==49){
        MOTER = valLED; //모터변수에 LED변수 넣어주기
        if (MOTER == 0) //모터변수=LED변수가 0이면
        {
          value = 0; // LED값이 0이면 모터가 90회전한 상태일 것으로 그대로 있기
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          valLED=0;
        } else if(MOTER == 255/3)
        {
          value = -90; // LED값이 255/3이면 모터가 180회전한 상태일 것으로 -90도 더 돌려서 90도로
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          for(i = valLED ; i>=0 ; i--) // LED변수=255/3를 i에 넣고 0보다 같거나 클때까지 i를 (-)
          {
            analogWrite(LED,i);
            delay(10);
          }
          valLED=0;
        } else // MOTER==255
        {
          value = -180; // LED값이 255이면 모터가 270도 회전한 상태일 것으로 -180도 더 돌려서 90도로
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          for(i = valLED ; i>=0 ; i--) // LED변수=255를 i에 넣고 0보다 같거나 클때까지 i를 (-)
          {
            analogWrite(LED,i);
            delay(10);
          }
          valLED=0;
        }
//  <<<<<<< Updated upstream
      } else if (ch==50 || ch==51){
        MOTER = valLED; //모터변수에 LED변수 넣어주기
//  =======
      } 
      else if(ch==50&ch==51){
        MOTER = LED; //모터변수에 LED변수 넣어주기
//  >>>>>>> Stashed changes
        if (MOTER == 255/3) //모터변수=LED변수가 255/3이면
        {
          value = 0; // LED값이 255/3이면 모터가 180도 회전한 상태일 것으로 그대로 있기
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          valLED=255/3;
        } else if(MOTER == 0)
        {
          value = 180; // LED값이 0이면 모터가 90도 회전한 상태일 것으로 90도 더 돌려서 180도로
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          for(i = valLED ; i<=255/3 ; i++) // LED변수=0를 i에 넣고 255/3보다 같거나 작을때까지 i를 (+)
          {
            analogWrite(LED,i);
            delay(10);
          }
          valLED=255/3;
        } else //MOTER==255
        {
          value = -90; // LED값이 255이면 모터가 270도 회전한 상태일 것으로 -90도 더 돌려서 180도로
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          for(i = valLED ; i>=255/3 ; i--) // LED변수=255를 i에 넣고 255/3보다 같거나 클때까지 i를 (-)
          {
            analogWrite(LED,i);
            delay(10);
          }
          valLED=255/3;
        }
      }  else {   //ch==52 || ch==53
        MOTER = valLED; //모터변수에 LED변수 넣어주기
        if (MOTER == 255) //모터변수=LED변수가 255이면
        {
          value = 0; // LED값이 255이면 모터가 270도 회전한 상태일 것으로 그대로 있기
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          valLED=255;
        } else if(MOTER == 0)
        {
          value = 180; // LED값이 0이면 모터가 90도 회전한 상태일 것으로 180도 더 돌려서 270도로
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          for(i = valLED ; i<=255 ; i++) // LED변수=0를 i에 넣고 255보다 같거나 작을때까지 i를 (+)
          {
            analogWrite(LED,i);
            delay(10);
          }
          valLED=255;
        } else //MOTER==255/3
        {
          value = 90; // LED값이 255/3이면 모터가 180도 회전한 상태일 것으로 90도 더 돌려서 270도로
          servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
          delay(500);
          for(i = LED ; i<=255 ; i++) // LED변수=255를 i에 넣고 255보다 같거나 클때까지 i를 (+)
          {
            analogWrite(LED,i);
            delay(10);
          }
          valLED=255;
        }
      }
    }
  }
}
