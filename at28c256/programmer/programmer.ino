// PROOF OF CONCEPT
// Using an arduino with at least 12 io lines
// Address lines will have to manual switches since I don't have a bigger board, which isn't very functional, but could look pretty sick https://www.digikey.com/en/products/detail/cit-relay-and-switch/ANT11SEBQE/12503360
// Might as well make the data lines manual as well 
// Programmer for at28c256 eeprom
  int WE = 13;
  int OE = 2;
  int CE = 12;
  int D0 = 3;
  int D1 = 4;
  int D2 = 5;
  int D3 = 6;
  int D4 = 7;
  int D5 = 8;
  int D6 = 9;
  int D7 = 10;

  int dl [] = {D0, D1, D2, D3, D4, D5, D6, D7};
void setup() {
  pinMode(WE, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  digitalWrite(WE, HIGH); // Start with the eeprom off (Active Low)
  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);
  Serial.begin(9600);

  delay(5000); // Arduino does some wacky stuff when it starts, setting a delay to let everything settle before writing
  write();
}

void loop() {
  read();
}

void write() {
  for (int i : dl) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  } // Make sure all data lines are off before beginning a write
  delay(10);
  digitalWrite(D0, HIGH); // This will be replaced by some code that reads the manual data lines switches since the add lines will be manual anyway, for now just hardcoding the write as a pof
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);

  digitalWrite(OE, HIGH); // Disable output
  digitalWrite(CE, LOW); // Enable chip
  delay(1); // Chip Enable Setup Time
  digitalWrite(WE, LOW); // Begin write
  delay(1); // Write Pulse Width
  digitalWrite(WE, HIGH); // End write
  digitalWrite(OE, HIGH); // Disable out
  digitalWrite(CE, HIGH); // Disable chip
}

void read() { // Could make a switch to toggle read mode... 
  byte data = 0; // Variable to store the read byte
  for (int i : dl) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  delay(10);
  // // Set data lines to input
  for (int i: dl) {
    digitalWrite(i, LOW);
    pinMode(i, INPUT);
  }
  delay(10);
  // Begin read sequence
  digitalWrite(WE, HIGH); // Disable writing
  digitalWrite(OE, LOW); // Enable output
  digitalWrite(CE, LOW); // Enable chip
  delay(1); // Small delay to allow signals to settle and data to become valid
  // Read all data lines
  for (int i = 0; i < 8; i++) {
    if (digitalRead(dl[i])) {
      data |= (1 << i);
    }
  }
  // End read sequence
  digitalWrite(CE, HIGH); // Disable chip
  digitalWrite(OE, HIGH); // Disable output
}
