#ifndef Board_hpp
#define Board_hpp

#include "Commons.hpp"
#include <SDL2/SDL.h>

class Tile{
private:
    static std::string rpath;

public:

    bool  covered = false;
    Uint8 num = 0;
    int x = 0;
    int y = 0;
    
    SDL_Surface* img = nullptr;
    
};


class Board{
public:
    int w = 20;
    int h = 20;
    float tileScale = 1;
    float mineDensity = 10;
    
    std::vector<Tile> tiles;
    
    Board(int, int, float);
    
    void setMines();
    void populate();
    
};





#endif /* Board_hpp */