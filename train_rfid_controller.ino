/*
 * Programme Arduino pour Train Miniature avec RFID
 * Auteur: Projet Trains Automatiques
 * 
 * Ce programme contrôle un train miniature automatique avec:
 * - Lecture RFID pour détection de stations
 * - Contrôle de moteur DC
 * - Arrêts automatiques aux stations
 * - LEDs d'indication d'état
 */

#include <SPI.h>
#include <MFRC522.h>

// Configuration des pins
#define RST_PIN         9           // Pin RST du module RFID
#define SS_PIN          10          // Pin SDA/SS du module RFID
#define MOTOR_PIN_1     3           // Pin 1 du contrôleur moteur (PWM)
#define MOTOR_PIN_2     4           // Pin 2 du contrôleur moteur
#define LED_GREEN       5           // LED verte (train en marche)
#define LED_RED         6           // LED rouge (train arrêté)
#define LED_BLUE        7           // LED bleue (station détectée)
#define BUZZER_PIN      8           // Buzzer pour signalisation

// Configuration du moteur
#define MOTOR_SPEED     150         // Vitesse du moteur (0-255)
#define STOP_DURATION   3000        // Durée d'arrêt en station (ms)

// Initialisation du module RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Variables globales
bool trainRunning = true;           // État du train
bool stationDetected = false;       // Station détectée
unsigned long stopStartTime = 0;   // Temps de début d'arrêt
unsigned long lastRfidRead = 0;     // Dernière lecture RFID
const unsigned long RFID_COOLDOWN = 2000; // Temps d'attente entre lectures RFID

// UIDs des cartes RFID de stations (à personnaliser)
byte stationUIDs[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF},  // Station 1
  {0xCA, 0xFE, 0xBA, 0xBE},  // Station 2
  {0x12, 0x34, 0x56, 0x78},  // Station 3
};
const int NUM_STATIONS = 3;

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("=== Train Miniature avec RFID ===");
  Serial.println("Initialisation...");
  
  // Configuration des pins
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initialisation SPI et RFID
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Test du module RFID
  Serial.print("Version du firmware: 0x");
  byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.println(version, HEX);
  
  if (version == 0x00 || version == 0xFF) {
    Serial.println("ATTENTION: Communication RFID échouée!");
  } else {
    Serial.println("Module RFID initialisé avec succès");
  }
  
  // Démarrage du train
  startTrain();
  Serial.println("Train démarré - Recherche de stations RFID...");
}

void loop() {
  // Lecture RFID
  checkRFID();
  
  // Gestion des états du train
  if (trainRunning && !stationDetected) {
    // Train en marche normale
    runTrain();
    setLEDs(true, false, false);
  } else if (stationDetected) {
    // Station détectée - arrêt temporaire
    stopTrain();
    setLEDs(false, true, true);
    
    // Vérifier si le temps d'arrêt est écoulé
    if (millis() - stopStartTime >= STOP_DURATION) {
      stationDetected = false;
      trainRunning = true;
      Serial.println("Reprise de la marche");
      signalBeep(2); // Double bip de reprise
    }
  }
  
  delay(100); // Petite pause pour éviter la surcharge
}

void checkRFID() {
  // Vérifier la présence d'une carte et le cooldown
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  if (millis() - lastRfidRead < RFID_COOLDOWN) {
    return; // Trop tôt pour une nouvelle lecture
  }
  
  // Lire l'UID de la carte
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uidString += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  uidString.toUpperCase();
  
  Serial.print("Carte RFID détectée: ");
  Serial.println(uidString);
  
  // Vérifier si c'est une station connue
  for (int i = 0; i < NUM_STATIONS; i++) {
    if (compareUID(mfrc522.uid.uidByte, stationUIDs[i])) {
      Serial.print("Station ");
      Serial.print(i + 1);
      Serial.println(" détectée!");
      
      stationDetected = true;
      stopStartTime = millis();
      lastRfidRead = millis();
      signalBeep(1); // Un bip pour signaler l'arrêt
      break;
    }
  }
  
  // Arrêter la lecture RFID
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

bool compareUID(byte* uid1, byte* uid2) {
  for (int i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}

void startTrain() {
  trainRunning = true;
  Serial.println("Train démarré");
}

void runTrain() {
  // Faire avancer le train
  analogWrite(MOTOR_PIN_1, MOTOR_SPEED);
  digitalWrite(MOTOR_PIN_2, LOW);
}

void stopTrain() {
  // Arrêter le train
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, LOW);
}

void setLEDs(bool green, bool red, bool blue) {
  digitalWrite(LED_GREEN, green ? HIGH : LOW);
  digitalWrite(LED_RED, red ? HIGH : LOW);
  digitalWrite(LED_BLUE, blue ? HIGH : LOW);
}

void signalBeep(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    if (i < count - 1) {
      delay(200);
    }
  }
}

// Fonction pour afficher les informations de debug
void printDebugInfo() {
  Serial.println("=== État du système ===");
  Serial.print("Train en marche: ");
  Serial.println(trainRunning ? "Oui" : "Non");
  Serial.print("Station détectée: ");
  Serial.println(stationDetected ? "Oui" : "Non");
  Serial.print("Temps depuis arrêt: ");
  Serial.print(millis() - stopStartTime);
  Serial.println(" ms");
  Serial.println("=====================");
}