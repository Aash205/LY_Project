Wireless Surveillance Rover Using DTMF Technology

A low-cost wireless surveillance rover that can be controlled remotely using mobile phone DTMF signals, featuring live video streaming and autonomous obstacle avoidance capabilities.

![Image](https://github.com/user-attachments/assets/3bf0413f-dae6-4185-8a97-181ea0f949c5)

🎯 Project Overview

This project presents a DTMF-controlled wireless surveillance rover designed for remote monitoring applications in areas where traditional surveillance systems are not feasible. The rover combines DTMF technology with modern wireless communication to provide reliable remote surveillance capabilities.

Key Applications
- Military surveillance operations
- Mining industry monitoring
- Natural disaster recovery operations
- Security and research applications
- Remote area exploration where human access is limited

Features

- Remote Control: Control via mobile phone using DTMF (Dual Tone Multi Frequency) technology
- Live Video Streaming: Real-time visual monitoring through Raspberry Pi camera
- Obstacle Avoidance: Autonomous navigation using ultrasonic sensors
- Long Range Communication: LoRa wireless module for extended range (up to 15km in optimal conditions)
- Speed Control: Variable speed control with 4 different speed levels
- Real-time Video: 5MP Raspberry Pi camera with recording capabilities
- Global Access: Remote.it integration for worldwide access to video feed

Hardware Components

Main Controllers
Raspberry Pi: Main processing unit for video streaming
Arduino Nano: Motor control and sensor management

Communication Modules
- DTMF Decoder: For phone-based remote control
- LoRa Transceiver: Long-range wireless communication
- 5MP Raspberry Pi Camera: Video capture and streaming

Sensors & Actuators
- Ultrasonic Sensors (2x): Obstacle detection with 90° angular coverage
- Motor Driver: Four-wheel drive system
- 12.5V Battery System: Power supply

 Technical Specifications

Control Commands (DTMF)
| Digit | Binary Value | Action |
|-------|--------------|--------|
| 2 | 01001 | Forward |
| 4 | 00101 | Left |
| 6 | 01101 | Right |
| 8 | 00011 | Backward |
| 5 | 10101 | Stop |


Getting Started

 Prerequisites
```bash
# Raspberry Pi Libraries
sudo apt update
sudo apt install python3-pip
pip3 install picamera
pip3 install remote.it

# Arduino Libraries
- DTMF Decoder Library
- LoRa Library
- Ultrasonic Sensor Library
```

 Hardware Setup
1. Connect Arduino Nano to motor drivers and sensors
2. Wire DTMF decoder to Arduino analog pins
3. Connect LoRa modules for wireless communication
4. Mount Raspberry Pi camera on the rover
5. Set up dual ultrasonic sensors at outward angles

 Software Installation
1. Flash the Arduino code for motor control and sensor management
2. Configure Raspberry Pi for video streaming
3. Set up Remote.it for global access
4. Configure LoRa communication parameters
