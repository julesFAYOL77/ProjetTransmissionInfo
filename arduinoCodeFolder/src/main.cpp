#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>

const char* ssid = "DESKTOP-AD099U7 9292";
const char* password = "12345678";

const char* host = "louetonfilm.com";
const int httpsPort = 443; // Port 443 pour HTTPS

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  // Configurer la mise à jour de l'heure via NTP
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  // Attendre que l'heure soit mise à jour
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nTime updated");

  // Désactiver la vérification du certificat SSL (non recommandé pour la production)
  client.setInsecure();
}

void loop() {
  // Récupérer l'heure actuelle
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);

  // Convertir l'heure en une chaîne de caractères
  char timeString[16];
  strftime(timeString, sizeof(timeString), "%H:%M:%S", p_tm);
  
  // Créer une requête HTTP avec l'heure
  if (client.connect(host, httpsPort)) {
    String url = String("/api.php?time=") + timeString;
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");

    // Attendre que le serveur réponde
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break; // Fin des en-têtes HTTP
      }
    }

    // Lire le corps de la réponse
    while (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }

    client.stop(); // Fermer la connexion
  } else {
    Serial.println("Connection failed");
  }

  // Attendre une minute avant d'envoyer la prochaine requête
  delay(60000);
}
