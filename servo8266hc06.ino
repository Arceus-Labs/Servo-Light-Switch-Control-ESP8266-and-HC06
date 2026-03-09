#include <ESP8266WiFi.h>
#include <Servo.h>

Servo s1;
Servo s2;

const int servo1Pin = 14;   // D5
const int servo2Pin = 12;   // D6

int center = 90;
int onPos  = 180;
int offPos = 0;

bool btActive = false;


// -------- Function to center both servos --------
void centerServos() {

  s1.attach(servo1Pin);
  s2.attach(servo2Pin);

  s1.write(center);
  s2.write(center);

  delay(250);

  s1.detach();
  s2.detach();
}


// -------- Function to toggle a servo --------
void toggleServo(Servo &servo, int pin, int targetPos) {

  servo.attach(pin);

  servo.write(center);
  delay(80);

  servo.write(targetPos);
  delay(200);

  servo.write(center);
  delay(80);

  servo.detach();
}


// -------- Setup --------
void setup() {

  WiFi.mode(WIFI_OFF);          // disable WiFi
  WiFi.forceSleepBegin();
  delay(1);

  Serial.begin(9600);
  Serial.setTimeout(50);        // prevent 1s blocking delay

  centerServos();               // initial alignment
}


// -------- Main Loop --------
void loop() {

  if (Serial.available()) {

    if (!btActive) {
      centerServos();           // auto reset when bluetooth starts
      btActive = true;
      Serial.println("BT Connected - Servos Centered");
    }

    String cmd = Serial.readString();
    cmd.trim();
    cmd.toUpperCase();


    if (cmd == "ONW") {
      toggleServo(s1, servo1Pin, offPos);
      Serial.println("ONW done");
    }

    else if (cmd == "OFFW") {
      toggleServo(s1, servo1Pin, onPos);
      Serial.println("OFFW done");
    }

    else if (cmd == "ONO") {
      toggleServo(s2, servo2Pin, offPos);
      Serial.println("ONO done");
    }

    else if (cmd == "OFFO") {
      toggleServo(s2, servo2Pin, onPos);
      Serial.println("OFFO done");
    }
  }

  else {
    delay(3000);
    btActive = false;           // reset bluetooth state
  }
}
