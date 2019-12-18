#include "GameSelector.h"
#include "PlayerSelector.h"
#include "Field.h"
#include "Game.h"

#define dataPin  2
#define latchPin 3
#define clockPin 4

#define upPin    6
#define downPin  7
#define leftPin  8
#define rightPin 9

#define PLAYERS_COUNT 5
Player_Info_t players[][PLAYERS_COUNT] = {
  {
    {"Андрей", 54},
    {"Катя",   17},
    {"Максим", 2},
    {"Папа",   64},
    {"Мама",   19},
  },
  {
    {"Андрей", 1},
    {"Катя",   1},
    {"Максим", 1},
    {"Папа",   90},
    {"Мама",   1},
  }
};

//#define LCD_PORT 0x27
#define LCD_PORT 0x38

Buttons buttons(upPin, downPin, leftPin, rightPin);
Field field(dataPin, latchPin, clockPin);
LCD_1602_RUS lcd(LCD_PORT, 16, 2);
GameSelector gameSelector(&buttons, &lcd);
PlayerSelector playerSelector(&buttons, &lcd);
Game game(&buttons, &lcd, &field);

void setup() {
  lcd.init();
  lcd.backlight();
  field.clear();
  field.draw();
}

void loop() {
  uint8_t game_type = gameSelector.process();
  Player_Info_t * player = playerSelector.process(players[game_type], PLAYERS_COUNT);
  uint8_t score = game.process(game_type, player->name);
  // выводим рекорд, если есть
  if (player->score < score) {    
    lcd.setCursor(0, 1);
    lcd.print("Рекорд! " + String(score) + "          ");
    player->score = score;
  }
  // мигаем полем
  unsigned long flash_time = millis();
  while (millis() - flash_time < 5000) {
    field.flash();
  }
  lcd.setCursor(0, 1);
  lcd.print("Нажмите кнопку");
  // ждем кнопку и мигаем полем
  buttons.reset();
  while (!buttons.is_any()) {
      buttons.process();
      field.flash();
  }
  buttons.reset();
  field.clear();
}
