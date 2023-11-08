  #include <SoftwareSerial.h>
  #include <ArduinoJson.h>

  SoftwareSerial nodemcu(D6, D5);  // Using D6 as Rx and D5 as Tx

  unsigned long previousMillis = 0;
  unsigned long currentMillis;
  const unsigned long period = 2500;  // Timer to run Arduino code every 10 seconds

  void setup() {
    Serial.begin(9600);
    nodemcu.begin(9600);
    while (!Serial) continue;
  }

  void loop() {
    currentMillis = millis();

    if (currentMillis - previousMillis >= period) {
      StaticJsonDocument<200> doc;

      while (nodemcu.available()) {
        char c = nodemcu.read();
        Serial.print(c); // Print each character received from nodemcu
      }

      DeserializationError error = deserializeJson(doc, nodemcu);

      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      } else {
        float averageSpeed = doc["average_speed"];
        float averageDistance = doc["average_distance"];

        Serial.println("JSON Object Received");
        Serial.print("Received Average Speed:  ");
        Serial.println(averageSpeed);
        Serial.print("Received Average Distance:  ");
        Serial.println(averageDistance);
        Serial.println("-----------------------------------------");
      }

      previousMillis = currentMillis;
    }
  }
