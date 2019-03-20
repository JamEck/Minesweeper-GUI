#ifndef Window_hpp
#define Window_hpp

#include "Commons.hpp"
#include <SDL2/SDL.h>

class Window{
public:
    SDL_Window* win = nullptr;
    SDL_Renderer *ren = nullptr;
    SDL_Surface *surf = nullptr;
    
    int x = 100, y = 100;
//    int w = 1200, h = 675;
    int w = 600, h = 480;
    unsigned int length = w*h;
    
    
    Window();
    ~Window();
    
    void clear(Uint32 = 0xFF0000FF);
};

#endif /* Window_hpp */