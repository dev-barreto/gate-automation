//#define WOKWI

/*
  Forum: https://forum.arduino.cc/t/automating-a-gate-project/1168477
  Wokwi: https://wokwi.com/projects/375852170316319745

  If "WOKWI" is defined ( see #define WOKWI in line 1) the WiFi parts are excluded from the sketch
  as they are not required for the first steps

*/


#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Time.h>
//#include <RTClib.h>

// Configurações da Rede
const char* ssid = "ssid_name";
const char* password = "ssid_password";

// Informações de data e Hora
//RTC_DS3231 rtc;

constexpr byte gateSensor = 2; // Pino onde o sensor do portão está conectado
constexpr byte photocellsPin = 4;  // Pino onde as fotocélulas estão conectadas
constexpr byte commandGatePin = 15; // Pino para o comando de abertura do portão
constexpr byte gateStatePin   = 19; // Pino que envia sinal quanto portão está fechado

enum gateModes {MORNING, EVENING, RESTOFDAY, UNKNOWN};
gateModes gateMode = UNKNOWN;

byte gateState = LOW;

void setup() {

  pinMode(gateSensor, INPUT_PULLUP); // Pino em modo de entrada de informações  // ****** Added PULLUP
  pinMode(photocellsPin, OUTPUT); // Pino em modo de saida de informações // White on = HIGH
  pinMode(commandGatePin, OUTPUT); // Pino em modo de saida de informações  // Blue on = HIGH
  pinMode(gateStatePin, OUTPUT);      // Pin to show the state of the gate (Green on = Open/HIGH)

  // Connect rtc
//  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
//    abort();
//  }
//  Serial.begin(115200);
//  delay(1000);

#ifndef WOKWI
  // Conecção WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password, 6);
  Serial.println("\nConnecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.println(WiFi.ssid());
Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
#endif
  Serial.println("Start of loop()");
}

void loop() {
  // Obtém a hora atual
  int realTime = getHour(true);  // change parameter to "true" for RTC time and "false" for fake Hour
  gateState = getGateState();
  byte mode = 0;
  switch (realTime) {
    case 6 : openGate();
      break;
    case 19 : closeGate();
      break;
//    default : standardHandling();
//      break;
  }
}

int getFakeHour() {
  static int hour = 0;
  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case  'm' : hour = 6;   //m for Morning routine
        break;
      case  'e' : hour = 19;  // e for Evening routine
        break;
//      case  'r' : hour = 12;  // r for Rest of Day routine
 //       break;
    }
  }
  return hour;
}

int getHour(boolean trueTime) {
  if (!trueTime) {
    return getFakeHour();
  }
  static int lastSecond = -1;
  DateTime now = rtc.now();
  if (now.second() != lastSecond) {
    Serial.printf("%.2d:%.2d:%.2d\n", now.hour(), now.minute(), now.second());
    lastSecond = now.second();
  }
  return now.hour();
}


void openGate() {
  if (gateMode == MORNING) {
    return;
  }
  if (gateState == LOW) {
    // Sensor HIGH às 06:00h, desativa as fotocélulas
    digitalWrite(photocellsPin, LOW);
  } else {
    // Sensor HIGH às 06:00h, desativa as fotocélulas e envia comando de abertura do portão
    digitalWrite(photocellsPin, LOW);
    digitalWrite(commandGatePin, HIGH);
    delay(1000);
    digitalWrite(commandGatePin, LOW);
  }
  gateMode = MORNING;
  Serial.println("MORNING");
}

void closeGate() {
  if (gateMode == EVENING) {
    return;
  }
  if (gateState == HIGH) {
    // Sensor LOW às 19:00h, ativa as fotocélulas
    digitalWrite(photocellsPin, HIGH);
  } else {
    // Sensor HIGH às 19:00h, ativa as fotocélulas e envia comando de fechamento do portão
    digitalWrite(photocellsPin, HIGH);
    digitalWrite(commandGatePin, HIGH);
    delay(1000);
    digitalWrite(commandGatePin, LOW);
  }
  gateMode = EVENING;
  Serial.println("EVENING");
}

//void standardHandling() {
//  if (gateMode == RESTOFDAY) {
//    return;
//  }
  // Em outros horários, desativa as fotocélulas e os comandos do portão
//  digitalWrite(commandGatePin, LOW);
//  gateMode = RESTOFDAY;
//  Serial.println("REST OF DAY");
//}



byte getGateState() {
  static byte gState = LOW;
  static byte lastStateRead = LOW;
  static unsigned long lastChange = 0;
  byte actState = digitalRead(gateSensor);
  if (actState != lastStateRead) {
    lastStateRead = actState;
    lastChange = millis();
  }
  if (millis() - lastChange > 30 && gState != lastStateRead) {
    gState = lastStateRead;
    digitalWrite(gateStatePin, gState);
  }
  return gState;
}