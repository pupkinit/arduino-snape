#include "Game.h"

Game::Game(Buttons * buttons, LCD_1602_RUS * lcd, Field * field) {
  _buttons = buttons;
  _lcd = lcd;
  _field = field;
}

uint8_t Game::process(uint8_t game_type, String player) {
  randomSeed(analogRead(0));
  _game_type = game_type;
  _player = player;
  _field->clear();
  // ставим питона в исходную позицию
  if (_game_type == 0) {
    _field->set(4, 0, 2);
    _field->set(4, 1, 1);
  }
  if (_game_type == 1) {
    _field->set(4, 0, 3);
    _field->set(4, 1, 2);
    _field->set(4, 2, 1);
  }
  // ставим фрукт в случайном месте
  place_fruit();
  // длина змейки 2
  if (_game_type == 0) {
    score = 2;
  }
  // первая скорость
  if (_game_type == 1) {
    score = 1;
  }
  unsigned long step_time = millis();
  char direction = 'E'; // идем на восток
  _lcd->clear();
  info();
  while (true) {
    _buttons->process();
    int pause_time = 1000;
    if (_game_type == 1) pause_time = pause_time - score;
    if (millis() - step_time > pause_time) {
      if (_buttons->is_up() && direction != 'S') {
        direction = 'N';
      } else if (_buttons->is_down() && direction != 'N') {
        direction = 'S';
      } else if (_buttons->is_left() && direction != 'E') {
        direction = 'W';
      } else if (_buttons->is_right() && direction != 'W') {
        direction = 'E';
      }
      // ищем голову и хвост
      int8_t head_x, head_y, tail_x, tail_y;
      for (uint8_t row = 0; row < HEIGHT; row++) {
        for (uint8_t col = 0; col < WIDTH; col++) {
          if (_field->get(row, col) == 1) {
            // нашли голову
            head_x = col;
            head_y = row;
          }
          if (_game_type == 0 && _field->get(row, col) == score
              || _game_type == 1 && _field->get(row, col) == 3) {
            // нашли хвост
            tail_x = col;
            tail_y = row;
          }
        }
      }
      // пытаемся подвинуть голову
      if (direction == 'N') head_y++;
      else if (direction == 'S') head_y--;
      else if (direction == 'W') head_x--;
      else if (direction == 'E') head_x++;
     // проверяем границы и саму змейку
      if (head_y < 0 || head_y == HEIGHT || head_x < 0 || head_x == WIDTH || _field->get(head_y, head_x) > 0 && _field->get(head_y, head_x) < 100) {
        return score;
      } else if (_field->get(head_y, head_x) == 100) { // съели фрукт
        // свободных клеток больше нет
        if (score == HEIGHT * WIDTH - 1) {
          return score + 1;
        }
        if (_game_type == 1) _field->set(tail_y, tail_x, 0); // змейка не растет
        // ставим новый фрукт
        place_fruit();
        // съедаем фрукт
        _field->set(head_y, head_x, 0);
        score++; // увеличиваем длину/скорость
        info();
      } else {
        // подчищаем хвост, т.к. фрукт не съели
        _field->set(tail_y, tail_x, 0);
      }
      // передвигаем тело
      for (uint8_t row = 0; row < HEIGHT; row++) {
        for (uint8_t col = 0; col < WIDTH; col++) {
          if (_field->get(row, col) > 0 && _field->get(row, col) < 100) {
            _field->set(row, col, _field->get(row, col) + 1);
          }
        }
      }
      // ставим голову
      _field->set(head_y, head_x, 1);
      step_time = millis();
    }
    _field->draw();
  }
}

void Game::info() {
  _lcd->setCursor(0, 0);
  _lcd->print(_player);
  _lcd->setCursor(0, 1);
  if (_game_type == 0) {
    _lcd->print("Длина: " + String(score));
  }
  if (_game_type == 1) {
    _lcd->print("Скорость: " + String(score));
  }
}

void Game::place_fruit() {
  bool placed = false;
  while (!placed) {
    uint8_t x = random(HEIGHT);
    uint8_t y = random(WIDTH);
    if (_field->get(x, y) > 0) continue;
    _field->set(x, y, 100);
    placed = true;
  }
}
