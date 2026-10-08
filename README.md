# ESP32 mDNS

Exemplo mínimo de um servidor HTTP no ESP32 com descoberta via mDNS. Após conectar-se ao Wi-Fi, o dispositivo pode ser acessado em `http://esp32.local` sem precisar conhecer seu endereço IP.

Copie `src/config.example.h` para `src/config.h`, informe as credenciais da rede e grave o projeto com o PlatformIO.
