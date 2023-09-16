#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>

// Configurações da Rede
const char* ssid = "username";
const char* password = "password";

// Informações de data e Hora
RTC_DS3231 rtc;

const int gateSensor = 2; // Pino onde o sensor do portão está conectado
const int photocellsPin = 3;  // Pino onde as fotocélulas estão conectadas
const int commandGatePin = 4; // Pino para o comando de abertura do portão

void setup(){

  pinMode(gateSensor INPUT); // Pino em modo de entrada de informações
  pinMode(photocellsPin, OUTPUT); // Pino em modo de saida de informações
  pinMode(commandGatePin, OUTPUT); // Pino em modo de saida de informações


  // Conecção WiFi
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.println(WiFi.ssid());
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

}

void loop(){

  // Obtém a hora atual
  int realTime = hour();
  
  // Obtém o estado do sensor do portão
  int gateState = digitalRead(gateSensor);

    // Verifica a hora atual e o estado do sensor para tomar decisões
  if (realTime == 19) {
    if (gateState == HIGH) {
      // Sensor HIGH às 19:00h, libera as fotocélulas
      digitalWrite(photocellsPin, HIGH);
    } else {
      // Sensor LOW às 19:00h, libera as fotocélulas e envia comando de fechamento do portão
      digitalWrite(photocellsPin, HIGH);
      digitalWrite(commandGatePin, HIGH);
    }
  } else if (realTime == 6) {
    if (gateState == LOW) {
      // Sensor LOW às 6:00h, desativa as fotocélulas
      digitalWrite(photocellsPin, LOW);
    } else {
      // Sensor HIGH às 6:00h, destiva as fotocélulas e envia comando de abertura do portão
      digitalWrite(photocellsPin, LOW);
      digitalWrite(commandGatePin, HIGH);
    }
  } else {
    // Em outros horários, desativa as fotocélulas e os comandos do portão
    digitalWrite(commandGatePin, LOW);
  }
  
  // Outras ações ou código podem ser adicionados aqui
  
  delay(1000); // Aguarde 1 segundo antes de verificar novamente

}