#pragma once
#include <iostream>

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Turn{
    uint16_t x;
    uint16_t y;
    Direction direction;
    Turn(uint16_t x, uint16_t y, Direction direction): x{x}, y{y}, direction{direction}{};
};


struct Body{
    uint16_t x;
    uint16_t y;
    Direction direction;
    Body(){};
    Body(uint16_t x, uint16_t y, Direction direction):x{x}, y{y}, direction{direction}{};
    void move(){
        if(direction == Direction::UP)--(this->y);
        else if(direction == Direction::DOWN) ++(this->y);
        else if(direction == Direction::RIGHT) ++(this->x);
        else --(this->x);
    }

    void change_direction(Direction new_direction){
        direction = new_direction;
    }
};

class Snake{
private: 
    std::vector<Body> body;
    Body head;
    std::deque<Turn> turns;   

public:
    Snake(){};
    Snake(uint16_t x, uint16_t y){
        body.push_back(Body(x, y, head.direction));
        body.push_back(Body(x, y+1, head.direction));
        body.push_back(Body(x, y+2, head.direction));
        body.push_back(Body(x, y+3, head.direction));
        head = body[0];
    };

    inline const uint16_t get_x(){return head.x;};
    inline const uint16_t get_y(){return head.y;};
    inline const Direction get_direction(){return head.direction;};
    inline std::vector<Body>& get_body(){return body;};
    

    void move(){
        for(Body& body_piece : body){
            for(Turn& turn : turns){
                if(body_piece.x == turn.x && body_piece.y == turn.y){
                    body_piece.change_direction(turn.direction); 
                    if(body_piece.x == body.back().x && body_piece.y == body.back().y){
                        turns.pop_front();
                    }
                }

            }
                  body_piece.move();
        }
        head = body[0];     
    }

    void change_direction(Direction new_direction){
        if(new_direction != head.direction){
            if( (new_direction == Direction::RIGHT && head.direction == Direction::LEFT) ||  
                (new_direction == Direction::LEFT && head.direction == Direction::RIGHT) ||
                (new_direction == Direction::UP && head.direction == Direction::DOWN) ||
                (new_direction == Direction::DOWN && head.direction == Direction::UP))
                return;
            else
                turns.push_back(Turn(head.x,head.y,new_direction));
        }  
    }

    void eat(){
        Body tail = body.back();
        uint16_t tail_x = tail.x;
        uint16_t tail_y = tail.y;
        uint16_t new_x;
        uint16_t new_y;

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

        body.push_back(Body(new_x,new_y,tail.direction));
    }

    
};