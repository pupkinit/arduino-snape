#ifndef FIELD_H
#define FIELD_H

#include <inttypes.h>

#define WIDTH 8
#define HEIGHT 8

class Field {
  public:
    Field(uint8_t, uint8_t, uint8_t);
    void draw();
    void flash();
    void set(uint8_t, uint8_t, uint8_t);
    uint8_t get(uint8_t, uint8_t);
    void clear();
  private:
    uint8_t _dataPin;
    uint8_t _latchPin;
    uint8_t _clockPin;
    uint8_t _field[8][8];
    uint8_t _tick;
    void _draw(bool);
};

#endif
