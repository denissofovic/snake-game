#include "snake.h"
#include <iostream>

Snake::Snake(int x, int y){
    std::cout << "snake init" << std::endl;
    body.push_back(Body{x,y,Direction::UP});
}

void Snake::move(){
    for(Body& body_piece : body){
        for(Turn& turn : turns){
            if(body_piece.x == turn.x && body_piece.y == turn.y){
                body_piece.direction = turn.direction; 
                if(body_piece.x == body.back().x && body_piece.y == body.back().y){
                    turns.pop_front();
                }
            }
        }
            body_piece.move();
    }
}

void Snake::change_direction(Direction new_direction){
    if(new_direction != body[0].direction){
        if( (new_direction == Direction::RIGHT && body[0].direction == Direction::LEFT) ||  
            (new_direction == Direction::LEFT && body[0].direction == Direction::RIGHT) ||
            (new_direction == Direction::UP && body[0].direction == Direction::DOWN) ||
            (new_direction == Direction::DOWN && body[0].direction == Direction::UP))
            return;
        else
            turns.push_back(Turn{body[0].x,body[0].y,new_direction});
    }  
}

void Snake::eat(){
    Body tail = body.back();
    int tail_x = tail.x;
    int tail_y = tail.y;
    int new_x;
    int new_y;

    if(tail.direction == Direction::UP){
        new_x = tail_x;
        new_y = tail_y + 1;
    }else if(tail.direction == Direction::DOWN){
        new_x = tail_x;
        new_y = tail_y - 1;
    }else if(tail.direction == Direction::LEFT){
        new_x = tail_x + 1;
        new_y = tail_y;
    }else{
        new_x = tail_x - 1;
        new_y = tail_y;
    }

    body.push_back(Body{new_x,new_y,tail.direction});
}

