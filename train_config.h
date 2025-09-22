/*
 * Train Configuration Library
 * 
 * This file contains all configurable parameters for the train system.
 * Modify these values to customize your train layout and behavior.
 */

#ifndef TRAIN_CONFIG_H
#define TRAIN_CONFIG_H

// ===============================
// PIN CONFIGURATION
// ===============================

// RFID Module Pins
#define RST_PIN         9
#define SS_PIN          10

// Motor Driver Pins (L298N)
#define MOTOR_IN1       4
#define MOTOR_IN2       5
#define MOTOR_ENA       6

// Optional second motor (for dual motor trains)
#define MOTOR_IN3       -1  // Set to -1 if not used
#define MOTOR_IN4       -1  // Set to -1 if not used
#define MOTOR_ENB       -1  // Set to -1 if not used

// LED Status Indicators
#define LED_POWER       2
#define LED_RFID        3
#define LED_STATION     7
#define LED_ERROR       8

// Control Button Pins
#define BTN_START       A0
#define BTN_STOP        A1
#define BTN_EMERGENCY   A2

// Optional Components
#define BUZZER_PIN      -1  // Set to pin number if buzzer is connected
#define LCD_RS          -1  // LCD pins if display is connected
#define LCD_EN          -1
#define LCD_D4          -1
#define LCD_D5          -1
#define LCD_D6          -1
#define LCD_D7          -1

// ===============================
// SPEED AND TIMING CONFIGURATION
// ===============================

// Motor Speed Settings (0-255)
#define MAX_SPEED       255
#define CRUISE_SPEED    180
#define SLOW_SPEED      100
#define STARTING_SPEED  80

// Timing Settings (milliseconds)
#define STATION_DELAY       3000    // Default stop time at stations
#define ACCELERATION_STEP   10      // Speed increase per step
#define ACCELERATION_DELAY  50      // Delay between acceleration steps
#define DECELERATION_STEP   15      // Speed decrease per step
#define DECELERATION_DELAY  30      // Delay between deceleration steps
#define RFID_READ_COOLDOWN  2000    // Time before re-reading same tag
#define BUTTON_DEBOUNCE     200     // Button debounce time
#define LED_BLINK_INTERVAL  500     // LED blink rate for status
#define EMERGENCY_BLINK     100     // Emergency LED blink rate

// ===============================
// SYSTEM BEHAVIOR CONFIGURATION
// ===============================

// Direction Settings
#define FORWARD_DIRECTION   true
#define REVERSE_DIRECTION   false
#define AUTO_REVERSE_AT_TERMINAL true

// Safety Settings
#define ENABLE_EMERGENCY_STOP    true
#define ENABLE_GRADUAL_STOPS     true
#define ENABLE_SPEED_LIMITING    true
#define MAX_CONTINUOUS_RUN_TIME  300000  // 5 minutes max continuous run

// Debug Settings
#define ENABLE_SERIAL_DEBUG      true
#define SERIAL_BAUD_RATE        9600
#define ENABLE_VERBOSE_LOGGING   true

// ===============================
// STATION CONFIGURATION
// ===============================

// Maximum number of stations supported
#define MAX_STATIONS    10

// Station data structure
struct StationConfig {
  const char* rfidTag;
  const char* name;
  bool isTerminal;
  int stopDuration;
  int speedLimit;     // Speed limit approaching this station (0 = no limit)
  bool hasAnnouncement;
};

// Default station configurations
// Modify these for your specific RFID tags and layout
const StationConfig DEFAULT_STATIONS[] = {
  {
    "04:52:7E:2A",      // RFID tag ID
    "Central Station",   // Station name
    false,              // Not a terminal station
    3000,               // Stop for 3 seconds
    120,                // Slow down to 120 when approaching
    true                // Play announcement
  },
  {
    "04:8F:2C:1B",
    "North Terminal",
    true,               // Terminal station (train reverses here)
    5000,               // Stop for 5 seconds
    80,                 // Slow down to 80 when approaching
    true
  },
  {
    "04:A3:5D:4C",
    "South Terminal",
    true,
    5000,
    80,
    true
  },
  {
    "04:71:9B:8E",
    "Maintenance Depot",
    false,
    2000,
    60,                 // Very slow approach to depot
    false
  },
  {
    "04:B1:C2:D3",
    "Freight Yard",
    false,
    4000,
    100,
    false
  }
};

