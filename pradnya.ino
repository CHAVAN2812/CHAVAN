#include <Servo.h>

const int soilSensorPin = A0;    // Soil moisture sensor connected to analog pin A0
const int ledPin = 13;           // LED connected to digital pin 13
const int servoPin = 8;          // Servo motor connected to digital pin 8
const int trigPin = 10;          // Ultrasonic sensor trigger pin
const int echoPin = 11;          // Ultrasonic sensor echo pin

Servo myservo; // Create a servo object

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin); // Attach the servo to the specified pin
  Serial.begin(9600);
}

float getDistanceUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;  // Calculate distance in centimeters
  return distance;
}

void loop() {
  int soilMoisture = analogRead(soilSensorPin); // Read analog value from soil moisture sensor
  float ultrasonicDistance = getDistanceUltrasonic();  // Get distance from ultrasonic sensor

  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);
  Serial.print("Ultrasonic Distance: ");
  Serial.println(ultrasonicDistance);

  int dryThreshold = 600;
  int dryThreshold1 = 700;
  
  if (ultrasonicDistance < 4) {
    if (soilMoisture > dryThreshold) {
      digitalWrite(ledPin, HIGH);
      myservo.write(180); // Rotate servo to 180 degrees
      Serial.println("Servo Rotated to 180 degrees");
      delay(1000);
    }
    if (soilMoisture < dryThreshold1) {
      digitalWrite(ledPin, HIGH);
      myservo.write(0); // Rotate servo to 0 degrees
      Serial.println("Servo Rotated to 0 degrees");
      delay(1000);
    }
  } 
  else {
    digitalWrite(ledPin, HIGH);
    myservo.write(90); // Rotate servo to 90 degrees (middle position)
    Serial.println("Servo Rotated to 90 degrees");
  }
  delay(100); // Add a small delay to prevent rapid iterations
}
