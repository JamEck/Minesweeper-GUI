#include "Commons.hpp"
#include <SDL2/SDL.h>
#include "Board.hpp"
#define FPS 20.0f

bool SDLinit(){
    
    bool issue = false;
    
    if(SDL_Init(SDL_INIT_VIDEO)){
        printf("SDL Video Failed to Initialize.\n");
        issue = true;
    }
    
    return true;
}

void showPoint(Window& win, int y, int x){
    SDL_Rect rec;
    rec.x = x-2;
    rec.y = y-2;
    rec.w = 5;
    rec.h = 5;
    
    Pixel p;
    SDL_GetRenderDrawColor(win.ren, &p.r, &p.g, &p.b, &p.a);
   
    SDL_SetRenderDrawColor(win.ren, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(win.ren,&rec);

    SDL_SetRenderDrawColor(win.ren, p.r, p.g, p.b, p.a);

}

int main(){
    
    srand(time(NULL));
    SDLinit();
    
    float framePeriod = 1000/FPS;
//    std::cout << framePeriod << std::endl;
    Uint32 time = SDL_GetTicks();
    
    Window win;
    EventManager e;
    Board b(10, 10, 20);
    b.place(40, 40,  1);
    
    win.clear(0x007F00FF);
    b.display(win);
    SDL_RenderPresent(win.ren);
    
    std::string rpath = "assets/";
    
    
    // fps limited while loop
    while(!e.quit){ if(SDL_GetTicks() - time > framePeriod){ time = SDL_GetTicks();
//        std::this_thread::sleep_for(std::chrono::milliseconds(17));
        e.checkEvents();
        
        b.update(e, win);
        
        if(b.change){
            win.clear(0x007F00FF);
            b.display(win);
            SDL_RenderPresent(win.ren);
        }
        

    }}
        
    SDL_Quit();
}