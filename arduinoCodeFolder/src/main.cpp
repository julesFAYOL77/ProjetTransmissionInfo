#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "Freebox-16D4DD";
const char* password = "inperabit&-vicinalem-flabrali6-disruperit";

const char* host = "louetonfilm.com";
const int httpsPort = 443; // Port 443 for HTTPS

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure(); // Bypass SSL certificate verification

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    return;
  }

  // Compose a GET request with an example action 'testAction'
  String url = "/api.php?action=testAction";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // Wait for the response and read it
    while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break; // Les en-têtes sont terminés, le corps commence
    }
  }

  // Lisez le corps de la réponse qui est au format JSON
  String response = client.readString();
  Serial.println("Received response:");
  Serial.println(response);

}

void loop() {
  // No need to repeat the action in the loop.
}

