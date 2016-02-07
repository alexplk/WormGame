#import "SegmentDisplay.h"

const static byte segmentDisplayDigits[10] = {
  0b11111100,
  0b01100000,
  0b11011010,
  0b11110010,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11100110,
};


SegmentDisplay::SegmentDisplay(byte groundPin, byte vccPin, byte dataPin, byte latchPin, byte clockPin) {
  init(groundPin, vccPin, dataPin, latchPin, clockPin);
}

SegmentDisplay::SegmentDisplay(byte dataPin, byte latchPin, byte clockPin) {
  init(0, 0, dataPin, latchPin, clockPin);
}

SegmentDisplay::SegmentDisplay(byte firstPinGround) {
  init(firstPinGround, firstPinGround + 1, firstPinGround + 2, firstPinGround + 3, firstPinGround + 4);
}

void SegmentDisplay::init(byte groundPin, byte vccPin, byte dataPin, byte latchPin, byte clockPin) {
  _groundPin = groundPin;
  _vccPin = vccPin;
  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;

  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);

  if (_groundPin != 0) {
    pinMode(_groundPin, OUTPUT);
    digitalWrite(_groundPin, LOW); 
  }
  if (_vccPin != 0) {
    pinMode(_vccPin, OUTPUT);
    analogWrite(_vccPin, HIGH);
  }
}

void SegmentDisplay::writeNumber(int number) {
  digitalWrite(_latchPin, LOW);

  // shift the bits out:
  shiftOut(_dataPin, _clockPin, LSBFIRST, segmentDisplayDigits[number % 10]);
  number /= 10;
  shiftOut(_dataPin, _clockPin, LSBFIRST, segmentDisplayDigits[number % 10]);
  
  // turn on the output so the LEDs can light up:
  //analogWrite(_latchPin, HIGH / 10);
  digitalWrite(_latchPin, HIGH);
}
