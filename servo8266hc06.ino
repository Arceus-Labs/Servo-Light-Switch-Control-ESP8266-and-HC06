#include <Servo.h>

Servo s;

int center = 90;
int onPos  = 175;
int offPos = 0;

void setup() {
  Serial.begin(9600);
  s.attach(14);
  s.write(center);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();
    cmd.trim();
    cmd.toUpperCase();

    if (cmd == "OFF") {
      s.write(onPos);
      delay(400);
      s.write(center);
      Serial.println("OFF done");
    }

    if (cmd == "ON") {
      s.write(offPos);
      delay(400);
      s.write(center);
      Serial.println("ON done");
    }
  }
}
