#define LDR_PIN A0
#define SYNC_PIN 7

#define THRESHOLD 50
short char_counter = 8;
char received_char = 0;

// Setup
void setup() {
  Serial.begin(9600);

  pinMode(LDR_PIN, INPUT);
  digitalWrite(LDR_PIN, LOW);

  pinMode(SYNC_PIN, INPUT);
  digitalWrite(SYNC_PIN, LOW);
}

// Main loop
void loop() {
  while (true)
  {
    if (digitalRead(SYNC_PIN) == HIGH) {
      short a_val = analogRead(LDR_PIN);
      int bit_val = a_val < THRESHOLD;
      received_char |= (bit_val << char_counter);

      if (char_counter == 0)
      {
        char c = received_char;
        received_char = 0;
        char_counter = 8;
        a_val = 1024;
        bit_val = 0;
        
        Serial.print(c);
        c = 0;
      }
      char_counter--;
    }
  }
}
