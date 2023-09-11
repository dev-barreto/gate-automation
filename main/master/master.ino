#include <WiFi.h>
#include <NTCPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>

// Configurações da Rede
const char* ssid = "social";
const char* password = "tplink123";

// Informações de data e Hora
RTC_DS3231 rtc;

const int sensorPortaoPin = 2; // Pino onde o sensor do portão está conectado
const int fotocelulasPin = 3;  // Pino onde as fotocélulas estão conectadas
const int aberturaPortaoPin = 4; // Pino para o comando de abertura do portão
const int fechamentoPortaoPin = 5; // Pino para o comando de fechamento do portão

void setup(){

  pinMode(sensorPortaoPin, INPUT); // Pino em modo de entrada de informações
  pinMode(fotocelulasPin, OUTPUT); // Pino em modo de saida de informações
  pinMode(aberturaPortaoPin, OUTPUT); // Pino em modo de saida de informações
  pinMode(fechamentoPortaoPin, OUTPUT); // Pino em modo de saida de informações

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

  // Informações da Data e hora

  rtc.begin();

  rtc.adjust(DateTime(2023, 9, 11, 14, 6, 0));

}

void loop(){

  // Informações da Data e Hora
  DateTime now = rtc.now();
  // Verifica se é o horário programado para iniciar o fechamento do portão 
  int year = now.year();
  int month = now.month();
  int day = now.day();
  int hour = now.hour();
  int minute = now.minute();
  int seconds = now.seconds();

  if (now.time() == 19 && 6) {
    digitalWrite(comPin, HIGH);
  }
  else{
    digitalWrite(comPin, LOW);
  }

  // Verifica estatus do Sensor do Portão

  // Comando de Abertura do Portão
           

}