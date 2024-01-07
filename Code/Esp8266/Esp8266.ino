"""MIT License

Copyright (c) 2024 Peavepuf

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE."""


#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define RX_PIN D5  // RX pin
#define TX_PIN D6  // TX pin
#define BAUD_RATE 9600  // Serial communication

SoftwareSerial uart(RX_PIN, TX_PIN);

const char *ssid = "HERE";  // Enter your WiFi network's SSID
const char *password = "HERE";  // Enter your WiFi network's password
const char *host = "HERE";  // Thingspeak API address
const char *apiKey = "HERE";  // Enter your Thingspeak channel's API key

void setup() {
  Serial.begin(115200);  // Start serial connection
  uart.begin(BAUD_RATE); // Start software serial connection
  connectWiFi();
}

void loop() {
  static String received_data;

  while (uart.available()) {
    char c = uart.read();

    if (c == '\n') {
      Serial.println("Received data: " + received_data);
      processReceivedData(received_data);
      received_data = ""; // Reset received data
    }
    else {
      received_data += c;
    }
  }

  delay(100);
}

void connectWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");
}

void sendToThingspeak(float pressure, float altitude, float temperature, float humidity) {
  WiFiClient client;

  if (client.connect(host, 80)) {
    String postStr = "field1=" + String(pressure) + "&field2=" + String(altitude) + "&field3=" + String(temperature) + "&field4=" + String(humidity) + "&key=" + apiKey;

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(postStr.length()));
    client.println();
    client.println(postStr);
    delay(1000);
    Serial.println("Data sent to Thingspeak");
  } else {
    Serial.println("Connection to Thingspeak failed");
  }
}

void processReceivedData(String data) {
  // Get data as an array
  char dataArray[data.length() + 1];
  data.toCharArray(dataArray, sizeof(dataArray));

  // Parse the array and process based on the respective field
  char *token = strtok(dataArray, "[], ");
  
  int i = 0;
  float pressure, altitude, temperature, humidity;

  while (token != NULL) {
    if (i == 0) {
      pressure = atof(token);
    } else if (i == 1) {
      altitude = atof(token);
    } else if (i == 2) {
      temperature = atof(token);
    } else if (i == 3) {
      humidity = atof(token);
    }
    token = strtok(NULL, "[], ");
    i++;
  }

  // Send the received data to Thingspeak
  sendToThingspeak(pressure, altitude, temperature, humidity);
}
