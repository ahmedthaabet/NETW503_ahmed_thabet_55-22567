#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "Wael AP"
#define STAPSK "W@elW@el"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.10";
const uint16_t port = 4497;

ESP8266WiFiMulti WiFiMulti;

const int ldrPin = A0;
int light_sensor = A0;

WiFiClient client;

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

void connectToServer() {
  // Read the LDR sensor value
  int ldrValue = analogRead(ldrPin);

  // Connect to the server
//  WiFiClient client;
  if (client.connect(host, port)) {
    Serial.println("Connected to server");
  } else {
    // If the connection failed, print an error message
    Serial.print("Connection to server failed. ");
    Serial.println(client.status());
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();

  // Send initial sensor data to the server
  connectToServer();
}

void loop() {
  // Your main loop code goes here
  int raw_light = analogRead(light_sensor);
  int light = map(raw_light, 0, 1023, 0, 100);

  Serial.print("Light level: ");
  Serial.println(light);
  client.print("Light level 2: ");
  client.print(light);
  // Wait for some time before sending the next update
  delay(3000);

}