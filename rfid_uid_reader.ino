/*
 * Script de test pour lire les UIDs des cartes RFID
 * Utilisez ce script pour identifier les UIDs de vos cartes
 * et les configurer dans le programme principal
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("=== Lecteur UID RFID ===");
  Serial.println("Approchez une carte du lecteur pour lire son UID");
  Serial.println();
}

void loop() {
  // Chercher une nouvelle carte
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Sélectionner une carte
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Afficher l'UID
  Serial.print("UID de la carte: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  // Afficher le format pour le code principal
  Serial.print("Format pour le code: {");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print("0x");
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) {
      Serial.print(", ");
    }
  }
  Serial.println("}");
  Serial.println();

  // Arrêter la lecture
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
  delay(2000); // Attendre 2 secondes avant la prochaine lecture
}