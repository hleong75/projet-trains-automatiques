# Guide de Dépannage - Train Automatique RFID

## Problèmes Courants et Solutions

### 1. Le code ne se compile pas

#### Erreur: "MFRC522.h: No such file or directory"
**Solution:**
1. Ouvrir l'IDE Arduino
2. Aller dans `Outils > Gérer les bibliothèques`
3. Chercher "MFRC522"
4. Installer la bibliothèque par **GithubCommunity**

#### Erreur: "SPI.h: No such file or directory"  
**Solution:**
- SPI.h est inclus avec Arduino IDE
- Vérifier que vous utilisez Arduino IDE 1.6+ ou Arduino IDE 2.x

### 2. Problèmes de Communication RFID

#### "Communication RFID échouée!" dans le moniteur série
**Causes possibles:**
- Mauvaises connexions SPI
- Alimentation insuffisante  
- Module RFID défaillant

**Solutions:**
1. **Vérifier les connexions:**
   ```
   RC522 -> Arduino
   VCC   -> 3.3V (PAS 5V!)
   GND   -> GND
   RST   -> Pin 9
   SDA   -> Pin 10
   MOSI  -> Pin 11
   MISO  -> Pin 12
   SCK   -> Pin 13
   ```

2. **Tester l'alimentation:**
   - Mesurer 3.3V entre VCC et GND du RC522
   - Vérifier que l'Arduino est bien alimenté

3. **Test avec exemple de base:**
   - Utiliser `rfid_uid_reader.ino` pour tester

#### Les cartes RFID ne sont pas détectées
**Solutions:**
1. **Distance:** Approcher la carte à 1-2cm du lecteur
2. **Type de carte:** Utiliser des cartes 13.56MHz uniquement
3. **Test:** Utiliser `rfid_uid_reader.ino` pour voir si des UIDs s'affichent

### 3. Problèmes de Moteur

#### Le moteur ne tourne pas
**Vérifications:**
1. **Alimentation externe:** Le L298N nécessite une alimentation 6-12V séparée
2. **Connexions:**
   ```
   L298N -> Arduino
   ENA   -> Pin 3 (PWM)
   IN1   -> Pin 4
   VCC   -> 5V Arduino
   GND   -> GND Arduino
   ```
3. **Moteur:** Connecter OUT1 et OUT2 aux bornes du moteur

#### Le moteur tourne dans le mauvais sens
**Solution:**
- Inverser les fils du moteur (OUT1 ↔ OUT2)
- Ou modifier le code: inverser `MOTOR_PIN_1` et `MOTOR_PIN_2`

#### Le moteur est trop lent/rapide
**Solution:**
- Ajuster `MOTOR_SPEED` dans le code (0-255)
- Vérifier la tension d'alimentation du moteur

### 4. Problèmes d'Éclairage

#### Les LEDs ne s'allument pas
**Vérifications:**
1. **Polarité:** LED anode (+) vers pin Arduino, cathode (-) vers GND
2. **Résistances:** Utiliser 220Ω entre pin Arduino et LED
3. **Test:** Utiliser `basic_component_test.ino`

#### Les LEDs sont trop faibles
**Solutions:**
- Vérifier les résistances (220Ω recommandé)
- Tester avec résistances plus faibles (100Ω) prudemment

### 5. Problèmes de Communication Série

#### Rien ne s'affiche dans le moniteur série
**Solutions:**
1. **Vitesse:** Configurer à 9600 bauds
2. **Port:** Sélectionner le bon port COM/ttyUSB
3. **Pilotes:** Installer les pilotes USB de l'Arduino

#### Caractères bizarres dans le moniteur série
**Solution:**
- Vérifier la vitesse (doit être 9600 bauds)

### 6. Comportement Étrange du Train

#### Le train s'arrête en continu
**Causes possibles:**
- Une carte RFID est restée près du lecteur
- Problème de cooldown RFID

**Solutions:**
- Éloigner toutes les cartes du lecteur
- Augmenter `RFID_COOLDOWN` dans le code

#### Le train ne repart pas après un arrêt
**Vérifications:**
1. Vérifier `STOP_DURATION` (3000ms par défaut)
2. Regarder le moniteur série pour les messages d'état
3. Tester avec `basic_component_test.ino`

### 7. Outils de Diagnostic

#### Utilisation du Moniteur Série
```
Outils > Moniteur série (Ctrl+Shift+M)
Configurer à 9600 bauds
```

**Messages importants:**
- `"Module RFID initialisé avec succès"` → RFID OK
- `"Carte RFID détectée: XXXXXXXX"` → Lecture UID
- `"Station X détectée!"` → Station reconnue

#### Scripts de Test
1. **`basic_component_test.ino`** → Test LEDs et buzzer
2. **`rfid_uid_reader.ino`** → Test RFID et lecture UIDs

### 8. Mesures de Sécurité

#### Alimentation
- **Jamais connecter moteur directement à l'Arduino**
- Utiliser un driver moteur (L298N recommandé)
- Alimentation séparée pour le moteur

#### Court-circuits
- Vérifier toutes les connexions avant alimentation
- Utiliser un multimètre pour vérifier la continuité
- Ajouter des fusibles si possible

### 9. Optimisations

#### Performance
- Si le train répond lentement, réduire le `delay(100)` dans la boucle principale
- Augmenter `RFID_COOLDOWN` si trop de lectures parasites

#### Fiabilité
- Ajouter des condensateurs de découplage (100nF) près de chaque composant
- Utiliser des connexions soudées pour la version finale

### 10. Demande d'Aide

#### Informations à fournir
Quand vous demandez de l'aide, incluez:
1. **Message d'erreur complet** du moniteur série
2. **Schéma de connexion** utilisé
3. **Matériel exact** (modèles Arduino, moteur, etc.)
4. **Code modifié** si différent de l'original

#### Communautés utiles
- **Forum Arduino français**
- **Reddit r/arduino**
- **Discord/Telegram Arduino**
- **Fablabs locaux**