#ifndef BUTTONS_H
#define BUTTONS_H

#include <inttypes.h>

class Buttons {
  public:
    Buttons(uint8_t, uint8_t, uint8_t, uint8_t);
    void process();
    bool is_up();
    bool is_down();
    bool is_left();
    bool is_right();
    bool is_any();
    void reset();

  private:
    uint8_t _up_pin;
    uint8_t _down_pin;
    uint8_t _left_pin;
    uint8_t _right_pin;
    uint8_t _last_pin;

    bool _up_pressed = false;
    bool _down_pressed = false;
    bool _left_pressed = false;
    bool _right_pressed = false;

    unsigned long _up_time;
    unsigned long _down_time;
    unsigned long _left_time;
    unsigned long _right_time;
};

#endif
