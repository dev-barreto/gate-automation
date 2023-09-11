#include <WiFi.h>

const char* ssid = "social";
const char* password = "tplink123";

void setup(){

    // WiFi Connection
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

    //Command Open Gate

    

}

void loop(){

    // Command Open Gete


}