#pragma once
#include <iostream>

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Body{
private:
    uint16_t x;
    uint16_t y;
    Direction direction;
public:
    Body(uint16_t x, uint16_t y):x{x}, y{y}, direction{Direction::UP}{};
    inline const uint16_t get_x(){return x;};
    inline const uint16_t get_y(){return y;};
    inline const Direction get_direction(){return direction;};

    inline void set_x(uint16_t x){this->x = x;};
    inline void set_y(uint16_t y){this->y = y;};

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
    uint16_t head_x;
    uint16_t head_y;
    std::vector<Body> body;
    Direction direction;
    uint16_t x_chg;
    uint16_t y_chg;
public:
    Snake(){};
    Snake(uint16_t x, uint16_t y): head_x{x}, head_y{y}, direction{Direction::UP}, x_chg{3000}, y_chg{3000}{
        body.push_back(Body(x, y+1));
        body.push_back(Body(x, y+2));
        body.push_back(Body(x, y+3));

    };

    inline const uint16_t get_x(){return head_x;};
    inline const uint16_t get_y(){return head_y;};
    inline const Direction get_direction(){return direction;};
    inline const std::vector<Body>& get_body(){return body;};
    inline void set_x(uint16_t x){this->head_x = x;};
    inline void set_y(uint16_t y){this->head_y = y;};

    void move(){
        if(direction == Direction::UP) --(this->head_y);
        else if(direction == Direction::DOWN) ++(this->head_y);
        else if(direction == Direction::RIGHT) ++(this->head_x);
        else --(this->head_x);
        for(Body& body_piece : body){
            if(body_piece.get_x() == x_chg && body_piece.get_y() == y_chg){
                body_piece.change_direction(direction);
            }
            body_piece.move();
        }

    }

    void change_direction(Direction new_direction){
        if(new_direction != direction){
            x_chg = head_x;
            y_chg = head_y;
            direction = new_direction;
        }
        
        
    }

    void eat(){
        Body tail = body.back();
        uint16_t tail_x = tail.get_x();
        uint16_t tail_y = tail.get_y();
        uint16_t new_x;
        uint16_t new_y;

        if(tail.get_direction() == Direction::UP){
            new_x = tail_x;
            new_y = tail_y + 1;
        }else if(tail.get_direction() == Direction::DOWN){
            new_x = tail_x;
            new_y = tail_y + 1;
        }else if(tail.get_direction() == Direction::LEFT){
            new_x = tail_x + 1;
            new_y = tail_y;
        }else{
            new_x = tail_x - 1;
            new_y = tail_y;
        }

        body.push_back(Body(new_x,new_y));
    }

    
};