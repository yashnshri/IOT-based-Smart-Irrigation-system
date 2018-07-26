#include "dht.h"
#define dht_apin 12 // DHT11
#include "LiquidCrystal.h";
const int buzzer = 13;
dht DHT;
int sensor_pin = A0;
int output_value;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int led = 13;

void setup() {

  Serial.begin(9600);
  delay(500);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);
  Serial.println("Reading From the Sensor ...");

  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("HACKTHON 5.0");
  lcd.setCursor(2, 1);
  lcd.print("Hello,AD_26");
  delay(5000);
  lcd.clear();

  pinMode(buzzer, OUTPUT);

}//end "setup()"


void loop() {
  //Start of Program

  DHT.read11(dht_apin);

  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C  ");
  // Temperature
  lcd.setCursor(2, 0);
  lcd.print("Temp=");
  lcd.setCursor(7, 0);
  lcd.print(DHT.temperature);
  lcd.setCursor(13, 0);
  lcd.print("C");
   if (DHT.temperature > 32 || DHT.temperature < 4  ) {
    lcd.setCursor(2, 1);
    lcd.print("Sit:Critical");
    delay(3000);
    lcd.clear();
  } else {
    lcd.setCursor(2, 1);
    lcd.print("Sit:Normal  ");
    delay(3000);
    lcd.clear();
  }
  
  //HDTY
  lcd.setCursor(2, 0);
  lcd.print("HDTY=");
  lcd.setCursor(7, 0);
  lcd.print(DHT.humidity);
  lcd.setCursor(12, 0);
  lcd.print(" %");
  if ( DHT.humidity > 55 || DHT.humidity<10  ) {
    lcd.setCursor(2, 1);
    lcd.print("Sit:Critical");
    delay(3000);
    lcd.clear();
  } else {
    lcd.setCursor(2, 1);
    lcd.print("Sit:Normal  ");
    delay(3000);
    lcd.clear();
  }

 //SMS
    output_value = analogRead(sensor_pin);
    output_value = map(output_value, 550, 0, 0, 100);
    Serial.print("Mositure : ");
    Serial.print(output_value);
    Serial.println("%");
    lcd.setCursor(2, 0);
    lcd.print("Moist=");
    lcd.setCursor(8, 0);
    lcd.print(output_value);
    if (output_value > 30 || output_value < -30 ) {
      lcd.setCursor(2, 1);
      lcd.print("Sit:Critical");
      delay(3000);
    } else {
      lcd.setCursor(2, 1);
      lcd.print("Sit:Normal  ");
      delay(3000);
    }
    if (DHT.temperature > 32 || DHT.temperature < 4 || DHT.humidity > 55 || DHT.humidity<10 || output_value > 30 || output_value < -30)
    {
      tone(buzzer, 500);
      delay(3000);
      noTone(buzzer);
    } else {
      noTone(buzzer);
    }
    //End of program
    delay(1000);
  }
