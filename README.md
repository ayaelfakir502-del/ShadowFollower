# ShadowFollower 

## Overview
ShadowFollower is an autonomous mobile robot designed to follow a black line path while intelligently avoiding obstacles. The project is developed using the **C programming language** on the Arduino framework.

## Key Features
* **Line Following**: Uses dual IR sensors to track black paths with precision.
* **Obstacle Avoidance**: Equipped with an ultrasonic sensor to detect objects within a 20cm range.
* **Interactive Mode**: The robot communicates via the Serial Monitor, asking the user whether to wait or bypass an obstacle.
* **Safety System**: Includes a buzzer alert system for collision warnings.

## Components Used
* Arduino Uno SMD
* L293D Motor Driver
* HC-SR04 Ultrasonic Sensor
* TCRT5000 IR Sensors
* 2WD Robot Chassis

## How to Run
1. Upload the `ShadowFollower_V1.ino` file to your Arduino.
2. Open the Serial Monitor (9600 baud) to interact with the robot.
3. Place the robot on a black line and watch it go!
