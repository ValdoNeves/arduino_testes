#include <ESP8266WiFi.h>

const char* ssid = "********";
const char* password = "********";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  //preparando GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);

  Serial.println();
  Serial.println();
  Serial.println("Conectando com ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");

  server.begin();
  Serial.print("Servidor iniciado em");

  Serial.println(WiFi.localIP());

}

void loop() {

  WiFiClient client = server.available();
  if(!client){
    return;
  }

  Serial.println("Cliente encontrado ");
  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  int val;
  if(req.indexOf("/gpio/0") != -1){
    val = 0;
  }
  else if(req.indexOf("/gpio/1") != -1){
    val = 1;
  }
  else{
    Serial.println("Requisicao invalida");
    client.stop();
    return;
  }

  digitalWrite(2, val);
  client.flush();

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO na placa nodeMCU8266 no momento esta ";
  s += (val)?"ligada":"desligada";
  s += "</html>\n";

  client.print(s);
  delay(1);
  Serial.println("Cliente desconectado");




}
