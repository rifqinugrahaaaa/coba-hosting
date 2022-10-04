/*Plant watering system with new blynk update
   Home Page
*/
//Include the library files
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "OkdVN-Vu3grvrnAy9pZu_GbXZ04sMy38";//Enter your Auth token
char ssid[] = "rifqinugraha";//Enter your WIFI name
char pass[] = "Rifqi190803";//Enter your WIFI password

BlynkTimer timer;

//Define component pins
#define sensor A0
#define relay D4

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  lcd.begin();
  lcd.backlight();

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  lcd.setCursor(1, 0);
  lcd.print("Nungguin yaaa");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(100);
  }
  lcd.clear();




  //Call the function
  timer.setInterval(100L, soilMoistureSensor);
}

//Get the button value
//BLYNK_WRITE(V1) {
//  Relay = param.asInt();
//
//  if (Relay == 1) {
//    digitalWrite(waterPump, LOW);
//    lcd.setCursor(0, 1);
//    lcd.print("Motor is ON ");
//  } else {
//    digitalWrite(waterPump, HIGH);
//    lcd.setCursor(0, 1);
//    lcd.print("Motor is OFF");
//  }
//}


//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);
  lcd.setCursor(0, 0);
  lcd.print(" Kelembapan :");
  lcd.print(value);
  lcd.print(" ");

  if (value < 30 ) {
  digitalWrite(relay, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Kering");
} 

  else if (value > 30 < 50) {
  digitalWrite(relay, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Normal");
}
  else if (value > 50) {
  digitalWrite(relay, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Basah"  );
}

}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
