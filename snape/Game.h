#ifndef GAME_H
#define GAME_H

#include "Buttons.h"
#include <LCD_1602_RUS.h>
#include "Field.h"

class Game {
  public:
    Game(Buttons *, LCD_1602_RUS *, Field *);
    uint8_t process(uint8_t, String player);
  private:
    uint8_t _game_type;
    String _player;
    Buttons * _buttons;
    LCD_1602_RUS * _lcd;
    Field * _field;
    void info();
    void place_fruit();
    uint8_t score;
};

#endif
