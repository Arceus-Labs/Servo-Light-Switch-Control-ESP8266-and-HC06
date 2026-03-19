#include <ESP8266WiFi.h>
#include <Servo.h>

Servo servoW;
Servo servoO;

const int SERVO_W_PIN = 14;  // D5
const int SERVO_O_PIN = 12;  // D6

// Servo W angles
const int CENTER_W = 90;
const int ON_W = 0;
const int OFF_W = 180;

// Servo O angles
const int CENTER_O = 90;
const int ON_O = 0;
const int OFF_O = 180;

// Press extra offset for full switch press
const int PRESS_EXTRA = 7;

// Movement delays (ms)
const int MOVE_DELAY = 80;
const int PRESS_DELAY = 100;

// State tracking
bool isWOn = false;
bool isOOn = false;


void centerBoth() {
  servoW.write(CENTER_W);
  servoO.write(CENTER_O);
  delay(MOVE_DELAY);
}


void pressAndReturn(Servo &servo, int target, int center, int extra) {
  // Move beyond target with extra pressure
  servo.write(target + (target > center ? extra : -extra));
  delay(PRESS_DELAY);
  
  // Return to exact target
  servo.write(target);
  delay(MOVE_DELAY);
  
  // Return to center
  servo.write(center);
  delay(MOVE_DELAY);
}


void setup() {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  Serial.begin(9600);
  Serial.setTimeout(50);

  // Attach servos once
  servoW.attach(SERVO_W_PIN);
  servoO.attach(SERVO_O_PIN);

  centerBoth();
}


void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();
    cmd.trim();
    cmd.toUpperCase();

    // Always center first
    centerBoth();

    if (cmd == "W:ON") {
      pressAndReturn(servoW, ON_W, CENTER_W, PRESS_EXTRA);
      isWOn = true;
      Serial.println("W ON done");
    }
    else if (cmd == "W:OFF") {
      pressAndReturn(servoW, OFF_W, CENTER_W, PRESS_EXTRA);
      isWOn = false;
      Serial.println("W OFF done");
    }
    else if (cmd == "O:ON") {
      pressAndReturn(servoO, ON_O, CENTER_O, PRESS_EXTRA);
      isOOn = true;
      Serial.println("O ON done");
    }
    else if (cmd == "O:OFF") {
      pressAndReturn(servoO, OFF_O, CENTER_O, PRESS_EXTRA);
      isOOn = false;
      Serial.println("O OFF done");
    }
    else if (cmd == "ALLON") {
      pressAndReturn(servoW, ON_W, CENTER_W, PRESS_EXTRA);
      pressAndReturn(servoO, ON_O, CENTER_O, PRESS_EXTRA);
      isWOn = true;
      isOOn = true;
      Serial.println("ALL ON done");
    }
    else if (cmd == "ALLOFF") {
      pressAndReturn(servoW, OFF_W, CENTER_W, PRESS_EXTRA);
      pressAndReturn(servoO, OFF_O, CENTER_O, PRESS_EXTRA);
      isWOn = false;
      isOOn = false;
      Serial.println("ALL OFF done");
    }
  }
}
