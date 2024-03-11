// PROOF OF CONCEPT
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
  // bool dl_all_on = true;

void setup() {
  pinMode(WE, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  digitalWrite(WE, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);
  Serial.begin(9600);

  delay(5000);
  write();
}

void loop() {
  read();
}


void write() {
  for (int i : dl) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  delay(10);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);


  digitalWrite(OE, HIGH); // Disable output
  digitalWrite(CE, LOW); // Enable chip
  delay(1); // Wait tCS - Chip Select Setup Time
  digitalWrite(WE, LOW); // Begin write
  delay(1); // Wait tWP - Write Pulse Width
  digitalWrite(WE, HIGH); // End write
  digitalWrite(CE, HIGH); // Disable chip
  digitalWrite(OE, HIGH); // Disable out
}


void read() {
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

  // Print the read byte

}



// void nothing() {
//     t.setInterval([]() {
//     toggle_data_lines();
//   }, 2000);
// }

// void toggle_data_lines() {
//     int write_mode = dl_all_on ? HIGH : LOW; 
//     Serial.println(write_mode);
//     for (int i : dl) {
//     pinMode(i, OUTPUT);
//     digitalWrite(i, write_mode);
//   }

//   dl_all_on = !dl_all_on;
// }