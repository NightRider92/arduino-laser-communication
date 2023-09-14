#define LASER_SIGNAL_PIN 7
#define SYNC_PIN 8
#define LSB_MASK 0x01
#define PULSE_TIME 12000

String message = "";

// Transmit data over laser
void transmit(char c) {
  digitalWrite(SYNC_PIN, 1);
  delayMicroseconds(5);

  for (int i = 7; i >= 0; i--) {
    uint8_t bin = c >> i & LSB_MASK; // Get digit by digit (0 or 1)
    digitalWrite(LASER_SIGNAL_PIN, bin); // and transmit it over laser
    delayMicroseconds(PULSE_TIME);
  }

  delayMicroseconds(5);
  digitalWrite(SYNC_PIN, 0);
}

// Setup
void setup() {
  Serial.begin(9600);
  pinMode(LASER_SIGNAL_PIN, OUTPUT);

  pinMode(SYNC_PIN, OUTPUT);
  digitalWrite(SYNC_PIN, LOW);
}

// Main loop
void loop() {
  while (Serial.available() == 0) {}
  message = Serial.readString();
  message.trim();

  if (message == "LASER.ON")
  {
    digitalWrite(LASER_SIGNAL_PIN, HIGH);
    return;
  }
  else if (message == "LASER.OFF")
  {
    digitalWrite(LASER_SIGNAL_PIN, LOW);
    return;
  }
  Serial.println("Transmitting message: ");
  Serial.print(message);
  Serial.print("\n");;

  // Add termination
  message += '\0';

  // Calibration
  for (short i = 0; i < 25; i++)
  {
    char c = '@';
    transmit(c);
  }

  // Actual message transmit
  for (size_t i = 0; i < message.length(); i++) {
    char c = message.charAt(i);
    transmit(c);
  }

  // Set laser pin to low after transmitting and wait 5 seconds
  digitalWrite(LASER_SIGNAL_PIN, LOW);
}
