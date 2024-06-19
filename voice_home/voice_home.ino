#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

const char* ssid = "JioFiber-NuN5N";
const char* password = "adi123adi";
String command = ""; // Command received from Android device

// Set LED Pins
int led1 = 5;  // GPIO5 (D1)
int led2 = 4;  // GPIO4 (D2)

void setup()
{
  Serial.begin(115200);

  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);  

  digitalWrite(led1, LOW); // Turn off initially (assuming active high LED)
  digitalWrite(led2, LOW); // Turn off initially (assuming active high LED)

  connectWiFi();
  server.begin();
}

void loop()
{
    client = server.available();
    if (!client) return; 
    command = checkClient();
    command.replace("%20", " ");
    Serial.println("Received command: " + command);

    // Expanded command recognition to handle more voice command variations
    if (command == "r1on" || command == "turn on relay 1" || command == "relay 1 on" || command == "relay one on") {
        digitalWrite(led1, HIGH); // Turn on LED1
        Serial.println("LED1 turned ON");
    } else if (command == "r1off" || command == "turn off relay 1" || command == "relay 1 off" || command == "relay one off"|| command == "relay one of") {
        digitalWrite(led1, LOW); // Turn off LED1
        Serial.println("LED1 turned OFF");
    } else if (command == "r2on" || command == "turn on relay 2" || command == "relay 2 on" || command == "relay two on") {
        digitalWrite(led2, HIGH); // Turn on LED2
        Serial.println("LED2 turned ON");
    } else if (command == "r2off" || command == "turn off relay 2" || command == "relay 2 off" || command == "relay two off") {
        digitalWrite(led2, LOW); // Turn off LED2
        Serial.println("LED2 turned OFF");
    } else {
        Serial.println("Unknown command");
    }

    sendBackEcho(command); // Send command echo back to Android device
    command = "";
}

/* connecting WiFi */
void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((WiFi.status() != WL_CONNECTED))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is: ");
  Serial.print(WiFi.localIP());
}

/* check command received from Android Device */
String checkClient(void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);  // Remove "GET /"
  request.remove(request.length() - 9, 9); // Remove " HTTP/1.1"
  return request;
}

/* send command echo back to android device */
void sendBackEcho(String echo)
{
  client.println("HTTP/1.1 200 OK ");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(echo);
  client.println("</html>");
  client.stop();
  delay(1);
}
