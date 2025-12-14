#include "snake.h"

Snake::Snake(int x, int y){
    head = Body{x,y,Direction::UP};
    body.push_back(head);
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
    head = body[0];   
}

void Snake::change_direction(Direction new_direction){
    if(new_direction != head.direction){
        if( (new_direction == Direction::RIGHT && head.direction == Direction::LEFT) ||  
            (new_direction == Direction::LEFT && head.direction == Direction::RIGHT) ||
            (new_direction == Direction::UP && head.direction == Direction::DOWN) ||
            (new_direction == Direction::DOWN && head.direction == Direction::UP))
            return;
        else
            turns.push_back(Turn{head.x,head.y,new_direction});
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

