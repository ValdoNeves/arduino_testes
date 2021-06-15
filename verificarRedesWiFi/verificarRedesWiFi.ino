#include <ESP8266WiFi.h>;


// ESP8266 wifi;

String redeSSID = "";

int intensidadeSinal = -9999;

void setup() {
  
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  WiFi.disconnect();
  
}

void loop() {
  
  int n = WiFi.scanNetworks();
  Serial.println("Escaneamento realizado");

  if(n == 0){
    Serial.println("Nenhuma rede encontrada");
  }else{
    redeSSID = "";
    intensidadeSinal = -9999;
    Serial.print(n);
    Serial.println(" Redes encontradas\n");
    for(int i = 0; i < n; i++){
      Serial.print(WiFi.SSID(i));
      Serial.print(": ");
      Serial.println(WiFi.RSSI(i));
      Serial.println("");

      if(abs(WiFi.RSSI(i)) < abs(intensidadeSinal)){
        intensidadeSinal = WiFi.RSSI(i);
        redeSSID = WiFi.SSID(i);
        Serial.print("Rede com Melhor Sinal Encontrada: ");
        Serial.print(redeSSID);
        Serial.print(" - Sinal: ");
        Serial.println(intensidadeSinal);
        Serial.println("");
      }
    }
  }
  delay(5000);
}
