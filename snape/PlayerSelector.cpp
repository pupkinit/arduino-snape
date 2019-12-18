#include "PlayerSelector.h"

PlayerSelector::PlayerSelector(Buttons * buttons, LCD_1602_RUS * lcd) {
  _buttons = buttons;
  _lcd = lcd;
}

Player_Info_t * PlayerSelector::process(Player_Info_t * players, uint8_t players_count) {
  _players = players;
  _players_count = players_count;
  info();
  while (true) {
    _buttons->process();
    if (_buttons->is_down()) {
      _buttons->reset();
      _cur_player = _cur_player + 1;
      if (_cur_player > _players_count - 1) _cur_player = 0;
      info();
    } else if (_buttons->is_up()) {
      _buttons->reset();
      _cur_player = _cur_player - 1;
      if (_cur_player < 0) _cur_player = _players_count - 1;
      info();
    } else if (_buttons->is_right()) {
      _buttons->reset();
      return &_players[_cur_player];
    }
  }
}

void PlayerSelector::info() {
  _lcd->clear();
  _lcd->setCursor(0, 0);
  _lcd->print(_players[_cur_player].name);
  _lcd->setCursor(0, 1);
  _lcd->print("Рекорд: " + String(_players[_cur_player].score));
}
