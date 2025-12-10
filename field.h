#pragma once
#include <iostream>
#include<list>
#include "snake.h"
#include "food.h"

class Field{
private:
    uint16_t WIDTH = 50;
    uint16_t HEIGHT = 25;
    char tiles[25][50];   
   
public:
    inline const uint16_t get_width(){return WIDTH;};
    inline const uint16_t get_height(){return HEIGHT;};
    inline void set_width(uint16_t width){this->WIDTH = width;};
    inline void set_height(uint16_t height){this->HEIGHT = height;};

    void fill_tiles(Snake& snake, Food& food){
        for(int y = 0; y < HEIGHT; ++y){
            for(int x = 0; x < WIDTH; ++x){
                tiles[y][x] = ' ';
            }
        }
        for(Body body_piece : snake.get_body()){
            tiles[body_piece.y][body_piece.x] = 'o';
        }
        tiles[food.get_y()][food.get_x()] = '.';
    }

    void draw(){
        for(int i = 0; i < HEIGHT; ++i) std::cout << std::endl;    
        std::cout << std::string(WIDTH+2, 'x') << std::endl;
        for(int y = 0; y < HEIGHT; ++y){
            std::cout << "x";
            for(int x = 0; x < WIDTH; ++x){
                std::cout << tiles[y][x];
            }

            std::cout << "x" << std::endl;
        }
        std::cout << std::string(WIDTH+2, 'x') << std::endl;
        for(int i = 0; i < HEIGHT; ++i) std::cout << std::endl;
    }
    
};