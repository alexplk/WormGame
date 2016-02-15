#include "Keypad.h"


// How many shift register chips are daisy-chained.
#define NUMBER_OF_SHIFT_CHIPS   1

// Width of data (how many ext lines).
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

// Width of pulse to trigger the shift register to read and latch.
#define PULSE_WIDTH_USEC   5

// Optional delay between shift register reads.
#define POLL_DELAY_MSEC   1


//void Keypad::attach(byte pins[KeyCount]) {
//  for (int i = 0; i < KeyCount; i+) {
//    _pins[i] = pins[i];
//    pinMode(_pins[i], OUTPUT);
//  }
//}

Keypad::Keypad(byte ploadPin, byte clockEnablePin, byte dataPin, byte clockPin) {
  _ploadPin = ploadPin;
  _clockEnablePin = clockEnablePin;
  _dataPin = dataPin;
  _clockPin = clockPin;
//  _lastKeyPressMillis = 0;

  pinMode(_ploadPin, OUTPUT);
  pinMode(_clockEnablePin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, INPUT);

  digitalWrite(clockPin, LOW);
  digitalWrite(ploadPin, HIGH);
}

bool Keypad::isPressed(byte key) {
  return (_lastState & key) != 0;
}
  
bool Keypad::readKey(byte key) { 
  
}

byte Keypad::readShiftRegisters()
{
    long bitVal;
    byte bytesVal = 0;

    // Trigger a parallel Load to latch the state of the data lines,
    digitalWrite(_clockEnablePin, HIGH);
    digitalWrite(_ploadPin, LOW);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(_ploadPin, HIGH);
    digitalWrite(_clockEnablePin, LOW);

    // Loop to read each bit value from the serial out line
    // of the SN74HC165N.
    for(int i = 0; i < DATA_WIDTH; i++)
    {
        bitVal = digitalRead(_dataPin);

        // Set the corresponding bit in bytesVal.
        bytesVal |= (bitVal << ((DATA_WIDTH-1) - i));

        // Pulse the Clock (rising edge shifts the next bit).
        digitalWrite(_clockPin, HIGH);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWrite(_clockPin, LOW);
    }
    _lastState = bytesVal;
    return bytesVal;
}

