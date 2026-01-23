#include <ESP8266WiFi.h>
#include <Servo.h>

Servo s1;   // first servo
Servo s2;   // second servo

int center = 90;
int onPos  = 170;
int offPos = 0;

void setup() {
  // 🔋 Wi-Fi OFF (power saving)
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  Serial.begin(9600);

  s1.attach(14);   // D5
  s2.attach(12);   // D6

  s1.write(center);
  s2.write(center);

  delay(300);

  // 🔌 detach both after initial centering
  s1.detach();
  s2.detach();
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();
    cmd.trim();
    cmd.toUpperCase();

    // -------- Servo 1 --------
    if (cmd == "ONW") {
      s1.attach(14);
      s1.write(center);
      delay(200);

      s1.write(offPos);
      delay(400);
      s1.write(center);
      delay(200);

      s1.detach();   // 🔋 power saved
      Serial.println("ONW done");
    }

    if (cmd == "OFFW") {
      s1.attach(14);
      s1.write(center);
      delay(200);

      s1.write(onPos);
      delay(400);
      s1.write(center);
      delay(200);

      s1.detach();
      Serial.println("OFFW done");
    }

    // -------- Servo 2 --------
    if (cmd == "ONO") {
      s2.attach(12);
      s2.write(center);
      delay(200);

      s2.write(offPos);
      delay(400);
      s2.write(center);
      delay(200);

      s2.detach();
      Serial.println("ONO done");
    }

    if (cmd == "OFFO") {
      s2.attach(12);
      s2.write(center);
      delay(200);

      s2.write(onPos);
      delay(400);
      s2.write(center);
      delay(200);

      s2.detach();
      Serial.println("OFFO done");
    }
  }
}
