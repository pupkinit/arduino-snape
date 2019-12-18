#ifndef GAME_SELECTOR_H
#define GAME_SELECTOR_H

#include "Buttons.h"
#include <LCD_1602_RUS.h>

class GameSelector {
  public:
    GameSelector(Buttons *, LCD_1602_RUS *);
    uint8_t process();
  private:
    int8_t _cur_game = 0;
    Buttons * _buttons;
    LCD_1602_RUS * _lcd;
    void info();
};

#endif
