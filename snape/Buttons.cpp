#include "Buttons.h"
#include <Arduino.h>

Buttons::Buttons(uint8_t up_pin, uint8_t down_pin, uint8_t left_pin, uint8_t right_pin) {
  _up_pin = up_pin;
  _down_pin = down_pin;
  _left_pin = left_pin;
  _right_pin = right_pin;
  pinMode(up_pin, INPUT);
  pinMode(down_pin, INPUT);
  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);
}

void Buttons::process() {
  int up = digitalRead(_up_pin);
  int down = digitalRead(_down_pin);
  int left = digitalRead(_left_pin);
  int right = digitalRead(_right_pin);

  if (!_up_pressed && up == LOW) {
    _up_pressed = true;
    _up_time = millis();
  } else if (!_down_pressed && down == LOW) {
    _down_pressed = true;
    _down_time = millis();
  } else if (!_left_pressed && left == LOW) {
    _left_pressed = true;
    _left_time = millis();
  } else if (!_right_pressed && right == LOW) {
    _right_pressed = true;
    _right_time = millis();
  }

  if (_left_pressed && left == HIGH && millis() - _left_time > 100) {
    _left_pressed = false;
    _last_pin = _left_pin;
  } else if (_right_pressed && right == HIGH && millis() - _right_time > 100) {
    _right_pressed = false;
    _last_pin = _right_pin;
  } else if (_up_pressed && up == HIGH && millis() - _up_time > 100) {
    _up_pressed = false;
    _last_pin = _up_pin;
  } else if (_down_pressed && down == HIGH && millis() - _down_time > 100) {
    _down_pressed = false;
    _last_pin = _down_pin;
  }
}

bool Buttons::is_up() {
  return _last_pin == _up_pin;
}

bool Buttons::is_down() {
  return _last_pin == _down_pin;
}

bool Buttons::is_left() {
  return _last_pin == _left_pin;
}

bool Buttons::is_right() {
  return _last_pin == _right_pin;
}

bool Buttons::is_any() {
  return _last_pin != 0;
}

void Buttons::reset() {
  _last_pin = 0;
}
