
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include "config.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

WebServer server(80);

void handleRoot()
{
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="pt-BR">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport"
            content="width=device-width, initial-scale=1">
      <title>ESP32 - Teste</title>
      <style>
        body {
          font-family: Arial, sans-serif;
          background: #121212;
          color: white;
          display: flex;
          justify-content: center;
          align-items: center;
          min-height: 100vh;
          margin: 0;
        }
        .card {
          background: #242424;
          padding: 32px;
          border-radius: 16px;
          text-align: center;
        }
        h1 { color: #4ade80; }
      </style>
    </head>
    <body>
      <div class="card">
        <h1>ESP32 Online!</h1>
        <p>Servidor HTTP funcionando.</p>
        <p>mDNS: esp32.local</p>
        <p>IP: %IP%</p>
      </div>
    </body>
    </html>
  )rawliteral";

  html.replace("%IP%", WiFi.localIP().toString());

  server.send(200, "text/html; charset=utf-8", html);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Iniciando...");

  WiFi.mode(WIFI_STA);
  WiFi.setHostname("esp32");
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32"))
  {
    Serial.println("mDNS iniciado: esp32.local");
    MDNS.addService("http", "tcp", 80);
  }
  else
  {
    Serial.println("Falha ao iniciar mDNS");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.begin();

  Serial.println("Servidor HTTP iniciado!");
}

void loop()
{
  server.handleClient();
}
