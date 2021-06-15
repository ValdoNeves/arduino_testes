#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "********";
const char* password = "*******";
const char* mqttServer = "***********";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){

    delay(100);
    Serial.println("conectando a WiFi...");
  }

  Serial.println("Conectado!");

  //comunicacao com mqtt-dojot
  client.setServer(mqttServer, mqttPort);

  while(!client.connected()){
    Serial.println("Conectando ao Servidor Dojot...");
    if(client.connect("admin", "admin", "v@L135t1.")){
      Serial.println("Conectado ao servidor Dojot");
    }else{
      Serial.print("Falha ao conectar ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  
}

void loop() {
  

}
