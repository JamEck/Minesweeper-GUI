#include "EventManager.hpp"


    
void MouseManager::setPos(int x, int y){
        pos.x = x;
        pos.y = y;
}

void MouseManager::clearTriggers(){
    leftClickTrig = false;
    rightClickTrig = false;
}

void MouseManager::checkPos(SDL_Event& e){
    if(e.type == SDL_MOUSEMOTION){
        setPos(e.motion.x, e.motion.y);
    }
}
void MouseManager::checkClick(SDL_Event& e){
    if(e.type == SDL_MOUSEBUTTONDOWN ||
       e.type == SDL_MOUSEBUTTONUP){
        if(e.button.button == SDL_BUTTON_LEFT){
            leftClick = e.type == SDL_MOUSEBUTTONDOWN;
            leftClickTrig = true;
        }
        if(e.button.button == SDL_BUTTON_RIGHT){
            rightClick = e.type == SDL_MOUSEBUTTONDOWN;
            rightClickTrig = true;
        }
    }
}
void MouseManager::update(SDL_Event& e){
    checkPos(e);
    checkClick(e);
}


KeyboardManager::KeyboardManager(){
    ks.assign(sizeof(bind)/4, ButtonState());
    setBindings();
}

void KeyboardManager::setBindings(){
    for(int i = 0; i < ks.size(); i++){
        ks[i].keycode = ((Uint32*)(&bind))[i];
    }
}

void KeyboardManager::clearTriggers(){
    for(int i = 0; i < ks.size(); i++){
        ks[i].trig = false;
    }
    change = false;
}

void KeyboardManager::update(SDL_Event& e){
    //if either key is pressed or released
    if(e.type == SDL_KEYDOWN | e.type == SDL_KEYUP){
        change = false;
    
    // check against all key bindings
        for(int i = 0; i < ks.size(); i++){
    
    // if event keycode = key[i]'s keycode, and ignore rapid press
            if(ks[i].keycode == e.key.keysym.scancode &&
               ks[i].held != (e.key.type == SDL_KEYDOWN)){
                
                //record timestamp
                ks[i].timestamp = e.key.timestamp;
                
                // held matches truth of key event type being a press
                ks[i].held = e.key.type == SDL_KEYDOWN;
                
                // key events are only triggered on press and release frames
                ks[i].trig = true;
                
                change = true; // there has been a change
            }
        }
    }
}

ButtonState& KeyboardManager::getStateOf(Uint32& bttn){
    Uint32* lower = (Uint32*)&bind;
    Uint32* upper = lower + sizeof(bind);
    Uint32* inp   = (Uint32*)&bttn;
    
    
    if(inp >= lower && inp <= upper){
        Uint32 i = (inp - lower);
        return ks[i];
    }
    
    printf("Not a Valid Input.\n");
    return ks[0];
}

ButtonState& KeyboardManager::operator[] (Uint32& inp){
    return getStateOf(inp);
}

void KeyboardManager::printButtons(){
    printf("triggers:\t");

    for(int i = 0; i < ks.size(); i++){
        std::cout << ks[i].trig << " ";
    }
    printf("\nheld:\t\t");

    for(int i = 0; i < ks.size(); i++){
        std::cout << ks[i].held << " ";
    }
    printf("\n");
}


void EventManager::checkEvents(){
    k.clearTriggers();
    mouse.clearTriggers();
    
    while(SDL_PollEvent(&e)){
        
        
        
        k.update(e);
        
        
        mouse.update(e);
        
        
        if(e.type == SDL_QUIT || k.ks[0].trig)
            quit = true;
    }
    
//    if(k.change) k.printButtons();

}


