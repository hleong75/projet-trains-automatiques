/*
 * Script de test basique pour vérifier la configuration
 * Ce script teste les LEDs et le buzzer sans RFID ni moteur
 * Utile pour vérifier les connexions de base
 */

// Configuration des pins (même que le programme principal)
#define LED_GREEN       5
#define LED_RED         6  
#define LED_BLUE        7
#define BUZZER_PIN      8

void setup() {
  Serial.begin(9600);
  Serial.println("=== Test des Composants de Base ===");
  
  // Configuration des pins
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("Démarrage du test...");
  
  // Test séquentiel des LEDs
  testLEDs();
  
  // Test du buzzer
  testBuzzer();
  
  Serial.println("Test terminé. Les LEDs vont maintenant clignoter en continu.");
}

void loop() {
  // Simulation du cycle de fonctionnement
  simulateTrainCycle();
}

void testLEDs() {
  Serial.println("Test des LEDs...");
  
  // Test LED verte
  Serial.println("- LED Verte ON");
  digitalWrite(LED_GREEN, HIGH);
  delay(1000);
  digitalWrite(LED_GREEN, LOW);
  delay(500);
  
  // Test LED rouge
  Serial.println("- LED Rouge ON");
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_RED, LOW);
  delay(500);
  
  // Test LED bleue
  Serial.println("- LED Bleue ON");
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
  digitalWrite(LED_BLUE, LOW);
  delay(500);
  
  // Test toutes les LEDs ensemble
  Serial.println("- Toutes les LEDs ON");
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(500);
  
  Serial.println("Test des LEDs terminé.");
}

void testBuzzer() {
  Serial.println("Test du buzzer...");
  
  // Test bip simple
  Serial.println("- Bip simple");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  delay(500);
  
  // Test double bip
  Serial.println("- Double bip");
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
  delay(500);
  
  // Test mélodie simple
  Serial.println("- Mélodie de test");
  int melody[] = {200, 300, 400, 300, 200};
  for (int i = 0; i < 5; i++) {
    tone(BUZZER_PIN, melody[i], 200);
    delay(300);
  }
  
  Serial.println("Test du buzzer terminé.");
}

void simulateTrainCycle() {
  // Simulation: Train en marche (LED verte)
  Serial.println("Simulation: Train en marche");
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(3000);
  
  // Simulation: Station détectée (LED bleue + bip)
  Serial.println("Simulation: Station détectée");
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  delay(2800); // Reste de l'arrêt en station
  
  // Simulation: Reprise (double bip)
  Serial.println("Simulation: Reprise de la marche");
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
  digitalWrite(LED_BLUE, LOW);
  
  delay(1000);
}