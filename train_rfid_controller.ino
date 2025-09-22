/*
 * Arduino Program for Miniature Train with RFID Control
 * 
 * This program controls a miniature train system using RFID tags for:
 * - Train identification
 * - Station detection
 * - Automated route control
 * - Speed and direction management
 * 
 * Hardware Requirements:
 * - Arduino Uno/Nano
 * - RC522 RFID Reader Module
 * - L298N Motor Driver
 * - DC Motors for train movement
 * - LEDs for status indication
 * - Push buttons for manual control
 * 
 * Author: Train Automation Project
 * Version: 1.0
 */

#include <SPI.h>
#include <MFRC522.h>

// RFID Module Pins
#define RST_PIN         9
#define SS_PIN          10

// Motor Driver Pins (L298N)
#define MOTOR_IN1       4
#define MOTOR_IN2       5
#define MOTOR_ENA       6

// LED Status Indicators
#define LED_POWER       2
#define LED_RFID        3
#define LED_STATION     7
#define LED_ERROR       8

// Button Pins
#define BTN_START       A0
#define BTN_STOP        A1
#define BTN_EMERGENCY   A2

// Speed and Control Constants
#define MAX_SPEED       255
#define CRUISE_SPEED    180
#define SLOW_SPEED      100
#define STATION_DELAY   3000  // 3 seconds stop at station

// RFID Object
MFRC522 mfrc522(SS_PIN, RST_PIN);

// System State Variables
enum TrainState {
  STOPPED,
  STARTING,
  RUNNING,
  APPROACHING_STATION,
  AT_STATION,
  EMERGENCY_STOP
};

TrainState currentState = STOPPED;
int currentSpeed = 0;
bool trainDirection = true; // true = forward, false = backward
unsigned long stationStopTime = 0;
String lastRFIDTag = "";
unsigned long lastRFIDTime = 0;

// Station and Route Management
struct Station {
  String rfidTag;
  String name;
  bool isTerminal;
  int stopDuration;
};

// Predefined stations (can be expanded)
Station stations[] = {
  {"04:52:7E:2A", "Station Central", false, 3000},
  {"04:8F:2C:1B", "Station Nord", true, 5000},
  {"04:A3:5D:4C", "Station Sud", true, 5000},
  {"04:71:9B:8E", "Depot", false, 2000}
};

const int numStations = sizeof(stations) / sizeof(stations[0]);

void setup() {
  Serial.begin(9600);
  Serial.println("=== Train RFID Controller Starting ===");
  
  // Initialize SPI bus
  SPI.begin();
  
  // Initialize RFID reader
  mfrc522.PCD_Init();
  
  // Configure pins
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT);
  
  pinMode(LED_POWER, OUTPUT);
  pinMode(LED_RFID, OUTPUT);
  pinMode(LED_STATION, OUTPUT);
  pinMode(LED_ERROR, OUTPUT);
  
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);
  pinMode(BTN_EMERGENCY, INPUT_PULLUP);
  
  // Initial setup
  stopTrain();
  digitalWrite(LED_POWER, HIGH);
  
  Serial.println("System initialized successfully");
  Serial.println("Waiting for RFID tags or button commands...");
  
  // Test RFID reader
  if (mfrc522.PCD_PerformSelfTest()) {
    Serial.println("RFID Reader self-test passed");
    blinkLED(LED_RFID, 3);
  } else {
    Serial.println("RFID Reader self-test failed");
    digitalWrite(LED_ERROR, HIGH);
  }
}

void loop() {
  // Check for emergency stop
  if (digitalRead(BTN_EMERGENCY) == LOW) {
    emergencyStop();
    return;
  }
  
  // Check manual controls
  checkManualControls();
  
  // Read RFID tags
  checkRFIDTags();
  
  // Update train state machine
  updateTrainState();
  
  // Update status LEDs
  updateStatusLEDs();
  
  delay(100); // Main loop delay
}

void checkManualControls() {
  static unsigned long lastButtonCheck = 0;
  if (millis() - lastButtonCheck < 200) return; // Debounce
  lastButtonCheck = millis();
  
  if (digitalRead(BTN_START) == LOW && currentState == STOPPED) {
    Serial.println("Manual start command");
    startTrain();
  }
  
  if (digitalRead(BTN_STOP) == LOW && currentState != STOPPED) {
    Serial.println("Manual stop command");
    stopTrain();
  }
}

void checkRFIDTags() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Read card UID
  String tagUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (i > 0) tagUID += ":";
    if (mfrc522.uid.uidByte[i] < 0x10) tagUID += "0";
    tagUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  tagUID.toUpperCase();
  
  // Avoid reading the same tag repeatedly
  if (tagUID == lastRFIDTag && (millis() - lastRFIDTime) < 2000) {
    return;
  }
  
  lastRFIDTag = tagUID;
  lastRFIDTime = millis();
  
  Serial.print("RFID Tag detected: ");
  Serial.println(tagUID);
  
  // Flash RFID LED
  blinkLED(LED_RFID, 1);
  
  // Process the tag
  processRFIDTag(tagUID);
  
  // Halt PICC
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void processRFIDTag(String tagUID) {
  // Check if tag corresponds to a known station
  for (int i = 0; i < numStations; i++) {
    if (stations[i].rfidTag == tagUID) {
      Serial.print("Arrived at station: ");
      Serial.println(stations[i].name);
      
      if (currentState == RUNNING) {
        arriveAtStation(i);
      }
      return;
    }
  }
  
  // Handle unknown tags (could be train ID tags)
  Serial.println("Unknown RFID tag - could be train identifier");
  
  // If train is stopped, start it when train ID tag is detected
  if (currentState == STOPPED) {
    Serial.println("Train ID detected - starting train");
    startTrain();
  }
}

