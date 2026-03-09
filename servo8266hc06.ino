#include <ESP8266WiFi.h>
#include <Servo.h>

Servo s1;
Servo s2;

int center = 90;
int onPos  = 180;
int offPos = 0;

bool btConnected = false;   // track HC06 activity

void centerServos() {
  s1.attach(14);
  s2.attach(12);

  s1.write(center);
  s2.write(center);

  delay(400);

  s1.detach();
  s2.detach();
}

void setup() {

  // 🔋 WiFi OFF
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  Serial.begin(9600);

  s1.attach(14);
  s2.attach(12);

  s1.write(center);
  s2.write(center);

  delay(300);

  s1.detach();
  s2.detach();
}

void loop() {

  if (Serial.available()) {

    // Detect first activity from HC06
    if (!btConnected) {
      centerServos();           // auto reset position
      btConnected = true;
      Serial.println("Bluetooth Connected - Servos Centered");
    }

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

      s1.detach();
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

  // If Bluetooth inactive for long time reset flag
  if (!Serial.available()) {
    delay(5000);
    btConnected = false;
  }
}
