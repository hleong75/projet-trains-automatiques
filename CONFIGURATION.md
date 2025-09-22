# Configuration du Système de Train Automatique

## Paramètres par défaut

### Vitesse et timing
- Vitesse du moteur: 150 (sur 255)
- Durée d'arrêt en station: 3000ms (3 secondes)
- Cooldown RFID: 2000ms (2 secondes)

### Pins Arduino
```
RFID RC522:
- RST: Pin 9
- SS/SDA: Pin 10
- MOSI: Pin 11 (SPI)
- MISO: Pin 12 (SPI)
- SCK: Pin 13 (SPI)

Moteur:
- PWM: Pin 3
- Direction: Pin 4

LEDs:
- Verte (marche): Pin 5
- Rouge (arrêt): Pin 6
- Bleue (station): Pin 7

Signalisation:
- Buzzer: Pin 8
```

### UIDs RFID par défaut
```cpp
Station 1: {0xDE, 0xAD, 0xBE, 0xEF}
Station 2: {0xCA, 0xFE, 0xBA, 0xBE}
Station 3: {0x12, 0x34, 0x56, 0x78}
```

## Personnalisation

Pour personnaliser votre système:

1. **Identifier vos cartes RFID:**
   - Utilisez le script `rfid_uid_reader.ino`
   - Notez les UIDs affichés
   - Remplacez les valeurs dans `stationUIDs[]`

2. **Ajuster la vitesse:**
   - Modifiez `MOTOR_SPEED` (0-255)
   - Testez avec votre moteur spécifique

3. **Modifier les temps d'arrêt:**
   - Changez `STOP_DURATION` (en millisecondes)
   - Ajustez selon vos besoins

4. **Ajouter des stations:**
   - Augmentez `NUM_STATIONS`
   - Ajoutez des UIDs dans le tableau `stationUIDs`

## Schéma de Circuit (ASCII)

```
Arduino Uno                    RC522 RFID
+-------------+               +----------+
|         3V3 |<------------->| VCC      |
|         GND |<------------->| GND      |
|       Pin 9 |<------------->| RST      |
|      Pin 10 |<------------->| SDA/SS   |
|      Pin 11 |<------------->| MOSI     |
|      Pin 12 |<------------->| MISO     |
|      Pin 13 |<------------->| SCK      |
|             |               +----------+
|             |
|             |               L298N Motor Driver
|             |               +----------+
|       Pin 3 |<------------->| ENA      |
|       Pin 4 |<------------->| IN1      |
|         5V  |<------------->| VCC      |
|         GND |<------------->| GND      |
|             |               | OUT1     |<---> Moteur +
|             |               | OUT2     |<---> Moteur -
|             |               +----------+
|             |
|             |               LEDs (avec résistances 220Ω)
|       Pin 5 |<---[220Ω]----->| LED Verte
|       Pin 6 |<---[220Ω]----->| LED Rouge  
|       Pin 7 |<---[220Ω]----->| LED Bleue
|             |
|             |               Buzzer
|       Pin 8 |<------------->| Buzzer +
|         GND |<------------->| Buzzer -
+-------------+
```

## Alimentation

- **Arduino:** 5V via USB ou jack d'alimentation
- **RFID RC522:** 3.3V (fourni par l'Arduino)
- **Moteur:** 12V externe (via L298N)
- **LEDs et Buzzer:** 5V (fourni par l'Arduino)

**Important:** Le moteur nécessite une alimentation externe. Ne pas alimenter un moteur puissant directement depuis l'Arduino.