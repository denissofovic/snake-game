#pragma once
#include "snake.h"
#include "food.h"

class Field{
private:
    int width = 50;
    int height = 25;
    char tiles[50][25];   
   
public:
    inline constexpr uint16_t get_width(){return width;};
    inline constexpr uint16_t get_height(){return height;};
    void fill_tiles(Snake& snake, Food& food);
    void draw();
       
};