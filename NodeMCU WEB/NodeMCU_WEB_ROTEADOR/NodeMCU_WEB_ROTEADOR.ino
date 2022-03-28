//Enviar e Receber dados - via Wifi - Ponto de acesso

#include <ESP8266WiFi.h>


const char* ssid = "Projeto_Semaforo";
const char* password = "12345678";
WiFiServer server(80);

void setup() {
  //Configuracao
  Serial.begin(9600); 
  
  IPAddress staticIP(192, 168, 4, 2); // IP estatico
  IPAddress gateway(192, 168, 4, 1);  // gateway estatico IP
  IPAddress subnet(255, 255, 255, 0); // Ocultar sub rede

  WiFi.mode(WIFI_AP);// Modo de trabalho via Access Point 

  WiFi.softAP(ssid, password, 2, 0);
  WiFi.config(staticIP, gateway, subnet);

  server.begin(); //Incializacao do servidor

  Serial.println("Server started"); 
  Serial.println(WiFi.softAPIP());
}
//Criando rotina 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Enquanto nao enviar o comando
  while (!client.available()) {
    delay(1);
  }
  //Lendo o comando
  String req = client.readStringUntil('\r');
  req = req.substring(req.indexOf("/") + 1, req.indexOf("HTTP") - 1);
  Serial.println(req);
  client.flush();

  // Executando a tarefa pretendida - abaixo um exemplo -  

  if (req.indexOf("D") != -1)
  {
    client.print("REcebido seu dado D   ");
  }
  else if (req.indexOf("R") != -1)
  {
    client.print("REcebido seu dado R   ");
  }  
  else {
    client.print("Invalid Request");
    client.flush();
    client.stop();
    return;
  }

  client.print("HTTP/1.1 200 OK\n\n");
  client.flush();

}