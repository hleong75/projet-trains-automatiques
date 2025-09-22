/*
 * Motor Test Sketch for Train System
 * 
 * This sketch helps you test motor connections and calibrate speeds
 * Use this to verify your L298N motor driver setup before using the main system
 */

// Motor Driver Pins (L298N) - same as main project
#define MOTOR_IN1       4
#define MOTOR_IN2       5
#define MOTOR_ENA       6

// Test parameters
#define TEST_DURATION   2000    // 2 seconds per test
#define SPEED_STEP      25      // Speed increment for testing
#define PAUSE_BETWEEN   1000    // 1 second pause between tests

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("=== Motor Driver Test ===");
  Serial.println("This will test your motor connections");
  Serial.println("Make sure your motors are properly connected!");
  Serial.println();
  
  // Configure motor pins
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT);
  
  // Start with motors stopped
  stopMotor();
  
  Serial.println("Motor pins configured:");
  Serial.print("IN1: Pin ");
  Serial.println(MOTOR_IN1);
  Serial.print("IN2: Pin ");
  Serial.println(MOTOR_IN2);
  Serial.print("ENA: Pin ");
  Serial.println(MOTOR_ENA);
  Serial.println();
  
  Serial.println("Starting motor tests in 3 seconds...");
  delay(3000);
  
  runMotorTests();
  
  Serial.println();
  Serial.println("Motor tests complete!");
  Serial.println("Type commands to control motors manually:");
  Serial.println("Commands: forward, backward, stop, speed[0-255]");
  Serial.println("Examples: forward, speed150, backward, stop");
}

void loop() {
  // Handle serial commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();
    
    handleCommand(command);
  }
  
  delay(100);
}

void runMotorTests() {
  Serial.println("=== Starting Automated Tests ===");
  
  // Test 1: Basic forward movement
  Serial.println("Test 1: Forward direction at medium speed");
  moveForward(150);
  delay(TEST_DURATION);
  stopMotor();
  delay(PAUSE_BETWEEN);
  
  // Test 2: Basic backward movement
  Serial.println("Test 2: Backward direction at medium speed");
  moveBackward(150);
  delay(TEST_DURATION);
  stopMotor();
  delay(PAUSE_BETWEEN);
  
  // Test 3: Speed ramping forward
  Serial.println("Test 3: Speed ramping (forward)");
  testSpeedRamp(true);
  delay(PAUSE_BETWEEN);
  
  // Test 4: Speed ramping backward
  Serial.println("Test 4: Speed ramping (backward)");
  testSpeedRamp(false);
  delay(PAUSE_BETWEEN);
  
  // Test 5: Quick direction changes
  Serial.println("Test 5: Quick direction changes");
  testDirectionChanges();
  delay(PAUSE_BETWEEN);
  
  Serial.println("=== Automated Tests Complete ===");
}

void testSpeedRamp(bool forward) {
  Serial.print("Ramping speed from 0 to 255 (");
  Serial.print(forward ? "forward" : "backward");
  Serial.println(")");
  
  for (int speed = 0; speed <= 255; speed += SPEED_STEP) {
    Serial.print("Speed: ");
    Serial.println(speed);
    
    if (forward) {
      moveForward(speed);
    } else {
      moveBackward(speed);
    }
    
    delay(500);
  }
  
  stopMotor();
  Serial.println("Speed ramp complete");
}

void testDirectionChanges() {
  Serial.println("Testing quick direction changes...");
  
  for (int i = 0; i < 5; i++) {
    Serial.print("Change ");
    Serial.print(i + 1);
    Serial.println(": Forward");
    moveForward(120);
    delay(1000);
    
    Serial.print("Change ");
    Serial.print(i + 1);
    Serial.println(": Backward");
    moveBackward(120);
    delay(1000);
  }
  
  stopMotor();
  Serial.println("Direction change test complete");
}

void handleCommand(String command) {
  if (command == "forward") {
    Serial.println("Moving forward at speed 150");
    moveForward(150);
  }
  else if (command == "backward") {
    Serial.println("Moving backward at speed 150");
    moveBackward(150);
  }
  else if (command == "stop") {
    Serial.println("Stopping motor");
    stopMotor();
  }
  else if (command.startsWith("speed")) {
    // Extract speed value
    String speedStr = command.substring(5);
    int speed = speedStr.toInt();
    
    if (speed >= 0 && speed <= 255) {
      Serial.print("Setting speed to: ");
      Serial.println(speed);
      // Keep current direction, just change speed
      setMotorSpeed(speed);
    } else {
      Serial.println("Invalid speed! Use 0-255");
    }
  }
  else if (command == "test") {
    Serial.println("Running motor tests again...");
    runMotorTests();
  }
  else if (command == "help") {
    printHelp();
  }
  else {
    Serial.println("Unknown command. Type 'help' for available commands.");
  }
}

void moveForward(int speed) {
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, speed);
}

void moveBackward(int speed) {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  analogWrite(MOTOR_ENA, speed);
}

void stopMotor() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 0);
}

void setMotorSpeed(int speed) {
  // Maintain current direction, just change speed
  analogWrite(MOTOR_ENA, speed);
}

void printHelp() {
  Serial.println();
  Serial.println("=== Available Commands ===");
  Serial.println("forward     - Move forward at default speed");
  Serial.println("backward    - Move backward at default speed");
  Serial.println("stop        - Stop the motor");
  Serial.println("speed[0-255] - Set speed (e.g., speed100)");
  Serial.println("test        - Run automated tests again");
  Serial.println("help        - Show this help message");
  Serial.println();
  Serial.println("=== Troubleshooting Tips ===");
  Serial.println("- If motor doesn't move: Check power supply");
  Serial.println("- If motor runs but slowly: Check voltage level");
  Serial.println("- If direction is wrong: Swap motor wires");
  Serial.println("- If no response: Check L298N connections");
  Serial.println();
}

// Function to test motor driver without actual motor (LED test)
void testWithLED() {
  Serial.println("Testing motor driver outputs with LED...");
  Serial.println("Connect LEDs to IN1, IN2, and ENA pins to see signals");
  
  // This would blink LEDs connected to motor driver pins
  for (int i = 0; i < 5; i++) {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_ENA, 255);
    delay(500);
    
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
    analogWrite(MOTOR_ENA, 255);
    delay(500);
  }
  
  stopMotor();
  Serial.println("LED test complete");
}

// Function to measure motor current (if current sensing is available)
void measureCurrent() {
  Serial.println("Current measurement not implemented in basic setup");
  Serial.println("For current monitoring, add current sense resistors");
  Serial.println("and analog input connections to your circuit");
}