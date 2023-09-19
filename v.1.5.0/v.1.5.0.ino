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

bool dayTime () {
  int currentHour = timeClient.getHours();

  int dayStartTime = 6;
  int dayEndTime = 19;

  if (currentHour >= dayStartTime && currentHour < dayEndTime) {
    return true;
  } else {
    return false;
  }
}


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
    timeClient.setTimeOffset(-3 * 3600);


    pinMode (LED, OUTPUT);
    pinMode (sensor, OUTPUT);
    pinMode (command, OUTPUT);
}
void loop() {

    timeClient.update();
    Serial.println(dayTime());

    if (dayTime()) {
      digitalWrite(LED, LOW);
      digitalWrite(sensor, LOW);
    } else {
      digitalWrite(LED, HIGH);
      digitalWrite(sensor, HIGH);
    }
    
  delay(100);
}
