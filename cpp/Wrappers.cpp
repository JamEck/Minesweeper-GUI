#include "Wrappers.hpp"


Rect::Rect(){
    sdl.x =  0; sdl.y =  0;
    sdl.w = 50; sdl.h = 50;
}

Rect::Rect(int width, int height){
    sdl.x =     0; sdl.y =      0;
    sdl.w = width; sdl.h = height;
}

Rect::Rect(int width, int height, int posx, int posy){
    sdl.x =  posx; sdl.y =   posy;
    sdl.w = width; sdl.h = height;
}

Rect::Rect(std::pair<int,int> size, std::pair<int,int> pos){
    sdl.x =  pos.first; sdl.y =  pos.second;
    sdl.w = size.first; sdl.h = size.second;
}

void Rect::setPos(int x, int y, bool both){
    if(both){
        sdl.x = x;
        sdl.y = y;
    }else{
        sdl.x = (x>0)?x:sdl.x;
        sdl.y = (y>0)?y:sdl.y;
    }
}

void Rect::setSize(int w, int h){
    sdl.w = (w>0)?w:sdl.w;
    sdl.h = (h>0)?h:sdl.h;
}


Pixel::Pixel(Uint32 color){
    breakInt(color);
}

void Pixel::breakInt(Uint32 color){
    a = color & 0xFF; color >>= 8;
    b = color & 0xFF; color >>= 8;
    g = color & 0xFF; color >>= 8;
    r = color & 0xFF;
}