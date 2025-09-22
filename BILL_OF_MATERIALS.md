# Liste de Matériel - Train Automatique RFID

## Composants Essentiels

### Microcontrôleur
- **Arduino Uno R3** ou **Arduino Nano**
  - Quantité: 1
  - Prix approximatif: 15-25€
  - Alternative: ESP32 pour fonctionnalités avancées

### Module RFID
- **Module RFID RC522** 
  - Quantité: 1
  - Prix approximatif: 3-5€
  - Fréquence: 13.56MHz
  - Inclut généralement quelques cartes/tags

### Cartes RFID Supplémentaires
- **Cartes RFID 13.56MHz** ou **Tags RFID**
  - Quantité: 5-10 (pour stations + extras)
  - Prix approximatif: 0.50-1€ par carte
  - Format: Carte crédit ou porte-clés

### Contrôle Moteur
- **Driver Moteur L298N**
  - Quantité: 1
  - Prix approximatif: 3-8€
  - Supporte 2 moteurs DC ou 1 moteur pas-à-pas

### Moteur
- **Moteur DC 6-12V**
  - Quantité: 1
  - Prix approximatif: 5-15€
  - Couple adapté à votre train
  - Alternative: Servo moteur modifié

### Éclairage et Signalisation
- **LEDs 5mm**
  - Rouge: 1x
  - Verte: 1x  
  - Bleue: 1x
  - Prix approximatif: 0.10€ par LED

- **Buzzer Actif 5V**
  - Quantité: 1
  - Prix approximatif: 1-2€

### Résistances
- **Résistances 220Ω**
  - Quantité: 3 (pour les LEDs)
  - Prix approximatif: 0.05€ par résistance

### Connectique
- **Breadboard** (830 points recommandé)
- **Fils Dupont** (mâle-mâle, mâle-femelle)
- **Fils de connexion** variés
- Prix total connectique: 5-10€

### Alimentation
- **Adaptateur 12V 1-2A** (pour le moteur)
- **Connecteur Jack** pour Arduino (optionnel)
- Prix approximatif: 5-10€

## Matériel pour Installation Physique

### Support et Montage
- **Plaque de prototypage** ou **boîtier plastique**
- **Vis et entretoises** M3
- **Support moteur** (selon votre train)

### Outils Nécessaires
- **Fer à souder** et étain (si connexions permanentes)
- **Multimètre** (pour tests)
- **Pince à dénuder**
- **Tournevis** petits

## Budget Total Estimé

| Catégorie | Prix Min | Prix Max |
|-----------|----------|----------|
| Arduino | 15€ | 25€ |
| RFID + Cartes | 8€ | 15€ |
| Moteur + Driver | 8€ | 23€ |
| LEDs + Buzzer | 2€ | 5€ |
| Connectique | 5€ | 10€ |
| Alimentation | 5€ | 10€ |
| **TOTAL** | **43€** | **88€** |

## Fournisseurs Recommandés

### En Ligne
- **Amazon** - Large choix, livraison rapide
- **AliExpress** - Prix compétitifs, délais plus longs
- **GoTronic** - Spécialiste français
- **Adafruit/SparkFun** - Qualité premium

### Magasins Physiques
- **Castorama/Leroy Merlin** - Alimentation et connectique
- **Magasins d'électronique locaux**
- **Fablab/Makerspace** - Souvent équipés

## Notes d'Achat

### Kits Recommandés
Cherchez des "**Arduino Starter Kit**" qui incluent souvent:
- Arduino + breadboard + LEDs + résistances + fils
- Prix: 20-40€ selon le contenu

### Attention aux Compatibilités
- Vérifiez la tension du moteur (6-12V recommandé)
- RFID RC522 fonctionne en 3.3V (fourni par Arduino)
- Cartes RFID: 13.56MHz uniquement

### Économies Possibles
- Achat groupé si plusieurs projets
- Récupération de composants (moteurs, alimentation)
- Fabrication de PCB personnalisé pour version finale

## Extensions Futures

### Améliorations Possibles (+coût)
- **Écran LCD** (5-10€) - Affichage d'informations
- **Module WiFi ESP8266** (3-5€) - Contrôle à distance  
- **Capteurs fin de course** (2-5€) - Sécurité
- **Servomoteurs** (10-15€) - Aiguillages automatiques
- **Module son** (5-10€) - Effets sonores réalistes