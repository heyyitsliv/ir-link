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
const int COLS[4] = {8.9.10.11};
const IR_PIN = 3;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode (ROWS[i], OUTPUT);
    digitalWrite (ROWS[i], HIGH);
    pinMode (COLS[i], INPUT_PULLUP);
  }
  pinMode (IR_PIN, OUTPUT);
}

void loop() {
  // key = scanKeypad
  // if key is not 0:
  //  print "sending" key
  //  sendByte(key as byte)
  // wait 300ms
}

char scanKeypad() {
  // for each row r:
  //  write row r LOW
  //  for each column c:
  //    if column c reads LOW:
  //      wait 20ms
  //    while column c still reads LOW: wait
  //  put row r back HIGH
  // return 0 (nothing pressed)
}

// NEC protocol notes
//  560us on at the start of each bit @ 38kHz carrier burst
//  carrier burst = mark/pulse burst, frequency to filter out 
//    inference
//  logical 1 = 2.25ms
//  logical 0 = 1.125ms, 1/2 of 1
//  9ms to mark the start of an address followed by 4.5ms of nothing
//  560us at the end to determine value of last bit
//  command typically transmitted twice, 1st normally and 2nd time 
//    bits are inverted to verify reading of 1st sending
// my use case will have addresses sent as 8 bits

void sendByte() {
  // send 9000us of 38kHz carrier (start of address/header)
  // nothing for 4.5ms
  // for each bit from bit 7 down to bit 0:
  // send 560us of carrier
  // if the bit is 1: wait 1690us off
  // else: wait 560us off
  // send 560us of carrier (end marker)
}

carrier(time)
  // turn the 38kHz tone on
  // wait time
  // turn it off
