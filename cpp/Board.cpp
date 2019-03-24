#include "Board.hpp"


bool Tile::diggable (){return covered && !flagged;}

std::string Board::rpath = "assets/";
std::vector<SDL_Surface*> Board::tileImg = std::vector<SDL_Surface*>();
int Board::instances = 0;

Board::Board(int height, int width, int dens){
    if(Board::instances==0)
        loadMineImgs();
    mineDensity = dens;
    setSize(width, height);
    prepBoard();
    Board::instances++;
}

Board::~Board(){
    if(--Board::instances == 0){
        for(int i = 0; i < Board::tileImg.size(); i++){
            SDL_FreeSurface(tileImg[i]);
        }
    }
}

void Board::reset(){
    gameover = false;
    for(int i = 0; i < size; i++){
        tile[i] = Tile();
    }
    prepBoard();
}

void Board::prepBoard(){
    setMines();
    calcTileNums();
}

void Board::loadMineImgs(){
    
    tileImg.assign(12, 0);

    Board::tileImg[0] = SDL_LoadBMP
    ((Board::rpath+"tileUncovered.bmp").c_str());
    for(int i = 1; i < 9; i++){
        Board::tileImg[i] = SDL_LoadBMP
        ((Board::rpath+"tile"+std::to_string(i)+".bmp").c_str());
    }
    Board::tileImg[9] = SDL_LoadBMP
    ((Board::rpath+"mine.bmp").c_str());
    Board::tileImg[10] = SDL_LoadBMP
    ((Board::rpath+"tileCovered.bmp").c_str());
    Board::tileImg[11] = SDL_LoadBMP
    ((Board::rpath+"tileFlag.bmp").c_str());
}

void Board::setSize(int width, int height){
    if(height > 0 && height < 100) rows = height;
    if(width  > 0 && width  < 100) cols = width;
    size = cols*rows;
    tile.assign(size, Tile());
}

void Board::setMines(){
    int r = 0;
    flagCount = 0;
    for(int i = 0; i < size; i++){
        r = rand()%100;
        if(r < mineDensity){
            tile[i].num = 9;
            flagCount++;
        }
    }
}

int Board::countMineNeighbors(int ind){
    int ans = 0;
    int X = 0;
    int Y = 0;
    std::pair<int,int> coords = map1Dto2D(ind,cols);
    for(int row = -1; row < 2; row++){
    for(int col = -1; col < 2; col++){
        if(row || col){
            X = coords.first+col;
            Y = coords.second+row;
            if(X < cols && Y < rows && X >= 0 && Y >= 0){
                if(tile[map2Dto1D(Y,X,cols)].num == 9){
                    ans++;
                }
            }
        }
    }
    }
    return ans;
}

void Board::calcTileNums(){
    for(int i = 0; i < size; i++){
        if(tile[i].num != 9){
           tile[i].num  = countMineNeighbors(i);
        }
    }
}

void Board::print(){
    for(int row = 0, i = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            printf("%d ", tile[i].num);
            i++;
        }
        printf("\n");
    }
    printf("\n");

}

int Board::map2Dto1D(int row, int col, int w){
    return row * cols + col;
}

std::pair<int,int> Board::map1Dto2D(int ind, int w){
    std::pair<int,int> ans;
    ans.first = ind % w;
    ans.second = ind / w;
    return ans;
}

void Board::place(int y, int x, float scale){
    tileScale = scale;
    tileWidth = Board::tileImg[0]->w * scale;
    shape.w = cols*tileWidth;
    shape.h = rows*tileWidth;
    shape.x = x;
    shape.y = y;
}

std::pair<int,int> Board::findCursor(EventManager& e){
    std::pair<int,int> ans;
    
    if(e.mouse.pos.x >= shape.x &&
       e.mouse.pos.y >= shape.y &&
       e.mouse.pos.x <= shape.x + shape.w &&
       e.mouse.pos.y <= shape.y + shape.h
       ){

    
        ans.first  = (e.mouse.pos.x - shape.x)*cols/(shape.w);
        ans.second = (e.mouse.pos.y - shape.y)*rows/(shape.h);
    }else{
        ans.first = -1;
        ans.first = -1;
    }
    
    
    return ans;
}

void Board::flood(int y, int x){
    for(int dy = -1; dy < 2; dy++){
    for(int dx = -1; dx < 2; dx++){
        if(!(dx || dy)) continue;
        int X = x + dx;
        int Y = y + dy;
        if(X >= 0 && Y >= 0 && X < cols && Y < rows){
            Tile& t = getTile(Y,X);
            if(t.diggable()){
                t.covered = false;
                if(t.num == 0)
                    flood(Y, X);
            }
        }
    }}
}

bool Board::checkValidFlags(int y, int x){
    int count = getTile(y,x).num;
    for(int dy = -1; dy < 2; dy++){
    for(int dx = -1; dx < 2; dx++){
        if(!(dx || dy)) continue;
        int X = x + dx;
        int Y = y + dy;
        
        if(X >= 0 && Y >= 0 && X < cols && Y < rows){
            Tile& t = getTile(Y,X);
            if(!t.covered) continue;
            if(t.flagged){
                if(t.num != 9){
                    trigGameover();
                    return false;
                }else{
                    count--;
                }
            }
            if(!count)
                return true;
        }
    }}
    
    return false;
}

void Board::trigGameover(){
    gameover = true;
    for(int i = 0; i < size; i++){
        Tile& t = tile[i];
        if(t.num == 9){
            t.covered = false;
            t.flagged = false;
        }
    }
}

void Board::display(Window& win){
    
    for(int row = 0, py = shape.y, i = 0; row < rows; row++,py+=tileWidth){
        for(int col = 0, px = shape.x; col < cols; col++, px+=tileWidth){
            
            if(tile[i].flagged)
                win.blit(Board::tileImg[11], py,px, tileScale);
            else
            if(tile[i].covered)
                win.blit(Board::tileImg[10], py,px, tileScale);
            else
                win.blit(Board::tileImg[tile[i].num], py,px, tileScale);
            i++;
        }
    }
}

void Board::update(EventManager& e, Window& win){
    change = false;
    
    if(e.k.getStateOf(e.k.bind.up).checkPress()){
        reset();
        change = true;
    }
    
    if(e.mouse.checkTriggers() && !gameover){
        std::pair<int,int> mp = findCursor(e); // mp = mouse position
        if(mp.first>=0 && mp.second>=0){
            Tile& t = getTile(mp.second, mp.first);
            
            if(e.mouse.left.held){
                if(t.diggable()){
                    t.covered = false;
                    
                    if(t.num == 0)
                        flood(mp.second, mp.first);
                    else
                    if(t.num == 9){
                        trigGameover();
                    }
                    change = true;
                }else{
                    if(!t.covered)
                        if(checkValidFlags(mp.second, mp.first))
                            flood(mp.second, mp.first);
                    change = true;
                }
            }
            if(e.mouse.right.held){
                
                if(t.covered){
//                    t.flagged = !t.flagged;
                    if(t.flagged){
                        flagCount++;
                        t.flagged  = false;
                    }else{
                        flagCount--;
                        t.flagged  = true;
                    }
                    printf("%d\n", flagCount);
                    change = true;
                }
                
            }
        }
    }
}

Tile& Board::getTile(int row, int col){return tile[map2Dto1D(row,col,cols)];};
Tile& Board::operator[] (int ind){return tile[ind];}
Tile& Board::operator() (int ind){return tile[ind];}
Tile& Board::operator() (int row, int col){return getTile(row, col);}

