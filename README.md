# Arduino Train RFID Controller

Un système de contrôle automatique pour trains miniatures utilisant la technologie RFID pour la détection des stations et l'identification des trains.

## 🚂 Fonctionnalités

- **Contrôle automatique des trains** avec démarrage/arrêt intelligent
- **Détection RFID** pour identification des stations et des trains
- **Gestion des stations** avec arrêts automatiques et durées configurables
- **Contrôle de vitesse** avec accélération/décélération progressives
- **Stations terminales** avec inversion automatique de direction
- **Interface de contrôle manuel** avec boutons physiques
- **Indicateurs LED** pour le statut du système
- **Communication série** pour débogage et contrôle à distance
- **Arrêt d'urgence** pour la sécurité
- **Configuration modulaire** facile à personnaliser

## 📋 Matériel Requis

### Composants Principaux
- **Arduino Uno/Nano** - Microcontrôleur principal
- **Module RFID RC522** - Lecture des tags RFID
- **Driver Moteur L298N** - Contrôle des moteurs DC
- **Moteurs DC** - Mouvement du train
- **Tags RFID** - Identification des stations et trains
- **LEDs** (4x) - Indicateurs de statut
- **Boutons poussoirs** (3x) - Contrôles manuels
- **Résistances** (220Ω pour LEDs, 10kΩ pour boutons)

### Composants Optionnels
- **Écran LCD** - Affichage du statut
- **Buzzer** - Effets sonores
- **Servo-moteurs** - Aiguillages automatiques
- **Capteurs** - Détection d'obstacles

## 🔧 Installation

### 1. Préparation de l'IDE Arduino
```bash
# Installer les bibliothèques requises dans l'IDE Arduino:
# - MFRC522 (pour RFID)
# - SPI (intégrée)
```

### 2. Câblage du Circuit
Consultez le fichier [HARDWARE_SETUP.md](HARDWARE_SETUP.md) pour les instructions détaillées de câblage.

### 3. Configuration des Tags RFID
Programmez vos tags RFID avec les IDs définis dans `train_config.h`:

| Station | Tag RFID | Type | Durée d'arrêt |
|---------|----------|------|---------------|
| Station Centrale | 04:52:7E:2A | Normal | 3 secondes |
| Terminal Nord | 04:8F:2C:1B | Terminal | 5 secondes |
| Terminal Sud | 04:A3:5D:4C | Terminal | 5 secondes |
| Dépôt | 04:71:9B:8E | Normal | 2 secondes |

### 4. Téléchargement du Code
1. Ouvrez `train_rfid_controller.ino` dans l'IDE Arduino
2. Modifiez `train_config.h` selon votre configuration
3. Compilez et téléchargez vers l'Arduino

## 🚀 Utilisation

### Démarrage du Système
1. **Alimentez l'Arduino** - La LED d'alimentation s'allume
2. **Vérifiez le module RFID** - La LED RFID clignote 3 fois si OK
3. **Ouvrez le moniteur série** (9600 baud) pour voir les messages

### Contrôles Manuels
- **Bouton START** - Démarre le train
- **Bouton STOP** - Arrête le train
- **Bouton EMERGENCY** - Arrêt d'urgence immédiat

### Contrôles par Série
Envoyez ces commandes via le moniteur série:
```
start      - Démarre le train
stop       - Arrête le train
status     - Affiche l'état du système
emergency  - Arrêt d'urgence
reset      - Remet à zéro après urgence
```

### Fonctionnement Automatique
1. **Placez un tag train** près du lecteur RFID pour démarrer
2. **Le train démarre** et accélère progressivement
3. **À chaque station**, le train s'arrête automatiquement
4. **Aux stations terminales**, le train change de direction
5. **Surveillance continue** via les LEDs et le moniteur série

## ⚙️ Configuration

### Personnalisation des Stations
Modifiez le tableau `DEFAULT_STATIONS` dans `train_config.h`:

```cpp
const StationConfig DEFAULT_STATIONS[] = {
  {
    "04:52:7E:2A",      // ID du tag RFID
    "Ma Station",       // Nom de la station
    false,              // Terminal (true/false)
    3000,               // Durée d'arrêt (ms)
    120,                // Limite de vitesse en approche
    true                // Annonce sonore
  },
  // Ajoutez d'autres stations...
};
```

