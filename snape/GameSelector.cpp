#include "GameSelector.h"

GameSelector::GameSelector(Buttons * buttons, LCD_1602_RUS * lcd) {
  _buttons = buttons;
  _lcd = lcd;
}

uint8_t GameSelector::process() {
  info();
  while (true) {
    _buttons->process();
    if (_buttons->is_down()) {
      _buttons->reset();
      _cur_game = _cur_game + 1;
      if (_cur_game > 1) _cur_game = 0;
      info();
    } else if (_buttons->is_up()) {
      _buttons->reset();
      _cur_game = _cur_game - 1;
      if (_cur_game < 0) _cur_game = 1;
      info();
    } else if (_buttons->is_right()) {
      _buttons->reset();
      return _cur_game;
    }
  }
}

void GameSelector::info() {
  _lcd->clear();
  _lcd->setCursor(0, 0);
  _lcd->print("Тип игры");
  _lcd->setCursor(0, 1);
  if (_cur_game == 0) _lcd->print("Рост");
  if (_cur_game == 1) _lcd->print("Ускорение");
}
