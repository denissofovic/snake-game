#pragma once
#include "snake.h"
#include "field.h"
#include "food.h"
#include <random>
#include <chrono>
#include <thread>
#include <list>

class Game{
private:
    Field field;
    Snake snake;
    std::list<Food> food;

public:

    
    void init(uint16_t WIDTH, uint16_t HEIGHT){
        
        field.set_width(WIDTH);
        field.set_height(HEIGHT);
        snake = Snake(field.get_width()/2, field.get_height()/2);

        generate_food();
        food.push_back(Food(25,7));

        field.fill_tiles(snake,food);
        field.draw();

    }

    void loop(){

        while(1){
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            field.fill_tiles(snake,food);
            field.draw();

            char direction;
            std::cin >> direction;

            if(direction == 'a'){
                snake.change_direction(Direction::LEFT);
            }else if(direction == 'd'){
                snake.change_direction(Direction::RIGHT);
            }else if(direction == 's'){
                snake.change_direction(Direction::DOWN);
            }else if(direction == 'w'){
                snake.change_direction(Direction::UP);
            };

            snake.move();

            
            for(Food f: food){
                if(snake.get_x() == f.get_x() && snake.get_y() == f.get_y()){
                    snake.eat();                    
                };
            }


            if(game_over()){
                std::cout << "Game over!";
                break;
            }
                
        }
        
    }



    bool game_over(){
        if(snake.get_x() < 0 || snake.get_x() > field.get_width() || snake.get_y() < 0 || snake.get_y() > field.get_height()){
            return true;
        }
        return false;
    }   

    void generate_food(){
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> rand_int(1, 2);
        std::uniform_int_distribution<> rand_x(2, field.get_width()-2);
        std::uniform_int_distribution<> rand_y(2, field.get_height()-2);
        
        for(int i = 0; i < rand_int(gen); ++i){
            food.push_back(Food(rand_x(gen), rand_y(gen)));
        }
    }
};