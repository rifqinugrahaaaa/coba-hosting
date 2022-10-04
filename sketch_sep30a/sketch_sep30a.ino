#include <Wire.h>
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2);

int pump=2;


char auth[] = "HFtRL9ONXlPHqXPE0eVLfOWQeGPJNHuV"; //ISI TOKEN PADA APLIKASI BLYNX ANDROID
char ssid[] = "rifqinugraha";                             //NAMA HOTSPOT 
char pass[] = "Rifqi190803";                         //password hotspot

//SimpleTimer timer;
BlynkTimer timer;
WidgetLCD lcd(V1);

void sendSensor()
{                        //lcd to android && LCD to board lcd
  int POT = analogRead(A0);   LCD.setCursor(0,0);LCD.print("ADC");LCD.setCursor(,0);LCD.print(POT);LCD.print(" ");
  lcd.print(0,0,"KEADAAN");   LCD.
  
}
