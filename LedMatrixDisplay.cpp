#include "LedMatrixDisplay.h"


#define _invertRow 0
#define _invertColumn 0

#define DataOutPin 11 // MOSI
#define DataInPin 12 // MISO 
#define SpiClockPin 13 // SCK
#define SpiSlaveSelectPin 10 // SS

#define PwmPhases 1
#define Shades 4
const static short brightnessPatterns[4] = {
  0b0000000000000000,
  0b0000000000000001,
  0b0000000000001111,
  0b1111111111111111,
  };

const static byte shadeDurations[Shades - 1] = {
   1, 4, 16,
};

void printBin(byte value) {
  for (int i = 7; i >= 0; i--) {
    Serial.print((value >> i) & 1);
  }
}

LedMatrixDisplay::LedMatrixDisplay(byte rows, byte columns, byte rowRegisters, byte columnRegisters) { ///, byte dataPin, byte latchPin, byte clockPin) {
  
  //Serial.begin(9600);      // open the serial port at 9600 bps:    
  //delay(100);
//  // Pin setup 
//  _dataPin = dataPin;
//  _latchPin = latchPin;
//  _clockPin = clockPin;
//  pinMode(_latchPin, OUTPUT);
//  digitalWrite(_latchPin, LOW);
//  pinMode(_clockPin, OUTPUT);
//  pinMode(_dataPin, OUTPUT);
////  
////  pinMode(_latchPin-3, OUTPUT);
////  pinMode(_clockPin-3, OUTPUT);
////  pinMode(_dataPin-3, OUTPUT);

  // SPI setup 
  pinMode(SpiSlaveSelectPin, OUTPUT);
  SPI.begin();
  _latchPin = SpiSlaveSelectPin;
  
  // Data 
  _rowRegisters = rowRegisters;
  _columnRegisters = columnRegisters;
  _rows = rows;
  _columns = columns;
  _cells = new byte*[_rows];

  // array for cells with brightness values representing LEDs
  for (int r = 0; r < _rows; r++) {
    _cells[r] = new byte[_columns];
    for (int c = 0; c < _columns; c++) {
      _cells[r][c] = 0;
    }
  }

  // array for raw bytes sent out to shift registers at every iteration
  _rawColumnBits = new byte**[Shades - 1]; // 3
  for (int s = 0; s < Shades - 1; s++) {
    _rawColumnBits[s] = new byte*[_rows]; // 6
    for (int r = 0; r < _rows; r++) {
      _rawColumnBits[s][r] = new byte[_columnRegisters]; // 5
    }
  }
  _rawRowBits = new byte*[_rows]; // 6
  for (int r = 0; r < _rows; r++) {
    _rawRowBits[r] = new byte[_rowRegisters]; // 1
  }
  
  // pre-populate row bits 
  unsigned long rowBit = 1; 
  for (int r = 0; r < _rows; r++, rowBit <<= 1) {
    unsigned long regByte = rowBit;
    for (int rreg = _rowRegisters - 1; rreg >= 0; rreg--, regByte >>= 8) {
      _rawRowBits[r][rreg] = (byte)regByte;
    }
  }
}

void LedMatrixDisplay::clear() {
  for (int r = 0; r < _rows; r++) {
    memset(_cells[r], 0, _columns * sizeof(byte));
  }
}

void LedMatrixDisplay::set(byte row, byte column, byte value) {
  if (row >= 0 && row < _rows && column >= 0 && column < _columns) {
    _cells[row][column] = value;
  }
}

byte LedMatrixDisplay::get(byte row, byte column) {
  if (row >= 0 && row < _rows && column >= 0 && column < _columns) {
    return _cells[row][column];
  }
  return 0;
}

unsigned long lastMicros = 0;
unsigned long stopwatchStartTimes[10];
unsigned long stopwatchValues[10];

unsigned long loopRepeats = 0;

void swstart(int index) {
  stopwatchStartTimes[index] = micros();
}

void swstop(int index) {
  stopwatchValues[index] += micros() - stopwatchStartTimes[index];
}

long swreset(int index) {
  stopwatchStartTimes[index] = micros();
  stopwatchValues[index] = 0;
}

long swget(int index) { 
  return stopwatchValues[index]; 
}

#define fullLoopStopwatch 0
#define latchOffStopwatch 1
#define statsStopwatch 2
#define shiftOutStopwatch 3
#define displayOutStopwatch 4


void LedMatrixDisplay::render() {
  
//  // print rows
//  for (int r = 0; r < _rows; r++) {
//    for (int i = 0; i < _rowRegisters; i++) {
//      printBin(_rawRowBits[r][i]);
//      Serial.print(' ');
//    }
//    Serial.println();
//  }
//  Serial.println();
  
  for (int s = 0; s < Shades - 1; s++) {
    for (int r = 0; r < _rows; r++) {
      for (int creg = _columnRegisters - 1, cc = 0; creg >= 0; creg--, cc += 8) {
        byte regBits = 0;
        for (int c = cc; c < cc + 8 && c < _columns; c++) { // up to 8 columns for this register
          byte v = _cells[r][c];
          if (s < v) { // v=1 visible in s=0; v=2 visible in s=0,1; v=3 visible in all s=0,1,2
            regBits |= (1 << (c - cc));
          }
        }
        _rawColumnBits[s][r][creg] = regBits;
      }
    }
  }

//  // print columns
//  for (int s = 0; s < Shades - 1; s++) {
//    for (int r = 0; r < _rows; r++) {
//      for (int i = 0; i < _rowRegisters; i++) {
//        printBin(_rawRowBits[r][i]);
//        Serial.print(' ');
//      }
//      Serial.print(' ');
//      for (int i = 0; i < _columnRegisters; i++) {
//        printBin(_rawColumnBits[s][r][i]);
//        Serial.print(' ');
//      }
//      Serial.println();
//    }
//    Serial.println();
//  }
//
//  Serial.println(_rows);
//  Serial.println(_columns);
}


void LedMatrixDisplay::renderLoop() {

//  digitalWrite(_latchPin, LOW);
  SPI.beginTransaction(SPISettings(50000000, MSBFIRST, SPI_MODE0));
  
  for (int rr = 0; rr < _rowRegisters; rr++) {
    SPI.transfer(_rawRowBits[_renderRow][rr]);
  }
  
  for (int cr = 0; cr < _columnRegisters; cr++) {
    SPI.transfer(_rawColumnBits[_renderShadeLayer][_renderRow][cr]);
  }
  
  SPI.endTransaction();

  digitalWrite(_latchPin, LOW);
  digitalWrite(_latchPin, HIGH);


  if (--_renderShadeLayerTicksRemaining > 0) 
    return;  
  
  if (++_renderShadeLayer >= Shades - 1) {
    _renderShadeLayer = 0;
    if (++_renderRow >= _rows) {
      _renderRow = 0;
    }
  }
  _renderShadeLayerTicksRemaining = shadeDurations[_renderShadeLayer];

}

//
//void LedMatrixDisplay::set(Cell cell, bool fill) {
//  // Current implementation can only fill cells after full clear().
//  // fill == false will be ignored. 
//  
//  set(cell.r, cell.c, fill ? ON : OFF);
//  if (!fill)
//    return;
//      
//  for (byte s = 0; s < 6; s++) {
//    CellProjection p = projectOnSide(cell, s);
//    
//  }
//  
//}




