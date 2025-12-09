#pragma once
#include "snake.h"
#include "field.h"
#include "food.h"
#include <random>
#include <chrono>
#include <thread>
#include <list>
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
            Direction old_direction;
            if (read(STDIN_FILENO, &direction, 1) == 1) {
                if(direction == 'a'){
                old_direction = snake.get_direction();
                snake.change_direction(Direction::LEFT);
                if(snake.get_direction() != old_direction){
                    animate_steering();
                }
                }else if(direction == 'd'){
                    old_direction = snake.get_direction();
                    snake.change_direction(Direction::RIGHT);
                    if(snake.get_direction() != old_direction){
                        animate_steering();
                    }
                }else if(direction == 's'){
                    old_direction = snake.get_direction();
                    snake.change_direction(Direction::DOWN);
                    if(snake.get_direction() != old_direction){
                        animate_steering();
                    }
                }else if(direction == 'w'){
                    old_direction = snake.get_direction();
                    snake.change_direction(Direction::UP);
                    if(snake.get_direction() != old_direction){
                        animate_steering();
                    }
                };
                    
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(175));
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

    void animate_steering(){
        for(Body& body_piece : snake.get_body()){
            snake.move();
            if(food_eaten()){
                snake.eat();
                generate_food();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
            field.fill_tiles(snake,food);
            field.draw();
        }

    }

    bool food_eaten(){
        if(snake.get_x() == food.get_x() && snake.get_y() == food.get_y()){
            return true;                    
        };
        return false;
    }

   


};