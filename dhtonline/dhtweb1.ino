#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTPIN D2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

ESP8266WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);

void handle_index() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  // เช็คถ้าอ่านค่าไม่สำเร็จให้เริ่มอ่านใหม่
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  String res = "<meta charset='UTF-8'><h1>เซนเซอร์อุณหภูมิ ความชื้น</h1>Temp =" + String(t) ;
  res += "*C<br>ความชื้น=" + String(h);
  server.send(200, "text/html", res);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.begin("ssid", "passwd");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());

  server.on("/", handle_index);
  server.begin();
}
void loop(void) {
  server.handleClient();
}
