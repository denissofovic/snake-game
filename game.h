#pragma once
#include "snake.h"
#include "field.h"
#include "food.h"
#include <termios.h>
#include <unistd.h>


class Game{
private:
    Field field;
    Snake snake;
    Food food;
    termios orig_termios;

private:
    bool game_over();
    void generate_food();
    bool food_eaten();
    void disable_raw_mode();
    void enable_raw_mode();
        
public:
    void init();
    void loop();
   
        
};