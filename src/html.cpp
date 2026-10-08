#include "html.h"

#include <Arduino.h>
#include <WiFi.h>

void handleRoot(WebServer &server, const char *mdnsHostname)
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
        <p>mDNS: %MDNS%</p>
        <p>IP: %IP%</p>
      </div>
    </body>
    </html>
  )rawliteral";

  html.replace("%IP%", WiFi.localIP().toString());
  html.replace("%MDNS%", mdnsHostname);

  server.send(200, "text/html; charset=utf-8", html);
}
