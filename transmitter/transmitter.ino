// transmitter microcontroller
//  takes input from a keypad, converts to bits, and blinks
//  an ir led to send data using NEC protocol

// keypad char layout
const char KEYS[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// pinout constants
const int ROWS[4] = {4,5,6,7};
const int COLS[4] = {8,9,10,11};
const int IR_PIN = 3;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode (ROWS[i], OUTPUT);
    digitalWrite (ROWS[i], HIGH);
    pinMode (COLS[i], INPUT_PULLUP);
  }
  //pinMode (IR_PIN, OUTPUT);
}

char scanKeypad() {
  // for each row r:
  for (int r = 0; r < 4; r++) {
  //  write row r LOW
    digitalWrite(ROWS[r], LOW);
  //  for each column c:
    for (int c = 0; c < 4; c++) {
  //    if column c reads LOW:
      if(digitalRead(COLS[c]) == LOW) {
  //      wait 20ms
        delay(20);
  //    while column c still reads LOW: wait
        while (digitalRead(COLS[c]) == LOW);
        digitalWrite(ROWS[r], HIGH);
        return KEYS[r][c];
      }
    }
  //  put row r back HIGH
    digitalWrite(ROWS[r], HIGH);
  }
  // return 0 (nothing pressed)
  return 0;
}

// NEC protocol notes
//  560us on at the start of each bit @ 38kHz carrier burst
//  carrier burst = mark/pulse burst, frequency to filter out 
//    inference
//  logical 1 = 2.25ms total time
//  logical 0 = 1.125ms, 1/2 of 1
//  9ms to mark the start of an address followed by 4.5ms of nothing
//  560us at the end to determine value of last bit
//  command typically transmitted twice, 1st normally and 2nd time 
//    bits are inverted to verify reading of 1st sending
// my use case will have addresses sent as 8 bits

void sendByte(uint8_t b) {
  // send 9000us of 38kHz carrier (start of address/header)
  carrier(9000);
  // nothing for 4.5ms (also header)
  delayMicroseconds(4500);
  // for each bit from bit 7 down to bit 0:
  for (int i = 7; i >= 0; i--) {
  // send 560us of carrier
    carrier(560);
  // if the bit is 1: wait 1690us off
    if (b == 1) {
      delayMicroseconds(2250);
    } else {  // else: wait 565us off
      delayMicroseconds(565);
    }
  }
  // send 560us of carrier (end marker)
  carrier(560);
}

void carrier(int us) {
  // turn the 38kHz tone on 
  tone (IR_PIN, 38000);
  // wait time
  delayMicroseconds(us);
  // turn it off 
  noTone(IR_PIN);
}

void loop() {
  // key = scanKeypad
  char key = scanKeypad();
  // if key is not 0:
  if (key != 0) {
  //  print "sending" key 
    Serial.print("sending ");
    Serial.println(key);
  //  sendByte(key as byte)
    sendByte((uint8_t)key);
  }
  // wait 300ms
  delay(300);
}
