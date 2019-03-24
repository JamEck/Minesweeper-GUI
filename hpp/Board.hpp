#ifndef Board_hpp
#define Board_hpp

#include "Commons.hpp"
#include <SDL2/SDL.h>

struct Tile{
    bool  covered = true;
    bool  flagged = false;
    Uint8 num = 0; // 9 = mine 10 = covered
    
    bool diggable();
};


class Board{
private:
    static std::string rpath;
    static int instances;
    
public:
    static std::vector<SDL_Surface*> tileImg;
    int cols = 0;
    int rows = 0;
    int size = 0;
    
    bool change   = false;
    bool gameover = false;
    
    float tileScale = 1;
    int tileWidth = 1;
    float mineDensity = 10;
    int flagCount = 0;
    
    
    std::vector<Tile> tile;
    
    SDL_Rect shape;
    
    Board(int, int, int);
    ~Board();
    
    void prepBoard();
    void reset();
    void trigGameover();
    void calcTileNums();
    bool checkValidFlags(int,int);
    void setSize (int, int);

    void place(int,int,float);
    
    void display(Window&);
    void print();
    std::pair<int,int> findCursor(EventManager&);
    void update(EventManager&, Window&);
    
    Tile& getTile(int,int);
    Tile& operator[] (int);
    Tile& operator() (int);
    Tile& operator() (int,int);
    
    int map2Dto1D(int,int,int);
    std::pair<int,int> map1Dto2D(int,int);
    
private:
    void loadMineImgs();
    void setMines();
    int  countMineNeighbors(int);
    void flood(int,int);


};




#endif /* Board_hpp */