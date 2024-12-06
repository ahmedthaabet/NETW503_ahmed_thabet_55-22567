#include <ThingsBoard.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Seeed_mbedtls.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "Wael AP"
#define STAPSK "W@elW@el"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* tbToken = "lUdeTzSeWHJmzNouhkhg";
const char* tbServer = "thingsboard.cloud";

ESP8266WiFiMulti WiFiMulti;

const int ldrPin = A0;
int light_sensor = A0;

WiFiClient client;
ThingsBoard tb(client);

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// void connectToServer() {
//   // Read the LDR sensor value
//   int ldrValue = analogRead(ldrPin);

//   // Connect to the server
//   if (client.connect(host, port)) {
//     Serial.println("Connected to server");
//   } else {
//     // If the connection failed, print an error message
//     Serial.print("Connection to server failed. ");
//     Serial.println(client.status());
//   }
// }

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  if (!tb.connected()) {
    Serial.println("Connecting to ThingsBoard...");
    if (tb.connect(tbServer, tbToken)) {
      Serial.println("Connected!");
    } else {
      Serial.println("Failed to connect. Retry in 5 seconds...");
      delay(5000);
      return;
    }
  }
  int raw_light = analogRead(light_sensor);
  int light = map(raw_light, 0, 1023, 0, 100);

  Serial.print("Light level 2: ");
  Serial.println(light);
  tb.sendTelemetryInt("Light 2", light);
  delay(30000);


}