/* * Project Name: ShadowFollower
 * Language: C (Arduino Framework)
 */

#include <avr/io.h> 

// --- Sensor Pins Definitions ---
#define IR_LEFT A0      
#define IR_RIGHT A1     
#define TRIG 13         
#define ECHO 12         
#define BUZZER 7        

// --- Motor Pins Definitions ---
#define ENA 5           
#define IN1 4           
#define IN2 6           
#define ENB 11          
#define IN3 9           
#define IN4 10          

int blackLineValue = 500; 

// Function Prototypes
long getDistance(void);
void followLineLogic(void);
void smartEscape(void);
void moveForward(void);
void stopMotors(void);
void turnLeft(void);
void turnRight(void);

void setup() {
    pinMode(IR_LEFT, INPUT); 
    pinMode(IR_RIGHT, INPUT);
    pinMode(TRIG, OUTPUT); 
    pinMode(ECHO, INPUT); 
    pinMode(BUZZER, OUTPUT);
    
    pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

    Serial.begin(9600); 
    
    Serial.println("--- ShadowFollower System [C-Version] ---");
    delay(4000); 
    
    blackLineValue = analogRead(IR_LEFT) + 150; 
    Serial.println("ShadowFollower: Ready, Master!");
}

void loop() {
    long distance = getDistance(); 

    if (distance > 0 && distance < 20) { 
        stopMotors();
        tone(BUZZER, 1000); 
        
        Serial.println("\n[!] ShadowFollower: Obstacle detected!");
        Serial.println("Wait (y) or Bypass (n)?");

        while (Serial.available() == 0) { } 

        char response = (char)Serial.read(); 

        if (response == 'y' || response == 'Y') {
            Serial.println("ShadowFollower: Mode: Waiting...");
            noTone(BUZZER);
            delay(4000); 
        } 
        else if (response == 'n' || response == 'N') {
            Serial.println("ShadowFollower: Mode: Autonomous Bypass...");
            noTone(BUZZER);
            smartEscape(); 
        }
    } 
    else {
        followLineLogic();
    }
}

void followLineLogic(void) {
    int leftSens = analogRead(IR_LEFT);
    int rightSens = analogRead(IR_RIGHT);

    if (leftSens < blackLineValue && rightSens < blackLineValue) {
        moveForward();
    } 
    else if (leftSens > blackLineValue) {
        turnLeft();
    } 
    else if (rightSens > blackLineValue) {
        turnRight();
    } 
    else {
        stopMotors();
    }
}

void smartEscape(void) {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
    delay(1000); 

    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
    delay(1500); 

    moveForward();
    delay(1500);
}

void moveForward(void) {
    analogWrite(ENA, 160); digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    analogWrite(ENB, 160); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void stopMotors(void) {
    analogWrite(ENA, 0); analogWrite(ENB, 0);
}

void turnLeft(void) {
    analogWrite(ENA, 60); digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    analogWrite(ENB, 160); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight(void) {
    analogWrite(ENA, 160); digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    analogWrite(ENB, 60); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

long getDistance(void) {
    digitalWrite(TRIG, LOW); 
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH); 
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    return pulseIn(ECHO, HIGH) * 0.034 / 2;
}