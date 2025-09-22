# Projet Trains Automatiques

Un système de contrôle Arduino pour trains miniatures avec détection RFID des stations.

## Description

Ce projet implémente un système de contrôle automatique pour trains miniatures utilisant la technologie RFID pour détecter les stations et gérer les arrêts automatiques.

## Fonctionnalités

- 🚂 Contrôle automatique du moteur de train
- 📡 Détection RFID des stations
- 🛑 Arrêts automatiques aux stations programmées
- 💡 Indicateurs LED d'état
- 🔊 Signalisation sonore
- ⏱️ Temps d'arrêt configurable en station

## Matériel Requis

### Composants Principaux
- **Arduino Uno/Nano** (ou compatible)
- **Module RFID RC522**
- **Contrôleur moteur L298N** (ou similaire)
- **Moteur DC** pour le train
- **Cartes/tags RFID** pour les stations

### Composants Additionnels
- **3 LEDs** (verte, rouge, bleue)
- **Buzzer** pour signalisation
- **Résistances** 220Ω pour les LEDs
- **Breadboard** et fils de connexion
- **Alimentation** 12V pour le moteur

## Schéma de Connexion

### Module RFID RC522
| Pin RC522 | Pin Arduino |
|-----------|-------------|
| VCC       | 3.3V        |
| GND       | GND         |
| RST       | Pin 9       |
| SDA/SS    | Pin 10      |
| MOSI      | Pin 11      |
| MISO      | Pin 12      |
| SCK       | Pin 13      |

### Contrôleur Moteur L298N
| Pin L298N | Pin Arduino |
|-----------|-------------|
| ENA       | Pin 3 (PWM) |
| IN1       | Pin 4       |
| VCC       | 5V          |
| GND       | GND         |

### LEDs et Signalisation
| Composant | Pin Arduino |
|-----------|-------------|
| LED Verte | Pin 5       |
| LED Rouge | Pin 6       |
| LED Bleue | Pin 7       |
| Buzzer    | Pin 8       |

## Installation et Configuration

### 1. Installation des Bibliothèques
Dans l'IDE Arduino, installez les bibliothèques suivantes :
- **MFRC522** (par GithubCommunity)

```
Outils > Gérer les bibliothèques > Rechercher "MFRC522"
```

### 2. Configuration des UIDs RFID
Modifiez les UIDs dans le code pour correspondre à vos cartes RFID :

```cpp
byte stationUIDs[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF},  // Station 1 - Remplacez par votre UID
  {0xCA, 0xFE, 0xBA, 0xBE},  // Station 2 - Remplacez par votre UID
  {0x12, 0x34, 0x56, 0x78},  // Station 3 - Remplacez par votre UID
};
```

### 3. Téléchargement du Code
1. Ouvrez `train_rfid_controller.ino` dans l'IDE Arduino
2. Sélectionnez votre carte Arduino
3. Sélectionnez le port série approprié
4. Téléchargez le code sur votre Arduino

## Utilisation

### Démarrage
1. Alimentez votre Arduino et le système moteur
2. Le train démarre automatiquement
3. La LED verte indique que le train est en marche

### Fonctionnement
- **LED Verte** : Train en marche
- **LED Rouge** : Train arrêté
- **LED Bleue** : Station RFID détectée
- **Buzzer** : 1 bip = arrêt en station, 2 bips = reprise

### Détection de Station
1. Placez une carte RFID configurée près du lecteur
2. Le train s'arrête automatiquement
3. Après 3 secondes (configurable), le train repart

## Paramètres Configurables

```cpp
#define MOTOR_SPEED     150         // Vitesse du moteur (0-255)
#define STOP_DURATION   3000        // Durée d'arrêt en station (ms)
const unsigned long RFID_COOLDOWN = 2000; // Temps entre lectures RFID
```

## Dépannage

### Problèmes Courants

**Le module RFID ne fonctionne pas :**
- Vérifiez les connexions SPI
- Assurez-vous que l'alimentation est stable (3.3V)
- Vérifiez que la bibliothèque MFRC522 est installée

**Le moteur ne fonctionne pas :**
- Vérifiez l'alimentation du contrôleur moteur
- Vérifiez les connexions PWM et direction
- Testez avec un moteur différent

**Les cartes RFID ne sont pas reconnues :**
- Utilisez le moniteur série pour voir les UIDs lus
- Mettez à jour les UIDs dans le code
- Vérifiez la distance entre la carte et le lecteur

### Debug
Ouvrez le moniteur série (9600 bauds) pour voir :
- L'état d'initialisation
- Les UIDs RFID détectés
- L'état du train en temps réel

## Améliorations Possibles

- 🔄 Ajout de capteurs de fin de course
- 📍 Système de navigation multi-circuits
- 🌐 Interface web pour contrôle à distance
- 📊 Journalisation des trajets
- 🚥 Système de signalisation avancé

## Licence

Ce projet est sous licence libre. Vous pouvez l'utiliser et le modifier selon vos besoins.

## Contribution

Les contributions sont les bienvenues ! N'hésitez pas à proposer des améliorations ou à signaler des problèmes.
