#include "Board.hpp"

std::string Tile::rpath  = "assets/";


Board::Board(int width, int height, float dens){
    if(height > 0 && height < 100) h = height;
    if(width  > 0 && width  < 100) w = width;
    
    tiles.assign(w*h, Tile());
}

void Board::setMines(){
    int r = rand();
    for(int i = 0; i < tiles.size(); i++){
        
    }
}