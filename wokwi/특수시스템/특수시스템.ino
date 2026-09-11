#include <Arduino.h>

//115p

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

}

//117p
// #define LED_R 12

// void setup() {
//   pinMode(LED_R, OUTPUT);

// }

// void loop() {
//   digitalWrite(LED_R, HIGH);
//   delay(500);
//   digitalWrite(LED_R, LOW);
//   delay(500);

// }

//119-120p

/*
#define LED_R 12
#define LED_B 11

unsigned int interval = 500;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);

}

void loop() {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_B, LOW);
  delay(interval);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, HIGH);
  delay(interval);

}
*/

/*
//121-122p
const unsigned int LED0 = 12;
const unsigned int LED1 = 11;
const unsigned int LED2 = 10;
const unsigned int LED3 =  9;
const unsigned int LED4 =  8;
const unsigned int LED5 =  7;
const unsigned int LED6 =  6;
const unsigned int LED7 =  5;

unsigned int interval = 500;

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
}

void loop() {
  digitalWrite(LED0, HIGH);
  delay(interval);
  digitalWrite(LED1, HIGH);
  delay(interval);
  digitalWrite(LED2, HIGH);
  delay(interval);
  digitalWrite(LED3, HIGH);
  delay(interval);
  digitalWrite(LED4, HIGH);
  delay(interval);
  digitalWrite(LED5, HIGH);
  delay(interval);
  digitalWrite(LED6, HIGH);
  delay(interval);
  digitalWrite(LED7, HIGH);
  delay(interval);

  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  delay(interval);
}
*/