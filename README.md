# Servo Light Switch Control (ESP8266 + HC-06)

Control physical wall light switches remotely using servo motors. The ESP8266 receives commands via HC-06 Bluetooth module and moves servos to flip switches.

## Components

* ESP8266 (NodeMCU)
* HC-06 Bluetooth module
* 2× Servo motors (SG90 / MG90S)
* External 5V supply for servos
* Breadboard and jumper wires

## Pin Connections

### Servos

| Servo   | ESP8266 Pin | GPIO   |
| ------- | ----------- | ------ |
| Servo 1 | D5          | GPIO14 |
| Servo 2 | D6          | GPIO12 |

### HC-06

| HC-06 Pin | ESP8266 Pin |
| --------- | ----------- |
| TX        | RX          |
| RX        | TX          |
| VCC       | 3.3V        |
| GND       | GND         |

## Bluetooth Commands

### Servo 1 (Switch W)

* `ONW` → Turn switch ON
* `OFFW` → Turn switch OFF

### Servo 2 (Switch O)

* `ONO` → Turn switch ON
* `OFFO` → Turn switch OFF

## Features

* Wi-Fi disabled for lower power usage
* Servos detach after movement to save power
* Auto-centering when Bluetooth connects (resets servo alignment)
* Servo always returns to center (90°) after switching

## How it works

1. ESP8266 waits for commands from the HC-06 Bluetooth module.
2. When Bluetooth activity is detected, both servos move to center position (90°).
3. On receiving a command (`ONW`, `OFFW`, `ONO`, `OFFO`), the corresponding servo attaches.
4. Servo moves to toggle the switch, returns to center, then detaches.
