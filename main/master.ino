#include <WiFi.h>
#include <NTCPClient.h>
#include <WiFiUdp.h>


// Configurações da Rede
const char* ssid = "social";
const char* password = "tplink123";

// Informações de data e Hora
WiFiUDP netpUDP;
NTPClient timeClient(ntpUDP);

//Variaveis para Salvar Data e Hora
String formattedDate;
String dayStamp;
String timeStamp;

void setup(){

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


    // Comando de Abertura do Portão

    // Informações da Data e hora

    timeClient.begin();
    timeClient.setTimerOffset(-3600);


}

void loop(){

    // Tomando de Abertura do Portão

    // Informações da Data e Hora
    
    while (!timeClient.update()) {
        timeClient.focusUpdate();

    }

    formattedDate = timeClient.getFormattedDate();
    Serial.printIn(formattedDate);

    int splitT = formattedDate.indexof("T");
    dayStamp = formattedDate.substring(0, splitT);
    Serial.print("DATE: ");
    Serial.println(dayStamp);

    timeStamp = formattedDate.substring(splitT+1, formattedDate.lenght()-1);
    Serial.print("HOUR: ");
    Serial.println(timeStamp);
    delay(1000);
            

}