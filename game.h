#pragma once
#include "snake.h"
#include "field.h"
#include "food.h"
#include <random>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>

class Game{
private:
    Field field;
    Snake snake;
    Food food;
    termios orig_termios;
     void disable_raw_mode() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    void enable_raw_mode() {
        tcgetattr(STDIN_FILENO, &orig_termios);
        termios raw = orig_termios;
        raw.c_lflag &= ~(ICANON | ECHO);    
        raw.c_cc[VMIN] = 0;                 
        raw.c_cc[VTIME] = 0;                

        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }


public:
    void init(uint16_t WIDTH, uint16_t HEIGHT){
        enable_raw_mode();
        field.set_width(WIDTH);
        field.set_height(HEIGHT);
        snake = Snake(field.get_width()/2, field.get_height()/2);
        generate_food();
        field.fill_tiles(snake,food);
        field.draw();
    }

    void loop(){
        while(1){
            char direction;
            if (read(STDIN_FILENO, &direction, 1) == 1) {
                if(direction == 'a'){
                    snake.change_direction(Direction::LEFT);
                }else if(direction == 'd'){
                    snake.change_direction(Direction::RIGHT); 
                }else if(direction == 's'){
                    snake.change_direction(Direction::DOWN);  
                }else if(direction == 'w'){
                    snake.change_direction(Direction::UP);
                };      
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            field.fill_tiles(snake,food);
            field.draw();
            snake.move();

            if(food_eaten()){
                snake.eat();
                generate_food();
            }
            
            if(game_over()){
                std::cout << "Game over!";
                break;
            }             
        }   
    }

    bool game_over(){
        auto body = snake.get_body();
        for(int i = 1; i < body.size(); ++i){
            if(body[0].x == body[i].x && body[0].y == body[i].y)
                return true;
        }
        if(snake.get_x() < 0 || snake.get_x() > field.get_width()-1 || snake.get_y() < 0 || snake.get_y() > field.get_height()-1){
            return true;
        }
        return false;
    }   

    void generate_food(){
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> rand_x(2, field.get_width()-2);
        std::uniform_int_distribution<> rand_y(2, field.get_height()-2);
        food = Food(rand_x(gen), rand_y(gen));      
    }

    bool food_eaten(){
        if(snake.get_x() == food.get_x() && snake.get_y() == food.get_y()){
            return true;                    
        };
        return false;
    }

   


};