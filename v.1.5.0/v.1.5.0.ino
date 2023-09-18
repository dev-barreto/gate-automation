#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>

#define LED 2
#define command 4
#define sensor 19

const char* ssid = "SSID_NETWORK";
const char* password = "PASS_NETWORK";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi.");
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);

    timeClient.begin();
    timeClient.setTimeOffset(-3 * 3600); // Ajuste o fuso horário para o Brasil (GMT-3)

    pinMode (LED, OUTPUT);
    pinMode (sensor, OUTPUT);
    pinMode (command, OUTPUT);

}

void loop() {
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());

    // Verifique os horários e execute funções conforme necessário
    if (timeClient.getHours() == 19 && timeClient.getMinutes() == 00 && timeClient.getSeconds() == 00) {
        // Execute uma função no horário determinado
            digitalWrite(LED, HIGH);
            digitalWrite(sensor, HIGH);
//            digitalWrite(command, HIGH)
//            delay(1000);
//            digitalWrite(command, LOW)
    } else {
      // Excute algo fora do horário não necessário
    }

    if (timeClient.getHours() == 06 && timeClient.getMinutes() == 00 && timeClient.getSeconds() == 00) {
      // Executa a função no horário determinado

      digitalWrite(LED, LOW);
      digitalWrite(sensor, LOW);
    }


    // Outros horários e funções podem ser adicionados aqui

    delay(100); // Aguarde um minuto antes de verificar novamente
}
