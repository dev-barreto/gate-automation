#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

const char* ssid = "WiFi_SSID";
const char* password = "WiFi_PASSWORD";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Montar o sistema de arquivos
  if (!SPIFFS.begin(true)) {
    Serial.println("Error on building system files SPIFFS.");
    return;
  }

  // Defina a rota raiz ("/") para servir um arquivo HTML do sistema de arquivos
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    File file = SPIFFS.open("/index.html", "r");
    if (file) {
      request->send(SPIFFS, "/index.html", "text/html");
      file.close();
    } else {
      request->send(404, "text/plain", "File not found");
    }
  });

  server.begin();
}

void loop() {
  
  // Coloque sua lógica aqui, se necessário

}
