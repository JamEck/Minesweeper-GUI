//
//  Wrappers.hpp
//  MinesweeperSDL
//
//  Created by James Eckdahl on 3/18/19.
//  Copyright © 2019 James Eckdahl. All rights reserved.
//

#ifndef Wrappers_hpp
#define Wrappers_hpp

#include "commons.hpp"
#include <SDL2/SDL.h>

class Rect{
public:
    SDL_Rect sdl;
    Rect();
    Rect(int,int);
    Rect(int,int,int,int);
    
    Rect(std::pair<int,int>,std::pair<int,int>);
    
    void setPos(int, int, bool both = true);
    
    void setSize(int w, int);
};


class Pixel{
public:
    Uint8 r = 0x00;
    Uint8 g = 0x00;
    Uint8 b = 0x00;
    Uint8 a = 0xFF;
    
    Pixel(){}
    Pixel(Uint32);
    
    
    void breakInt(Uint32);
};


#endif /* Wrappers_hpp */
