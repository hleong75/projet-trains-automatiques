/*
 * RFID Test Sketch for Train System
 * 
 * This simple sketch helps you test your RFID setup and identify tag IDs
 * Use this to determine the IDs of your RFID tags before configuring the main system
 */

#include <SPI.h>
#include <MFRC522.h>

// RFID Module Pins (same as main project)
#define RST_PIN         9
#define SS_PIN          10

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);    // Wait for serial port
  
  Serial.println("=== RFID Tag ID Reader ===");
  Serial.println("Place RFID tags near the reader to see their IDs");
  Serial.println();
  
  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();         // Init MFRC522
  
  // Show reader details
  mfrc522.PCD_DumpVersionToSerial();
  
  // Test RFID reader
  if (mfrc522.PCD_PerformSelfTest()) {
    Serial.println("RFID Reader self-test: PASSED");
  } else {
    Serial.println("RFID Reader self-test: FAILED");
    Serial.println("Check your wiring and power connections");
  }
  
  Serial.println("Ready to read RFID tags...");
  Serial.println("========================================");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Show tag information
  Serial.println();
  Serial.println("RFID Tag Detected!");
  Serial.println("==================");
  
  // Show UID
  Serial.print("Tag UID: ");
  String tagID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (i > 0) {
      Serial.print(":");
      tagID += ":";
    }
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0");
      tagID += "0";
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    tagID += String(mfrc522.uid.uidByte[i], HEX);
  }
  tagID.toUpperCase();
  Serial.println();
  
  // Show formatted ID for config file
  Serial.print("For config file: \"");
  Serial.print(tagID);
  Serial.println("\"");
  
  // Show card type
  Serial.print("Card Type: ");
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  
  // Show memory size
  Serial.print("Memory Size: ");
  switch (piccType) {
    case MFRC522::PICC_TYPE_MIFARE_MINI:
      Serial.println("320 bytes");
      break;
    case MFRC522::PICC_TYPE_MIFARE_1K:
      Serial.println("1KB");
      break;
    case MFRC522::PICC_TYPE_MIFARE_4K:
      Serial.println("4KB");
      break;
    case MFRC522::PICC_TYPE_MIFARE_UL:
      Serial.println("512 bits");
      break;
    default:
      Serial.println("Unknown");
      break;
  }
  
  // Example configuration code
  Serial.println();
  Serial.println("Example station configuration:");
  Serial.println("================================");
  Serial.print("{\n  \"");
  Serial.print(tagID);
  Serial.println("\",");
  Serial.println("  \"My Station Name\",");
  Serial.println("  false,              // isTerminal");
  Serial.println("  3000,               // stopDuration (ms)");
  Serial.println("  120,                // speedLimit");
  Serial.println("  true                // hasAnnouncement");
  Serial.println("},");
  
  Serial.println();
  Serial.println("========================================");
  Serial.println("Waiting for next tag...");
  
  // Halt PICC
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
  delay(1000); // Wait before next read
}

// Additional functions for testing
void performAdvancedTest() {
  Serial.println("Performing advanced RFID tests...");
  
  // Test antenna gain
  byte gain = mfrc522.PCD_GetAntennaGain();
  Serial.print("Current antenna gain: ");
  Serial.print(gain, HEX);
  Serial.println(" (should be 0x04 or 0x07)");
  
  // Test communication
  byte version = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);
  Serial.print("Firmware version: 0x");
  Serial.println(version, HEX);
  
  if (version == 0x91 || version == 0x92) {
    Serial.println("Valid MFRC522 detected");
  } else {
    Serial.println("Warning: Unexpected firmware version");
  }
}

// Function to test tag writing (advanced users)
void writeTestData() {
  Serial.println("WARNING: This function writes to RFID tags!");
  Serial.println("Only proceed if you want to modify the tag content.");
  Serial.println("Type 'YES' to continue, or anything else to cancel:");
  
  while (!Serial.available()) {
    delay(100);
  }
  
  String response = Serial.readString();
  response.trim();
  
  if (response != "YES") {
    Serial.println("Tag writing cancelled.");
    return;
  }
  
  // Implementation would go here for writing station data to tags
  Serial.println("Tag writing not implemented in this test sketch.");
  Serial.println("Use the main train controller for operational use.");
}