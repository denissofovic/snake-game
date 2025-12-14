#pragma once

class Food{
private:    
    int x;
    int y;
    
public:
    Food(){};
    Food(int x, int y): x{x}, y{y}{};
    inline constexpr int get_x(){return x;};
    inline constexpr int get_y(){return y;};
};