#include "Field.h"
#include <Arduino.h>

Field::Field(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin) {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;
}

void Field::draw() {
  _draw(false);
}

void Field::flash() {
  _draw(true);
}

void Field::_draw(bool flash) {
  _tick = _tick + 1;
  for (uint8_t row = 0; row < HEIGHT; row++) {
    int row_byte = 0;
    for (uint8_t col = 0; col < WIDTH; col++) {
      if (_field[row][col] > 0) {
        if (_field[row][col] == 1 && (_tick / 10) % 2 == 0) { // голова питона мигает быстро
          continue;
        }
        if (_field[row][col] == 100 && (_tick / 80) % 2 == 0) { // фрукт мигает медленно
          continue;
        }
        if (flash && _field[row][col] < 100 && (_tick / 100) % 2 == 0) { // мигаем змейкой
          continue;
        }
        row_byte = row_byte | (1 << col);   
      }
    }
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, MSBFIRST, ~ (1 << row));
    shiftOut(_dataPin, _clockPin, MSBFIRST, row_byte);
    digitalWrite(_latchPin, HIGH);
  }  
}

void Field::set(uint8_t y, uint8_t x, uint8_t value) {
  _field[y][x] = value;
}

uint8_t Field::get(uint8_t y, uint8_t x) {
  return _field[y][x];
}

void Field::clear() {
  for (uint8_t row = 0; row < HEIGHT; row++) {
    for (uint8_t col = 0; col < WIDTH; col++) {
      _field[row][col] = 0;;
    }
  }
}
