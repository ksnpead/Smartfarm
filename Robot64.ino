#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

// Motor pins
int E1 = 10;
int M1 = 12;
int E2 = 11;
int M2 = 13;

//OLED
#define SCREEN_WIDTH 128 // pixel ความกว้าง
#define SCREEN_HEIGHT 32 // pixel ความสูง 
#define OLED_RESET -1 //ขา reset เป็น -1 ถ้าใช้ร่วมกับขา Arduino reset
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Ultrasonic pins
const int trigPin = 7;
int echoPin = 8;
int st;


void setup() {
    pinMode (M1, OUTPUT);
    pinMode (M2, OUTPUT);
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    st=0; 
    float cm = ReadUS();
    OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
    float cm = ReadUS();
    ShowOLED(cm);
    MS();
//    MF(255,255);
//    delay(3000);
//    MR1(255,255);
//    delay(3000);
//    ML1(255,255);
//    delay(3000);
//    MB(255,255);
//    delay(3000);







    
//    switch(st)
//    {
//      case 0:
//             if(cm < 10){ MR1(255,255); delay(3000); MS();st=1;} 
//             else { MF(255,255);} break; 
//      case 1:
//             if(cm < 15){ ML1(255,255); delay(3000); MS();st=2;} 
//             else { MF(255,255);} break; 
//      case 2:
//             if(cm < 20){ MR1(255,255); delay(3000); MS();st=3;} 
//             else { MF(255,255);} break;
//      case 4:
//             if(cm < 15){ MR2(255); delay(3000); MS();st=4;} break; 
//      default: MS();  break; 
//    }
}
void MS() {
      digitalWrite (M1, HIGH);
      digitalWrite (M2, HIGH);
      analogWrite (E1, 0); // PWM speed control
      analogWrite (E2, 0); // PWM speed control
}
void MF(int sp1,int sp2) {
      digitalWrite (M1, HIGH);
      digitalWrite (M2, HIGH);
      analogWrite (E1, sp1); // PWM speed control
      analogWrite (E2, sp2); // PWM speed control
      }
void MB(int sp1,int sp2) {
      digitalWrite (M1, LOW);
      digitalWrite (M2, LOW);
      analogWrite (E1, sp1); // PWM speed control
      analogWrite (E2, sp2); // PWM speed control
}
void MR1(int sp1,int sp2) {
      digitalWrite (M1, LOW);
      digitalWrite (M2, HIGH);
      analogWrite (E1, sp1); // PWM speed control
      analogWrite (E2, sp2); // PWM speed control}
}
void MR2(int sp) {
      digitalWrite (M1, LOW);
      digitalWrite (M2, HIGH);
      analogWrite (E1, 0); // PWM speed control
      analogWrite (E2, sp); // PWM speed control}
}
void ML1(int sp1,int sp2) {
      digitalWrite (M1, HIGH);
      digitalWrite (M2, LOW);
      analogWrite (E1, sp1); // PWM speed control
      analogWrite (E2, sp2); // PWM speed control
}
void ML2(int sp) {
      digitalWrite (M1, HIGH);
      digitalWrite (M2, LOW);
      analogWrite (E1, sp); // PWM speed control
      analogWrite (E2, 0); // PWM speed control}
}
float ReadUS(){
    long duration; 
    float d;   
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  
    duration = pulseIn(echoPin, HIGH);  
    d = duration/29.0/2;
    Serial.print(d);
    Serial.print(" cm");
    Serial.println();
    return d;
}
void ShowOLED(float cm)
{
    OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
    OLED.setTextColor(WHITE, BLACK); //กำหนดข้อความสีขาว ฉากหลังสีดำ
    OLED.setCursor(0, 0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
    OLED.setTextSize(2); // กำหนดขนาดตัวอักษร
    OLED.println("OLED"); // แสดงผลข้อความ 
    OLED.setTextColor(WHITE, BLACK);
    OLED.setCursor(128, 1);
    OLED.setTextSize(2);
    OLED.println(cm, DEC);
    OLED.display(); // สั่งให้จอแสดงผล
delay(500);
}
