# Arduino Train RFID Controller - Hardware Setup

## Required Components

### Main Components
- **Arduino Uno/Nano** - Main microcontroller
- **RC522 RFID Reader Module** - For reading RFID tags
- **L298N Motor Driver** - For controlling DC motors
- **DC Motors** (2x) - For train movement
- **RFID Tags** (multiple) - For station identification and train ID
- **LEDs** (4x) - Status indicators
- **Push Buttons** (3x) - Manual controls
- **Resistors** (220Ω for LEDs, 10kΩ for buttons)
- **Breadboard and Jumper Wires**

### Optional Components
- **Buzzer** - Audio feedback
- **LCD Display** - Status display
- **Servo Motors** - For switching tracks
- **Sensors** - IR or ultrasonic for obstacle detection

## Wiring Diagram

### Arduino Pin Assignments

| Component | Arduino Pin | Description |
|-----------|-------------|-------------|
| **RFID RC522** | | |
| SDA/SS | 10 | SPI Slave Select |
| SCK | 13 | SPI Clock |
| MOSI | 11 | SPI Data Out |
| MISO | 12 | SPI Data In |
| IRQ | - | Not used |
| GND | GND | Ground |
| RST | 9 | Reset |
| 3.3V | 3.3V | Power |
| **Motor Driver L298N** | | |
| IN1 | 4 | Motor A Direction 1 |
| IN2 | 5 | Motor A Direction 2 |
| ENA | 6 | Motor A Speed (PWM) |
| IN3 | - | Motor B Direction 1 (if needed) |
| IN4 | - | Motor B Direction 2 (if needed) |
| ENB | - | Motor B Speed (if needed) |
| VCC | 5V/12V | Motor Power |
| GND | GND | Ground |
| **Status LEDs** | | |
| Power LED | 2 | System power indicator |
| RFID LED | 3 | RFID activity indicator |
| Station LED | 7 | At station indicator |
| Error LED | 8 | Error/emergency indicator |
| **Control Buttons** | | |
| Start Button | A0 | Manual start |
| Stop Button | A1 | Manual stop |
| Emergency | A2 | Emergency stop |

### Detailed Wiring Instructions

#### RFID Module (RC522)
```
RC522    Arduino
VCC   -> 3.3V
RST   -> Pin 9
GND   -> GND
IRQ   -> Not connected
MISO  -> Pin 12
MOSI  -> Pin 11
SCK   -> Pin 13
SDA   -> Pin 10
```

#### Motor Driver (L298N)
```
L298N    Arduino    Motor/Power
IN1   -> Pin 4
IN2   -> Pin 5
ENA   -> Pin 6
VCC   -> 5V (for logic) / 12V (for motors)
GND   -> GND
OUT1  -> Motor +
OUT2  -> Motor -
```

#### LED Indicators
```
LED Type    Arduino Pin    Resistor
Power       Pin 2          220Ω
RFID        Pin 3          220Ω
Station     Pin 7          220Ω
Error       Pin 8          220Ω

Connect: Arduino Pin -> Resistor -> LED + -> LED - -> GND
```

#### Control Buttons
```
Button      Arduino Pin    Pull-up Resistor
Start       A0            10kΩ to VCC
Stop        A1            10kΩ to VCC
Emergency   A2            10kΩ to VCC

Connect: VCC -> 10kΩ -> Arduino Pin -> Button -> GND
```

## RFID Tag Configuration

### Station Tags
Configure RFID tags for different stations in your train layout:

| Station | RFID Tag ID | Terminal | Stop Duration |
|---------|------------|----------|---------------|
| Central Station | 04:52:7E:2A | No | 3 seconds |
| North Station | 04:8F:2C:1B | Yes | 5 seconds |
| South Station | 04:A3:5D:4C | Yes | 5 seconds |
| Depot | 04:71:9B:8E | No | 2 seconds |

### Train ID Tags
Use separate RFID tags to identify different trains:
- Train 1: 04:AA:BB:CC
- Train 2: 04:DD:EE:FF
- Maintenance: 04:99:88:77

## Power Supply Requirements

### Arduino Power
- **USB Power**: 5V from computer (for development)
- **External Power**: 7-12V DC adapter (for standalone operation)

### Motor Power
- **Voltage**: 6-12V DC (depending on your motors)
- **Current**: 2-3A capacity recommended
- **Note**: Use separate power supply for motors if they require more than 500mA

## Setup Instructions

1. **Wire the components** according to the diagram above
2. **Install required libraries**:
   - MFRC522 library for RFID
   - SPI library (built-in)
3. **Upload the Arduino sketch** (`train_rfid_controller.ino`)
4. **Configure RFID tags** with station IDs
5. **Test the system**:
   - Check serial monitor for debug output
   - Test manual controls
   - Test RFID tag detection
   - Test motor movement

## Troubleshooting

### Common Issues

#### RFID Not Working
- Check wiring connections
- Verify 3.3V power to RFID module
- Ensure tags are close enough (1-3cm)
- Check serial monitor for RFID self-test results

#### Motors Not Moving
- Verify motor driver connections
- Check power supply voltage/current
- Test with manual commands via serial
- Ensure motor driver enable pins are connected

#### LEDs Not Working
- Check resistor values (220Ω recommended)
- Verify LED polarity (+ to resistor, - to ground)
- Test with simple blink sketch

### Serial Commands for Testing
Open serial monitor at 9600 baud and try these commands:
- `start` - Start the train
- `stop` - Stop the train
- `status` - Show current system status
- `emergency` - Trigger emergency stop
- `reset` - Reset system after emergency

## Safety Considerations

⚠️ **Important Safety Notes:**
- Always use appropriate voltage levels for your motors
- Include emergency stop functionality
- Use proper fuses for motor circuits
- Ensure stable power supply
- Test thoroughly before unsupervised operation
- Keep RFID tags away from magnetic fields
- Use proper wire gauges for motor currents

## Expansion Ideas

### Advanced Features
- **Multiple Trains**: Support for multiple trains on the same track
- **Track Switching**: Servo-controlled track switches
- **Speed Zones**: Different speed limits in different areas
- **Obstacle Detection**: IR or ultrasonic sensors
- **Wireless Control**: WiFi or Bluetooth remote control
- **Data Logging**: SD card logging of train movements
- **Web Interface**: Real-time monitoring via web browser

### Hardware Additions
- **LCD Display**: Show current status and train information
- **Sound Effects**: Train whistle, station announcements
- **Lighting**: Automatic train and station lighting
- **Barriers**: Automatic level crossing barriers
- **Signaling**: Traffic light system for trains