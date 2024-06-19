#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "JioFiber-NuN5N";           // Your 2.4GHz Wi-Fi SSID (network name)
const char* password = "adi123adi"; // Your Wi-Fi password

void setup() {
  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);
  delay(10);

  // Print initial message
  Serial.println();
  Serial.println("Scanning for available networks...");

  // Scan for available networks
  int n = WiFi.scanNetworks();
  Serial.println("Scan done.");
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.print(n);
    Serial.println(" networks found:");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }

  // Print initial message
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  // Wait for connection
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retries++;
    if (retries > 60) { // 60*500ms = 30 seconds timeout
      Serial.println();
      Serial.println("Failed to connect to WiFi.");
      Serial.print("Current status: ");
      Serial.println(WiFi.status());
      return;
    }
  }

  // Print local IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("NodeMCU Local IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing to do here
}