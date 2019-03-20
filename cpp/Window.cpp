#include "Window.hpp"

Window::Window(){
    
    bool success = true;
    
    win  = SDL_CreateWindow("Test",x,y,w,h,SDL_WINDOW_SHOWN);
    ren  = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(ren);

    surf = SDL_CreateRGBSurface(
        0, w, h, 32,
        0xFF000000,
        0x00FF0000,
        0x0000FF00,
        0x000000FF
     ); // in case you want a surface to manip.
    
    if(win == nullptr){
        printf("Problem Creating Window.\n");
        success = false;
    }
    
    if (ren == nullptr){
        printf("Problem Creating Renderer.\n");
        printf("%s\n", SDL_GetError());
    }
    
    if(surf == nullptr){
        printf("Problem Getting Window Surface.\n");
        printf("%s", SDL_GetError());
    }
    
    if(!ren & !surf) success = false;
    
    if(!success){
        win  = nullptr;
        ren  = nullptr;
        surf = nullptr;
    }
}

Window::~Window(){
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
}

void Window::clear(Uint32 color){
    
    Pixel p(color);
    
    SDL_SetRenderDrawColor(ren, p.r, p.g, p.b, p.a);
    
    SDL_RenderClear(ren);
}