#include <IRremote.h>

// Pin Definitions
const int irSensorPin = 2;         // IR sensor pin
const int ultrasonicTrigPin = 3;   // Ultrasonic sensor trigger pin
const int ultrasonicEchoPin = 4;   // Ultrasonic sensor echo pin
const int buzzerPin = 5;           // Buzzer pin

long duration;                    // Duration of the pulse from ultrasonic sensor
int distance;                     // Distance measured by ultrasonic sensor (in cm)

void setup() {
  // Initialize pins
  pinMode(irSensorPin, INPUT);    // Set the IR sensor pin as input
  pinMode(ultrasonicTrigPin, OUTPUT);  // Set the ultrasonic trig pin as output
  pinMode(ultrasonicEchoPin, INPUT);  // Set the ultrasonic echo pin as input
  pinMode(buzzerPin, OUTPUT);     // Set the buzzer pin as output
  
  // Start serial communication for debugging (optional)
  Serial.begin(9600);             // Initialize serial communication at 9600 baud rate
}

void loop() {
  // Check if the IR sensor detects a person
  int personDetected = digitalRead(irSensorPin);  // Read the value from the IR sensor
  
  if (personDetected == HIGH) {  // If a person is detected
    // Send a pulse to the ultrasonic sensor to measure distance
    digitalWrite(ultrasonicTrigPin, LOW);  // Make sure the trigger pin is low for a brief moment
    delayMicroseconds(2);
    digitalWrite(ultrasonicTrigPin, HIGH); // Send a 10us HIGH pulse to trigger the sensor
    delayMicroseconds(10);
    digitalWrite(ultrasonicTrigPin, LOW);  // Set the trigger pin back to LOW
    
    // Measure the pulse duration that reflects the distance
    duration = pulseIn(ultrasonicEchoPin, HIGH);  // Read the duration of the pulse on the echo pin
    distance = duration * 0.0344 / 2;  // Convert duration to distance (in cm)

    // Output the measured distance to the serial monitor (for debugging)
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Check if the user is too close to the sensor (indicating poor posture)
    if (distance < 20) {  // If the distance is less than 20 cm, user is likely hunched over
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer to alert the user
    } else {
      digitalWrite(buzzerPin, LOW);   // Turn off the buzzer if posture is correct
    }
  } else {
    // If no person is detected, ensure the buzzer is off
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);  // Wait for half a second before checking again
}