### Réglage des Vitesses
```cpp
#define MAX_SPEED       255    // Vitesse maximale
#define CRUISE_SPEED    180    // Vitesse de croisière
#define SLOW_SPEED      100    // Vitesse lente
```

### Configuration des Pins
Tous les pins sont configurables dans `train_config.h`:
```cpp
#define MOTOR_IN1       4      // Contrôle moteur
#define LED_POWER       2      // LED d'alimentation
#define BTN_START       A0     // Bouton démarrage
```

## 🔍 Dépannage

### Problèmes Courants

#### ❌ RFID ne fonctionne pas
- Vérifiez les connexions (surtout l'alimentation 3.3V)
- Assurez-vous que les tags sont à 1-3cm du lecteur
- Vérifiez les messages du moniteur série

#### ❌ Moteurs ne bougent pas
- Vérifiez l'alimentation des moteurs (6-12V)
- Contrôlez les connexions du driver L298N
- Testez avec les commandes série

#### ❌ LEDs ne s'allument pas
- Vérifiez la polarité des LEDs
- Contrôlez les résistances (220Ω recommandées)
- Testez les pins avec un multimètre

### Messages de Débogage
Le système affiche des messages détaillés via le port série:
```
=== Train RFID Controller Starting ===
System initialized successfully
RFID Reader self-test passed
RFID Tag detected: 04:52:7E:2A
Arrived at station: Station Centrale
```

## 🛡️ Sécurité

⚠️ **Consignes de Sécurité Importantes:**
- Utilisez des tensions appropriées pour vos moteurs
- Implémentez toujours un arrêt d'urgence
- Utilisez des fusibles pour les circuits moteurs
- Testez soigneusement avant utilisation non supervisée
- Gardez les tags RFID à l'écart des champs magnétiques

## 🔮 Fonctionnalités Avancées

### Extensions Possibles
- **Trains multiples** sur la même voie
- **Aiguillages automatiques** avec servo-moteurs
- **Détection d'obstacles** avec capteurs IR/ultrasoniques
- **Interface web** pour contrôle à distance
- **Enregistrement de données** sur carte SD
- **Éclairage automatique** des trains et stations

### Exemple d'Extension - Capteur d'Obstacle
```cpp
// Ajoutez dans train_config.h:
#define ENABLE_OBSTACLE_DETECTION true
#define ULTRASONIC_TRIG_PIN       11
#define ULTRASONIC_ECHO_PIN       12
#define OBSTACLE_DISTANCE_CM      20
```

## 📊 États du Système

Le système utilise une machine d'états pour gérer le comportement:

```
STOPPED → STARTING → RUNNING → AT_STATION → RUNNING
    ↑                                           ↓
    ←←←←←←←←← EMERGENCY_STOP ←←←←←←←←←←←←←←←←←←←
```

### Indicateurs LED
- **LED Power (Pin 2)** - Toujours allumée quand système actif
- **LED RFID (Pin 3)** - Clignote pendant fonctionnement, flash à la lecture RFID
- **LED Station (Pin 7)** - Allumée quand arrêté en station
- **LED Error (Pin 8)** - Allumée en cas d'erreur ou arrêt d'urgence

## 🤝 Contribution

Les contributions sont les bienvenues! Pour contribuer:
1. Forkez le projet
2. Créez votre branche de fonctionnalité
3. Committez vos changements
4. Poussez vers la branche
5. Ouvrez une Pull Request

## 📄 Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails.

## 🆘 Support

Pour obtenir de l'aide:
1. Consultez la documentation dans [HARDWARE_SETUP.md](HARDWARE_SETUP.md)
2. Vérifiez les messages du moniteur série
3. Ouvrez une issue sur GitHub avec les détails du problème

## 📈 Historique des Versions

### Version 1.0
- ✅ Contrôle de base des trains avec RFID
- ✅ Gestion des stations et arrêts automatiques
- ✅ Interface de contrôle manuel
- ✅ Arrêt d'urgence et sécurité
- ✅ Configuration modulaire

### Prochaines Versions
- 🔄 Support multi-trains
- 🔄 Interface graphique web
- 🔄 Aiguillages automatiques
- 🔄 Système de signalisation
