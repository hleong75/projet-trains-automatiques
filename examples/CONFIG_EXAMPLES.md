# Exemples de Configuration pour Train RFID

Ce dossier contient des exemples de configuration pour différents types de layouts de trains.

## Configuration Simple (1 Ligne)

### Layout: Central ←→ Terminal Nord ←→ Terminal Sud
```cpp
// Configuration pour un layout simple avec 3 stations
const StationConfig SIMPLE_LAYOUT[] = {
  {
    "04:52:7E:2A",     // Tag RFID
    "Station Centrale", // Nom
    false,              // Pas un terminal
    3000,               // 3 secondes d'arrêt
    150,                // Vitesse d'approche
    true                // Annonce
  },
  {
    "04:8F:2C:1B",
    "Terminal Nord",
    true,               // Terminal - inversion direction
    5000,               // 5 secondes d'arrêt
    80,                 // Approche lente
    true
  },
  {
    "04:A3:5D:4C",
    "Terminal Sud",
    true,
    5000,
    80,
    true
  }
};
```

## Configuration Métro (Multiple Stations)

### Layout: Ligne de métro avec 6 stations
```cpp
const StationConfig METRO_LAYOUT[] = {
  {"04:11:22:33", "Châtelet", false, 2000, 120, true},
  {"04:44:55:66", "République", false, 2000, 120, true},
  {"04:77:88:99", "Bastille", false, 2000, 120, true},
  {"04:AA:BB:CC", "Nation", true, 4000, 80, true},
  {"04:DD:EE:FF", "Vincennes", true, 6000, 60, true}
};

// Vitesses spéciales pour métro
#define METRO_CRUISE_SPEED    200
#define METRO_STATION_SPEED   100
#define METRO_TERMINAL_SPEED  60
```

## Configuration Freight (Train de Marchandises)

### Layout: Dépôt ←→ Usine ←→ Port
```cpp
const StationConfig FREIGHT_LAYOUT[] = {
  {
    "04:F1:F2:F3",
    "Dépôt Central",
    false,
    5000,               // Arrêt long pour chargement
    80,                 // Approche très lente
    false               // Pas d'annonce
  },
  {
    "04:F4:F5:F6",
    "Zone Industrielle",
    false,
    8000,               // 8 secondes pour chargement/déchargement
    60,
    false
  },
  {
    "04:F7:F8:F9",
    "Port Maritime",
    true,
    10000,              // 10 secondes au port
    40,                 // Très lent près de l'eau
    false
  }
};

// Configuration train de marchandises
#define FREIGHT_MAX_SPEED     150   // Plus lent que trains passagers
#define FREIGHT_CRUISE_SPEED  100
#define FREIGHT_ACCEL_DELAY   100   // Accélération plus lente
```

## Configuration Touristique

### Layout: Circuit touristique avec points d'intérêt
```cpp
const StationConfig TOURIST_LAYOUT[] = {
  {
    "04:T1:T2:T3",
    "Gare Principale",
    false,
    4000,
    100,
    true
  },
  {
    "04:T4:T5:T6",
    "Château",
    false,
    6000,               // Arrêt long pour visite
    60,                 // Vitesse touristique
    true
  },
  {
    "04:T7:T8:T9",
    "Lac Panoramique",
    false,
    8000,               // Arrêt très long pour photos
    40,
    true
  },
  {
    "04:TA:TB:TC",
    "Village Historique",
    true,
    10000,              // Terminus - visite prolongée
    30,
    true
  }
};

// Sons touristiques
#define ENABLE_SCENIC_SOUNDS  true
#define PHOTO_STOP_DURATION   15000  // 15 secondes aux points photo
```

## Configuration Multi-Trains

### Layout: 2 trains sur la même voie avec évitement
```cpp
// Configuration pour train express
const TrainConfig EXPRESS_TRAIN = {
  "04:EX:PR:ES",
  "Train Express",
  255,                  // Vitesse max
  220,                  // Vitesse croisière élevée
  true,                 // Éclairage
  false                 // Pas de sirène
};

// Configuration pour train local
const TrainConfig LOCAL_TRAIN = {
  "04:LO:CA:L1",
  "Train Local",
  180,                  // Vitesse max réduite
  120,                  // Vitesse croisière modérée
  true,                 // Éclairage
  false
};

// Stations avec voies d'évitement
const StationConfig MULTI_TRAIN_LAYOUT[] = {
  {
    "04:M1:M2:M3",
    "Gare Centrale",
    false,
    3000,
    100,
    true
  },
  {
    "04:M4:M5:M6",
    "Station Évitement", // Station avec voie de garage
    false,
    5000,               // Temps pour évitement
    80,
    true
  },
  {
    "04:M7:M8:M9",
    "Terminal Express",
    true,
    4000,
    60,
    true
  }
};

// Paramètres de sécurité multi-trains
#define MIN_TRAIN_SEPARATION  30000   // 30 secondes entre trains
#define ENABLE_COLLISION_AVOIDANCE true
```

## Configuration de Test/Débogage

### Layout minimal pour tests
```cpp
const StationConfig TEST_LAYOUT[] = {
  {
    "04:99:99:99",
    "Test Station A",
    false,
    1000,               // Arrêts courts pour tests rapides
    200,
    false
  },
  {
    "04:88:88:88",
    "Test Station B",
    true,
    1000,
    200,
    false
  }
};

// Paramètres de test
#define TEST_MODE             true
#define FAST_TESTING          true
#define DEBUG_VERBOSE         true
#define SHORT_STATION_STOPS   1000
#define QUICK_ACCELERATION    true
```

## Instructions d'Utilisation

### Pour utiliser une configuration:

1. **Copiez la configuration** désirée dans votre fichier `train_config.h`
2. **Remplacez** `DEFAULT_STATIONS` par votre nouveau layout
3. **Ajustez** `NUM_DEFAULT_STATIONS` avec le bon nombre
4. **Modifiez** les vitesses selon vos préférences
5. **Programmez** vos tags RFID avec les IDs correspondants

### Exemple d'intégration:
```cpp
// Dans train_config.h, remplacez:
const StationConfig DEFAULT_STATIONS[] = METRO_LAYOUT;
const int NUM_DEFAULT_STATIONS = sizeof(METRO_LAYOUT) / sizeof(METRO_LAYOUT[0]);

// Et ajustez les vitesses:
#define CRUISE_SPEED METRO_CRUISE_SPEED
```

## Personnalisation Avancée

### Créer votre propre layout:

1. **Mesurez** les distances entre stations
2. **Chronométrez** les temps de parcours
3. **Testez** les vitesses d'approche optimales
4. **Ajustez** les durées d'arrêt selon l'usage
5. **Documentez** votre configuration pour référence future

### Outils utiles:
- Utilisez `rfid_test.ino` pour identifier vos tags
- Utilisez `motor_test.ino` pour calibrer les vitesses
- Testez avec des arrêts courts au début
- Augmentez progressivement les vitesses