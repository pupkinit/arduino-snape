#ifndef PLAYER_SELECTOR_H
#define PLAYER_SELECTOR_H

#include "Buttons.h"
#include <LCD_1602_RUS.h>

typedef struct {
  String name;
  uint8_t score;
} Player_Info_t;

class PlayerSelector {
  public:
    PlayerSelector(Buttons *, LCD_1602_RUS *);
    Player_Info_t * process(Player_Info_t *, uint8_t);
  private:
    Player_Info_t * _players;
    uint8_t _players_count;
    int8_t _cur_player = 0;
    Buttons * _buttons;
    LCD_1602_RUS * _lcd;
    void info();
};

#endif
