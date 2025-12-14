#include "field.h"
#include <list>
#include <iostream>


void Field::fill_tiles(Snake& snake, Food& food){
        for(int y = 0; y < height; ++y){
            for(int x = 0; x < width; ++x){
                tiles[y][x] = ' ';
            }
        }

        for(Body body_piece : snake.get_body()){
            tiles[body_piece.y][body_piece.x] = 'o';
        }
        
        tiles[food.get_y()][food.get_x()] = '.';

}


void Field::draw(){
    std::cout << "\033[2J\033[H"; 
    std::cout << std::string(width+2, 'x') << std::endl;
    for(int y = 0; y < height; ++y){
        std::cout << "x";
        for(int x = 0; x < width; ++x){
            std::cout << tiles[y][x];
        }
        std::cout << "x" << std::endl;
    }
    std::cout << std::string(width+2, 'x') << std::endl;

    std::cout.flush();
}