// Number of configured stations
const int NUM_DEFAULT_STATIONS = sizeof(DEFAULT_STATIONS) / sizeof(DEFAULT_STATIONS[0]);

// ===============================
// TRAIN CONFIGURATION
// ===============================

// Train ID tags and their properties
struct TrainConfig {
  const char* rfidTag;
  const char* name;
  int maxSpeed;
  int cruiseSpeed;
  bool hasLight;
  bool hasSiren;
};

const TrainConfig TRAIN_CONFIGS[] = {
  {
    "04:AA:BB:CC",
    "Express Train",
    255,                // Maximum speed
    200,                // Cruise speed
    true,               // Has lights
    false               // No siren
  },
  {
    "04:DD:EE:FF",
    "Local Train",
    200,
    150,
    true,
    false
  },
  {
    "04:99:88:77",
    "Maintenance Vehicle",
    120,
    80,
    true,
    true                // Has siren/warning
  }
};

const int NUM_TRAIN_CONFIGS = sizeof(TRAIN_CONFIGS) / sizeof(TRAIN_CONFIGS[0]);

// ===============================
// ROUTE CONFIGURATION
// ===============================

// Define routes between stations
struct RouteSegment {
  int fromStation;
  int toStation;
  int speedLimit;
  int travelTime;     // Expected travel time in ms
};

// Example routes (station indices from STATIONS array)
const RouteSegment DEFAULT_ROUTES[] = {
  {0, 1, 180, 15000},  // Central to North Terminal
  {1, 0, 180, 15000},  // North Terminal to Central
  {0, 2, 180, 20000},  // Central to South Terminal
  {2, 0, 180, 20000},  // South Terminal to Central
  {0, 3, 100, 8000},   // Central to Depot (slow)
  {3, 0, 100, 8000}    // Depot to Central (slow)
};

const int NUM_ROUTES = sizeof(DEFAULT_ROUTES) / sizeof(DEFAULT_ROUTES[0]);

// ===============================
// SOUND AND ANNOUNCEMENT CONFIG
// ===============================

// Sound effect durations (if buzzer is connected)
#define STARTUP_SOUND_DURATION    1000
#define STATION_ARRIVAL_BEEPS     3
#define EMERGENCY_ALARM_DURATION  5000
#define BUTTON_FEEDBACK_DURATION  100

// Announcement delays
#define ANNOUNCEMENT_DELAY        500   // Delay before station announcement
#define DEPARTURE_WARNING_TIME    2000  // Warning before departure

// ===============================
// ERROR HANDLING CONFIGURATION
// ===============================

// Error codes
enum ErrorCode {
  NO_ERROR = 0,
  RFID_INIT_FAILED = 1,
  MOTOR_DRIVER_ERROR = 2,
  EMERGENCY_STOP_ACTIVE = 3,
  UNKNOWN_RFID_TAG = 4,
  OVERSPEED_DETECTED = 5,
  COMMUNICATION_ERROR = 6
};

// Error behavior
#define RETRY_RFID_INIT_COUNT     3
#define ERROR_LED_FLASH_COUNT     5
#define AUTO_RECOVERY_TIMEOUT     10000  // 10 seconds

// ===============================
// ADVANCED FEATURES CONFIGURATION
// ===============================

// Feature flags - set to false to disable features
#define ENABLE_MULTIPLE_TRAINS    false
#define ENABLE_TRACK_SWITCHING    false
#define ENABLE_OBSTACLE_DETECTION false
#define ENABLE_SPEED_MONITORING   true
#define ENABLE_DATA_LOGGING       false
#define ENABLE_WEB_INTERFACE      false

// Multi-train settings (if ENABLE_MULTIPLE_TRAINS is true)
#define MAX_TRAINS_ON_TRACK       2
#define TRAIN_SEPARATION_DISTANCE 50   // Minimum distance between trains

// Track switching settings (if ENABLE_TRACK_SWITCHING is true)
#define SERVO_SWITCH_PIN          A3
#define SWITCH_ACTIVATION_TIME    1000

// Obstacle detection settings (if ENABLE_OBSTACLE_DETECTION is true)
#define ULTRASONIC_TRIG_PIN       11
#define ULTRASONIC_ECHO_PIN       12
#define OBSTACLE_DISTANCE_CM      20    // Stop if obstacle within 20cm

#endif // TRAIN_CONFIG_H