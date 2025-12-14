#pragma once
#include<vector>
#include<deque>

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Turn{
    int x;
    int y;
    Direction direction;
};


struct Body{
    int x;
    int y;
    Direction direction;
   
    inline void move(){
        if(direction == Direction::UP)--(this->y);
        else if(direction == Direction::DOWN) ++(this->y);
        else if(direction == Direction::RIGHT) ++(this->x);
        else --(this->x);
    }

};


class Snake{
private: 
    std::vector<Body> body;
    std::deque<Turn> turns;   

public:
    Snake(){};
    Snake(int x, int y);

    inline constexpr int get_x(){return body[0].x;};
    inline constexpr int get_y(){return body[0].y;};
    inline constexpr Direction get_direction(){return body[0].direction;};
    inline std::vector<Body>& get_body(){return body;};

    void move();
    void change_direction(Direction new_direction);
    void eat();
        
    

    
};