/*
  ROHIT BISWAS & AZHAR AHMED
  EXPERIMENTAL TECHNIQUES
  LIGHT DETECTION SOFTWARE
*/

#include <Servo.h>

// Create Servo objects for horizontal and vertical axes
Servo horizontal_servo;
Servo vertical_servo;

// Store the current angles for horizontal and vertical
int currentHorizontalAngle = 0;
int currentVerticalAngle   = 20;

void setup() {
  Serial.begin(9600);
  horizontal_servo.attach(5);
  vertical_servo.attach(6);

  // Perform an initial full sweep to find the best horizontal angle
  currentHorizontalAngle = findMaxPosition(horizontal_servo, A0);
  horizontal_servo.write(currentHorizontalAngle);
  delay(1200);

  // Perform an initial full sweep to find the best vertical angle
  currentVerticalAngle = findMaxPosition(vertical_servo, A0);
  vertical_servo.write(currentVerticalAngle);
  delay(1200);
}

void loop() {
  // Continuously refine horizontal angle around the current position
  currentHorizontalAngle = trackLightLocally(
                            horizontal_servo,
                            A0,
                            currentHorizontalAngle,
                            1,   // Step size
                            20   // Range around current angle
                          );

  // Continuously refine vertical angle around the current position
  currentVerticalAngle = trackLightLocally(
                          vertical_servo,
                          A0,
                          currentVerticalAngle,
                          1,   // Step size
                          20   // Range around current angle
                        );

  // Short delay before checking again
  delay(1000);
}

/**
 * Performs a full 0–180° sweep on the specified servo to find the angle
 * with the maximum voltage (i.e., brightest light).
 */
int findMaxPosition(Servo &servo, int sensorPin) {
  float maxVoltage = 0.0;
  int bestAngle = 25;

  for (int angle = 25; angle <= 180; angle++) {
    servo.write(angle);
    delay(50); // allow servo to move
    float voltage = readVoltage(sensorPin);

    if (voltage > maxVoltage) {
      maxVoltage = voltage;
      bestAngle = angle;
    }
  }

  return bestAngle;
}

/**
 * Looks around the current angle in a small +/- range to see if there's
 * a brighter spot nearby. Returns the new best angle found.
 */
int trackLightLocally(Servo &servo, int sensorPin, int currentAngle, int step, int range) {
  // Read the voltage at the current angle
  servo.write(currentAngle);
  delay(50);
  float bestVoltage = readVoltage(sensorPin);
  int bestAngle = currentAngle;

  // Check angles around the current angle
  for (int offset = -range; offset <= range; offset += step) {
    int testAngle = currentAngle + offset;

    // Keep angles within valid bounds
    if (testAngle < 25)   testAngle = 25;
    if (testAngle > 180) testAngle = 180;

    servo.write(testAngle);
    delay(50);
    float voltage = readVoltage(sensorPin);

    // If we find a better voltage, update bestAngle and bestVoltage
    if (voltage > bestVoltage) {
      bestVoltage = voltage;
      bestAngle = testAngle;
    }
  }

  // Move servo to the best angle in the local region
  servo.write(bestAngle);
  return bestAngle;
}

/**
 * Helper function to convert the raw analog reading to a voltage.
 */
float readVoltage(int sensorPin) {
  int rawValue = analogRead(sensorPin);
  return rawValue * (5.0 / 1023.0);
}