#include <WiFi.h>
#include <NTCPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>

// Configurações da Rede
const char* ssid = "Village 3";
const char* password = "adminv31500";

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

}

void loop(){

  // Obtém a hora atual
  int horaAtual = hour();
  
  // Obtém o estado do sensor do portão
  int estadoPortao = digitalRead(sensorPortaoPin);

    // Verifica a hora atual e o estado do sensor para tomar decisões
  if (horaAtual == 19) {
    if (estadoPortao == HIGH) {
      // Sensor HIGH às 19:00h, libera as fotocélulas
      digitalWrite(fotocelulasPin, HIGH);
    } else {
      // Sensor LOW às 19:00h, libera as fotocélulas e envia comando de fechamento do portão
      digitalWrite(fotocelulasPin, HIGH);
      digitalWrite(fechamentoPortaoPin, HIGH);
    }
  } else if (horaAtual == 6) {
    if (estadoPortao == LOW) {
      // Sensor LOW às 6:00h, libera as fotocélulas
      digitalWrite(fotocelulasPin, LOW);
    } else {
      // Sensor HIGH às 6:00h, libera as fotocélulas e envia comando de abertura do portão
      digitalWrite(fotocelulasPin, LOW);
      digitalWrite(aberturaPortaoPin, HIGH);
    }
  } else {
    // Em outros horários, desativa as fotocélulas e os comandos do portão

  }
  
  // Outras ações ou código podem ser adicionados aqui
  
  delay(1000); // Aguarde 1 segundo antes de verificar novamente

}