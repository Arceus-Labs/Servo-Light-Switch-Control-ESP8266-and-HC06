# Servo Light Switch Control (ESP8266 + HC-06)

Bluetooth-controlled servo system for automating physical light switches using ESP8266 and HC-06 Bluetooth module.

## 🔧 Components Used
- ESP8266 (NodeMCU)
- HC-06 Bluetooth Module
- 2x Servo Motors (SG90 or similar)
- Power supply for servos
- Breadboard & jumper wires

## 🔌 Pin Connections

### Servos
| Servo | ESP8266 Pin |
|-------|-------------|
| Servo 1 | D5 (GPIO14) |
| Servo 2 | D6 (GPIO12) |

### HC-06 Bluetooth
| HC-06 Pin | ESP8266 Pin |
|-----------|-------------|
| TX | RX |
| RX | TX |
| VCC | 3.3V |
| GND | GND |

## 📱 Bluetooth Commands

### Servo 1 (Switch W)
- `ONW` - Turn switch ON
- `OFFW` - Turn switch OFF

### Servo 2 (Switch O)
- `ONO` - Turn switch ON
- `OFFO` - Turn switch OFF

## ⚡ Features
- Wi-Fi disabled for power saving
- Servos detach after operation to reduce power consumption
- Smooth center-position return after each operation
- Serial feedback for debugging

## 🧠 Working Principle
1. ESP8266 receives Bluetooth commands via HC-06
2. Servo attaches, moves to center position
3. Servo rotates to ON/OFF position (0° or 170°)
4. Returns to center (90°)
5. Servo detaches to save power

## 👨‍💻 Author
Built for home automation using ESP8266 and basic servo control.
