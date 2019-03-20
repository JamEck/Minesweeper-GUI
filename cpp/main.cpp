#include "Commons.hpp"
#include <SDL2/SDL.h>
#include "Window.hpp"
#include "EventManager.hpp"
#include <thread>
#define FPS 60.0f

bool SDLinit(){
    
    bool issue = false;
    
    if(SDL_Init(SDL_INIT_VIDEO)){
        printf("SDL Video Failed to Initialize.\n");
        issue = true;
    }
    
    return true;
}

void blitToWindow(Window& win, SDL_Surface* surf, int x, int y, float scale = 1.0){
    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(win.ren,surf);
    if(tex == nullptr){
        printf("Could Not Generate Texture.\n");
        return;
    }

    Rect dest(surf->w*scale, surf->h*scale, x, y);
    
    SDL_RenderCopy(win.ren, tex, NULL, &dest.sdl);
    SDL_DestroyTexture(tex);
}


int main(){
    
    srand(time(NULL));
    SDLinit();
    
    float framePeriod = 1000/FPS;
    std::cout << framePeriod << std::endl;
    Uint32 time = SDL_GetTicks();
    
    Window win;
    EventManager e;
    
    std::string rpath = "assets/";
    
    
    // 60 fps while loop
    while(!e.quit){ if(SDL_GetTicks() - time > framePeriod){ time = SDL_GetTicks();
//        std::this_thread::sleep_for(std::chrono::milliseconds(17));
        e.checkEvents();
        
        win.clear(0x007F00FF);


        {
            SDL_Surface* tile = SDL_LoadBMP((rpath+"tile5.bmp").c_str());
            blitToWindow(win, tile, 100, 100, 2);
            SDL_FreeSurface(tile);
        }
        
        if(e.mouse.leftClickTrig){
            SDL_Surface* tile = SDL_LoadBMP((rpath + "tile1.bmp").c_str());
            blitToWindow(win, tile, e.mouse.pos.x, e.mouse.pos.y, 3.3);
            SDL_FreeSurface(tile);
        }
        if(e.mouse.rightClickTrig){
            SDL_Surface* tile = SDL_LoadBMP((rpath + "tile2.bmp").c_str());
            blitToWindow(win, tile, e.mouse.pos.x, e.mouse.pos.y, 3.3);
            SDL_FreeSurface(tile);
        }
        
        {
            SDL_Surface* tile = SDL_LoadBMP((rpath + "mine.bmp").c_str());
            blitToWindow(win, tile, e.mouse.pos.x-tile->w*3.3, e.mouse.pos.y-tile->h*3.3, 3.3);
            SDL_FreeSurface(tile);
        }
        
        SDL_RenderPresent(win.ren);
    
    }}
        
    SDL_Quit();
}