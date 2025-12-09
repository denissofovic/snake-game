#pragma once

class Food{
private:    
    uint16_t x;
    uint16_t y;
    
public:
    Food(uint16_t x, uint16_t y): x{x}, y{y}{};
    inline const uint16_t get_x(){return x;};
    inline const uint16_t get_y(){return y;};
    inline void set_x(uint16_t x){this->x = x;};
    inline void set_y(uint16_t y){this->y = y;};
};