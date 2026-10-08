
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include "config.h"
#include "html.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

WebServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println("Iniciando...");

  WiFi.mode(WIFI_STA);
  WiFi.setHostname(MDNS_HOSTNAME);
  WiFi.begin(ssid, password);
  WiFi.config(STATIC_IP, GATEWAY_IP, SUBNET_MASK);

  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(MDNS_HOSTNAME))
  {
    Serial.println("mDNS iniciado: " + String(MDNS_HOSTNAME) + ".local");
    MDNS.addService("http", "tcp", 80);
  }
  else
  {
    Serial.println("Falha ao iniciar mDNS");
  }

  server.on("/", HTTP_GET, []()
            { handleRoot(server, MDNS_HOSTNAME); });
  server.begin();

  Serial.println("Servidor HTTP iniciado!");
}

void loop()
{
  server.handleClient();
}
