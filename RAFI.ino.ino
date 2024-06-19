#include <WiFi.h>
#include "DHT.h"
#include <HTTPClient.h>
#define DHT11PIN 4

WiFiClient wifi;
DHT dht(DHT11PIN, DHT11); 



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  

  dht.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin("070323", "Anya8kali");

  while(WiFi.status()!=WL_CONNECTED){
    delay(300);
    Serial.print(".");
  }
  Serial.println("Wifi is Connected!");
}

void loop() {

  // Set URL server web
  HTTPClient http;
  http.begin("http://192.168.84.207:5000/sensor/wibu");
  http.addHeader("Content-Type", "application/json");

  float hum = dht.readHumidity();
  String humStr = String(hum, 2);

  float temp = dht.readTemperature();
  String tempStr = String(temp, 2);

  String timestampStr = String(millis());

  String data = "{"
                "  \"humidity\": " + humStr + ","
                "  \"temperature\": " + tempStr + ","
                "  \"timestamp\": " + timestampStr +
                "}";

  // Send POST request
  int httpCode = http.POST(data);

  Serial.println(data);
  if (httpCode > 0) { // Check for the returning code
    if (httpCode == HTTP_CODE_OK) {
      Serial.println("Data berhasil dikirim");
    } else {
      Serial.println("Unexpected HTTP code: " + String(httpCode));
    }
  } else {
    // Print detailed error message
    Serial.println("Error on sending POST: " + String(http.errorToString(httpCode).c_str()));
  }
  // Tutup objek HTTPClient
  http.end();
  delay(7000);
}
