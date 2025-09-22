# Schémas de Câblage - Train RFID Arduino

## Schéma de Base

```
Arduino Uno                    RC522 RFID Module
=============                  =================
3.3V        ←------------------→ VCC
Pin 9       ←------------------→ RST
GND         ←------------------→ GND
Pin 12      ←------------------→ MISO
Pin 11      ←------------------→ MOSI
Pin 13      ←------------------→ SCK
Pin 10      ←------------------→ SDA

Arduino Uno                    L298N Motor Driver
=============                  ==================
Pin 4       ←------------------→ IN1
Pin 5       ←------------------→ IN2
Pin 6       ←------------------→ ENA
5V          ←------------------→ VCC (Logic)
GND         ←------------------→ GND

L298N Motor Driver             DC Motor
==================             ========
OUT1        ←------------------→ Motor +
OUT2        ←------------------→ Motor -
12V Input   ←------------------→ External 12V Power Supply

Arduino Uno                    LEDs + Resistors
=============                  ================
Pin 2       ←---[220Ω]--------→ LED Power + → LED - → GND
Pin 3       ←---[220Ω]--------→ LED RFID + → LED - → GND
Pin 7       ←---[220Ω]--------→ LED Station + → LED - → GND
Pin 8       ←---[220Ω]--------→ LED Error + → LED - → GND

Arduino Uno                    Boutons + Pull-up
=============                  ===================
Pin A0      ←---[10kΩ]--- 5V   Button Start → Pin A0 → GND
Pin A1      ←---[10kΩ]--- 5V   Button Stop → Pin A1 → GND
Pin A2      ←---[10kΩ]--- 5V   Button Emergency → Pin A2 → GND
```

## Schéma Détaillé ASCII

```
                            ARDUINO UNO
                    ┌─────────────────────────┐
                    │                         │
         3.3V ──────┤ 3.3V                VIN ├────── 12V External
          GND ──────┤ GND                 GND ├────── GND
                    │                         │
     RC522 RST ─────┤ 9                    13 ├───── RC522 SCK
    RC522 SDA ──────┤ 10                   12 ├───── RC522 MISO
                    │ 11                   11 ├───── RC522 MOSI
                    │                         │
     Motor IN1 ─────┤ 4                    A0 ├───── Start Button
     Motor IN2 ─────┤ 5                    A1 ├───── Stop Button
     Motor ENA ─────┤ 6                    A2 ├───── Emergency Button
    Station LED ────┤ 7                    A3 ├───── (Reserved)
      Error LED ────┤ 8                    A4 ├───── (Reserved)
                    │                         │
      Power LED ────┤ 2                    A5 ├───── (Reserved)
       RFID LED ────┤ 3                     5V├───── L298N VCC
                    └─────────────────────────┘

                    L298N MOTOR DRIVER MODULE
                ┌─────────────────────────────────┐
                │  [12V]  [GND]  [5V]             │
                │    │     │     │               │
   12V Ext ─────────┘     │     └─── Arduino 5V │
   GND ─────────────────────┘                    │
                │                                │
                │  [IN1] [IN2] [IN3] [IN4]       │
   Arduino Pin 4───┘                            │
   Arduino Pin 5────────┘                       │
                │                                │
                │  [ENA] [ENB]                   │
   Arduino Pin 6───┘                            │
                │                                │
                │  [OUT1][OUT2][OUT3][OUT4]      │
                │    │    │                     │
                └────┼────┼─────────────────────┘
                     │    │
            ┌────────┘    └─────────┐
            │                      │
            ▼                      ▼
      ┌──────────┐           ┌──────────┐
      │ DC MOTOR │           │ Optional │
      │  (Train) │           │ 2nd Motor│
      └──────────┘           └──────────┘

                     RC522 RFID MODULE
                ┌─────────────────────────┐
                │  [3.3V][RST][GND]       │
                │    │    │   │           │
   Arduino 3.3V────┘    │   └─── Arduino GND
   Arduino Pin 9────────┘               │
                │                        │
                │  [IRQ][MISO][MOSI][SCK]│
                │   │     │     │    │   │
         Not Used───┘     │     │    └── Arduino Pin 13
         Arduino Pin 12───┘     │       │
         Arduino Pin 11─────────┘       │
                │                        │
                │  [SDA]                 │
   Arduino Pin 10──┘                    │
                └────────────────────────┘

                   STATUS LED INDICATORS
    ┌──[220Ω]──(LED)──┐    ← Power LED (Green)
Pin 2                 GND
    
    ┌──[220Ω]──(LED)──┐    ← RFID Activity LED (Blue)
Pin 3                 GND
    
    ┌──[220Ω]──(LED)──┐    ← Station LED (Yellow)
Pin 7                 GND
    
    ┌──[220Ω]──(LED)──┐    ← Error LED (Red)
Pin 8                 GND

                    CONTROL BUTTONS
     5V──[10kΩ]──┬──Pin A0     ← Start Button
                 │
                Button──GND

     5V──[10kΩ]──┬──Pin A1     ← Stop Button
                 │
                Button──GND

     5V──[10kΩ]──┬──Pin A2     ← Emergency Button
                 │
                Button──GND
```

## Alimentation

### Option 1: USB + Alimentation Externe (Recommandée)
```
USB Port → Arduino (Logique)
12V PSU → L298N (Moteurs)
```

### Option 2: Alimentation Unique
```
12V PSU → L298N VIN
L298N 5V Out → Arduino VIN
```

## Connexions Optionnelles

### Buzzer (Pin A3)
```
Pin A3 ──[100Ω]── Buzzer + ── Buzzer - ── GND
```

### Écran LCD 16x2 (I2C)
```
Arduino SDA (A4) ──── LCD SDA
Arduino SCL (A5) ──── LCD SCL
5V ──────────────────── LCD VCC
GND ─────────────────── LCD GND
```

### Capteur Ultrasonique HC-SR04
```
Pin 11 ───── Trig
Pin 12 ───── Echo
5V ──────── VCC
GND ────── GND
```

## Notes de Sécurité

⚠️ **IMPORTANT:**
- Utilisez des fusibles sur l'alimentation moteur
- Vérifiez la polarité avant de connecter
- Ne dépassez pas 12V pour les moteurs
- Utilisez des fils adaptés au courant moteur (≥ 1A)
- Connectez toujours les masses ensemble (GND commun)

## Liste de Courses

### Composants Électroniques
- Arduino Uno R3
- Module RFID RC522
- Driver Moteur L298N
- LEDs: 1x Verte, 1x Bleue, 1x Jaune, 1x Rouge
- Résistances: 4x 220Ω, 3x 10kΩ
- Boutons poussoirs: 3x
- Breadboard et fils jumper
- Alimentation 12V 2A

### Matériel Mécanique
- Moteurs DC 6-12V
- Châssis train miniature
- Rails ou guides
- Tags RFID (5-10 pièces minimum)
- Vis et supports de fixation