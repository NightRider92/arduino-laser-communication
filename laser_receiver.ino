#define LDR_PIN A0
#define SYNC_PIN 7

#define THRESHOLD 50
#define ORIGINAL_PULSE_TIME 11855

short pulse_time = ORIGINAL_PULSE_TIME;
int char_counter = 0;

// Receive data
char receive() {
  char received_char = 0;
  for (int i = 7; i >= 0; i--) {
    short a_val = analogRead(LDR_PIN);
    int bit_val = a_val < THRESHOLD;
    received_char |= (bit_val << i);
    delayMicroseconds(pulse_time);
  }
  return received_char;
}

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
  char c = 0;
  
  // Read actual message
  do {
    if (digitalRead(SYNC_PIN) == 1) {
       c = receive();
       char_counter++;
       if(char_counter > 25) 
       {
        pulse_time-=4;
        char_counter = 0;
       }
       if(c != '`' &&  c!='@'){Serial.print(c);}
    } 
  } while (c != '\0');

  pulse_time = ORIGINAL_PULSE_TIME;
}
