#include <dht11.h>
#include <LiquidCrystal.h>

#define DHT11_PIN A2
dht11 DHT11;
//définition type de variable
int temperature;
int humidity;
int lum;
int distance;

//definition des ports de connection des modules
const int blueLedPin = 6;
const int greenLedPin = 10;
const int yellowLedPin = 9;
const int redLedPin = 1;
const int fanPin = 8;
const int buzzerPin = A1;
const int trigPin = 7;
const int echoPin = 13;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  // Mesure de la température et de l'humidité
  int chk = DHT11.read(DHT11_PIN);
  temperature = DHT11.temperature;
  humidity = DHT11.humidity;

  // Mesure de la luminosité
  lum = analogRead(A0);

  // Mesure de la distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Affichage des mesures sur l'afficheur LCD
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%   ");

  // Bouton pour faire défiler les informations
  if(digitalRead(13) == HIGH){
    lcd.scrollDisplayLeft();
    delay(500);
  }

  // Gestion des LED et du ventilateur en fonction de la température
  if (temperature >= 10 && temperature <= 18) {
    digitalWrite(blueLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(fanPin, LOW);
  } else if (temperature >= 19 && temperature <= 21) {
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(fanPin, LOW);
  } else if (temperature > 22) {
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(fanPin, HIGH);
  } else {
    digitalWrite(blueLedPin, LOW);
digitalWrite(greenLedPin, LOW);
digitalWrite(yellowLedPin, LOW);
digitalWrite(redLedPin, LOW);
digitalWrite(fanPin, LOW);
    }

// Gestion des LED en fonction de l'humidité
if (humidity >= 40 && humidity <= 60) {
digitalWrite(greenLedPin, HIGH);
digitalWrite(yellowLedPin, LOW);
} else {
digitalWrite(greenLedPin, LOW);
digitalWrite(yellowLedPin, HIGH);
}

// Avertissement sonore si la distance est inférieure à 20 cm
if (distance < 20) {
tone(buzzerPin, 2000);
delay(100);
noTone(buzzerPin);
} else {
noTone(buzzerPin);
}
}
