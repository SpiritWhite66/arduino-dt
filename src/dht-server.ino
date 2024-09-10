#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTPIN D7 // Le pin de connection
#define DHTTYPE DHT22  // DHT22 ou DHT 11

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200); //Baudrate
  dht.begin();
  Serial.println("ESP starts");

  WiFi.begin("xxx","xxx");

  Serial.print("Connecting...");

  while(WiFi.status()!=WL_CONNECTED){ 
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected! IP-Address: ");
  Serial.println(WiFi.localIP()); //Displaying the IP Address

  server.onNotFound([](){
    server.send(404, "text/plain", "Link was not found!");  
  });
 
  server.on("/", []() {
    server.send(200, "text/plain", "Landing page!");
  });
 
  server.on("/all", []() {
    allData();
  });
  server.begin();
}

void loop() {
  server.handleClient();

}

void allData() {
  char buffer[800];
  sprintf(buffer, "{\"temperature\" : %f , \"humidity\": %f }", dht.readTemperature(), dht.readHumidity());
  server.send(200, "application/json", buffer);
}
