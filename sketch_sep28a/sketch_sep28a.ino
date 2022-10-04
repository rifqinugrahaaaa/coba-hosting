#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

LiquidCrystal_I2C LCD(0x27,16,2);  

int pump=2;   //pin 2 pada nodemcupin 4

char auth[] = "HFtRL9ONXlPHqXPE0eVLfOWQeGPJNHuV"; // TOKEN PADA APLIKASI BLYNX 
char ssid[] = "rifqinugraha";                                   //NAMA HOTSPOT 
char pass[] = "Rifqi190803";                                  //PASSWORD HOTSPOT

SimpleTimer timer;
WidgetLCD lcd(V1); 

void sendSensor()
{                         //lcd to android && LCD to board lcd 
  int POT = analogRead(A0); 
  lcd.print(0,0,"KEADAAN");   LCD.setCursor(0,0);LCD.print("ADC");LCD.setCursor(4,0);LCD.print(POT);LCD.print(" ");
  lcd.print(0,1,"PUMP");      LCD.setCursor(0,1);LCD.print("PUMP");
  Blynk.virtualWrite(V0, POT);
  
  if (POT>1000){
  Serial.println("KERING");//ke serial monitor
  lcd.print(8,0,"KERING");      LCD.setCursor(9,0);LCD.print("KERING");
  lcd.print(5,1,"ON ");         LCD.setCursor(5,1);LCD.print("ON ");
  digitalWrite(pump,LOW);
  }
  
  else if (POT>600&&POT<1000){
  Serial.println("NORMAL");
  lcd.print(8,0,"NORMAL");      LCD.setCursor(9,0);LCD.print("NORMAL");
  lcd.print(5,1,"OFF");         LCD.setCursor(5,1);LCD.print("OFF");
  digitalWrite(pump,HIGH);
  }
  
  else if (POT<600){
  Serial.println("BASAH");
  lcd.print(8,0,"BASAH ");      LCD.setCursor(9,0);LCD.print("BASAH ");
  lcd.print(5,1,"OFF");         LCD.setCursor(5,1);LCD.print("OFF");
  
  digitalWrite(pump,HIGH);
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  
  pinMode(pump,OUTPUT);
  digitalWrite(pump, HIGH); 
  LCD.begin();
  lcd.clear();       
  LCD.backlight();
}

void loop()
{
  Blynk.run();
  timer.run();
  delay(100);
}