void arriveAtStation(int stationIndex) {
  currentState = AT_STATION;
  stationStopTime = millis();
  
  // Stop at station
  setTrainSpeed(0);
  
  digitalWrite(LED_STATION, HIGH);
  
  Serial.print("Stopping at ");
  Serial.print(stations[stationIndex].name);
  Serial.print(" for ");
  Serial.print(stations[stationIndex].stopDuration);
  Serial.println(" ms");
  
  // Handle terminal stations
  if (stations[stationIndex].isTerminal) {
    Serial.println("Terminal station reached - reversing direction");
    trainDirection = !trainDirection;
  }
}

void startTrain() {
  if (currentState != EMERGENCY_STOP) {
    currentState = STARTING;
    Serial.println("Starting train...");
    
    // Gradual acceleration
    for (int speed = 0; speed <= CRUISE_SPEED; speed += 10) {
      setTrainSpeed(speed);
      delay(50);
    }
    
    currentState = RUNNING;
    Serial.println("Train running at cruise speed");
  }
}

void stopTrain() {
  if (currentState != EMERGENCY_STOP) {
    Serial.println("Stopping train...");
    
    // Gradual deceleration
    for (int speed = currentSpeed; speed >= 0; speed -= 15) {
      setTrainSpeed(speed);
      delay(30);
    }
    
    currentState = STOPPED;
    digitalWrite(LED_STATION, LOW);
    Serial.println("Train stopped");
  }
}

void emergencyStop() {
  currentState = EMERGENCY_STOP;
  setTrainSpeed(0);
  digitalWrite(LED_ERROR, HIGH);
  
  Serial.println("EMERGENCY STOP ACTIVATED!");
  
  // Blink error LED rapidly
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_ERROR, !digitalRead(LED_ERROR));
    delay(100);
  }
  
  // Reset to stopped state after emergency
  currentState = STOPPED;
  digitalWrite(LED_ERROR, LOW);
}

void setTrainSpeed(int speed) {
  currentSpeed = constrain(speed, 0, MAX_SPEED);
  
  if (currentSpeed == 0) {
    // Stop motor
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_ENA, 0);
  } else {
    // Set direction
    if (trainDirection) {
      digitalWrite(MOTOR_IN1, HIGH);
      digitalWrite(MOTOR_IN2, LOW);
    } else {
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, HIGH);
    }
    
    // Set speed
    analogWrite(MOTOR_ENA, currentSpeed);
  }
}

void updateTrainState() {
  switch (currentState) {
    case AT_STATION:
      // Check if station stop time has elapsed
      if (millis() - stationStopTime >= STATION_DELAY) {
        digitalWrite(LED_STATION, LOW);
        Serial.println("Departing from station");
        startTrain();
      }
      break;
      
    case RUNNING:
      // Normal running state - maintain speed
      if (currentSpeed != CRUISE_SPEED) {
        setTrainSpeed(CRUISE_SPEED);
      }
      break;
      
    default:
      // Other states handled elsewhere
      break;
  }
}

void updateStatusLEDs() {
  static unsigned long lastLEDUpdate = 0;
  static bool ledState = false;
  
  if (millis() - lastLEDUpdate >= 500) {
    lastLEDUpdate = millis();
    ledState = !ledState;
    
    // Power LED always on
    digitalWrite(LED_POWER, HIGH);
    
    // Running indicator - blink when running
    if (currentState == RUNNING) {
      digitalWrite(LED_RFID, ledState);
    } else if (currentState == STOPPED) {
      digitalWrite(LED_RFID, LOW);
    }
  }
}

void blinkLED(int pin, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
  }
}

// Serial command interface for debugging
void serialEvent() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "start") {
      startTrain();
    } else if (command == "stop") {
      stopTrain();
    } else if (command == "status") {
      printStatus();
    } else if (command == "emergency") {
      emergencyStop();
    } else if (command == "reset") {
      currentState = STOPPED;
      digitalWrite(LED_ERROR, LOW);
      Serial.println("System reset");
    }
  }
}

void printStatus() {
  Serial.println("=== Train Status ===");
  Serial.print("State: ");
  switch (currentState) {
    case STOPPED: Serial.println("STOPPED"); break;
    case STARTING: Serial.println("STARTING"); break;
    case RUNNING: Serial.println("RUNNING"); break;
    case APPROACHING_STATION: Serial.println("APPROACHING_STATION"); break;
    case AT_STATION: Serial.println("AT_STATION"); break;
    case EMERGENCY_STOP: Serial.println("EMERGENCY_STOP"); break;
  }
  Serial.print("Speed: ");
  Serial.println(currentSpeed);
  Serial.print("Direction: ");
  Serial.println(trainDirection ? "Forward" : "Backward");
  Serial.print("Last RFID: ");
  Serial.println(lastRFIDTag);
  Serial.println("==================");
}