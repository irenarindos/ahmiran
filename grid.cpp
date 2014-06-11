#include "gamedata.h"
#include "grid.h"
#include "ioManager.h"
#include <cstdlib>
#include <iostream>
#include <vector>

Grid::~Grid(){
    for(int i = 0; i < height/cellSize; ++i)
        delete [] grid[i] ;
    delete [] grid;
}

Grid& Grid::getInstance() {
    static Grid game;
    return game;
}

Grid::Grid(const string &name): 
    name(name),
    width(Gamedata::getInstance().getXmlInt(name+"Width")),
    height(Gamedata::getInstance().getXmlInt(name+"Height")),
    cellSize(Gamedata::getInstance().getXmlInt(name+"CellSize")),
    grid(new Cell *[width/cellSize])
{
    for( int i = 0 ; i <  height/cellSize; i++ )       
        grid[i] = new Cell[width/cellSize];

    SDL_Surface* surface = IOManager::getInstance().loadAndSet(Gamedata::getInstance().getXmlStr(name+"Objects"), false);
    SDL_LockSurface(surface);

    int x(0), y(0), blackCount(0); 
    for(int i = 0; i < height / cellSize; ++i, y+=cellSize){
        for(int j = 0; j < width / cellSize; ++j, x+=cellSize){
            grid[i][j].setCorner(x, y);
            grid[i][j].setSideLength(cellSize);
            grid[i][j].setGridPosition(i, j);

            //check the cell for black pixels in object map to set state of cell
            Cell check = grid[i][j];
            for(int y = check.getCornerY(); y < check.getCornerY()+cellSize; ++y){
                for(int x = check.getCornerX(); x < check.getCornerX()+cellSize; ++x){
                    if(getpixel(surface, x, y) == 0) ++blackCount;
                }
            }
            if(static_cast<float>(blackCount) / (cellSize*cellSize) > .05)
                grid[i][j].setState(INANIMATE);
            else grid[i][j].setState(EMPTY); 
            blackCount = 0;          
        }
        x = 0;
    }
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);
}

Uint32 Grid::getpixel(SDL_Surface *surface, int x, int y)
{
    //std::cout << "getting pixel " << x << ", " << y << std::endl;

    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
 
    switch (bpp) {
    case 1:
        return *p;
 
    case 2:
        return *(Uint16 *)p;
 
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
 
    case 4:
        return *(Uint32 *)p;
 
    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    } // switch
}

Cell Grid::getCell(int i, int j){
    if(i < 0 || i >= height/cellSize) i = 0;
    if(j < 0 || j >= width/cellSize) j = 0;
    return grid[i][j];
}

Cell Grid::getCell(const Vector2f &pos){
    int i = static_cast<int>(pos[1]) / cellSize;
    if(i < 0) i = 0;
    else if(i >= height/cellSize) i = height/cellSize - 1;
    int j = static_cast<int>(pos[0]) / cellSize;
    if(j < 0) j = 0;
    else if(j > width/cellSize) j = width/cellSize - 1;
    //std::cout << "(" << pos[1] << "," << pos[0] << ") = grid[" << i << "][" << j << "]" << std::endl; 
    return grid[i][j];
}

/*
 * 
 */
Cell Grid::path(const Vector2f &p1, const Vector2f &p2){   
    Cell start = getCell(p1);
    Cell end = getCell(p2);   

    //get row, col coordinates of starting and ending cells
    int i, j, end_i, end_j;
    i = start.getGridRow();
    j = start.getGridCol();
    end_i = end.getGridRow();
    end_j = end.getGridCol();
    //std::cout << "Request for path from cell " << i << ", " << j << " to cell " << end_i << ", " << end_j << std::endl;

    //points are in same cell
    if(start == end)
        return grid[i][j];

    //determine which neighbors are legal to move to
    std::vector<Cell> neighbors;
    if(i-1 >= 0 && grid[i-1][j].getState() == EMPTY) 
        neighbors.push_back(grid[i-1][j]);
    if(i+1 < height/cellSize && grid[i+1][j].getState() == EMPTY)
        neighbors.push_back(grid[i+1][j]);
    if(j-1 >= 0 && grid[i][j-1].getState() == EMPTY)
        neighbors.push_back(grid[i][j-1]);
    if(j+1 < width/cellSize && grid[i][j+1].getState() == EMPTY)
        neighbors.push_back(grid[i][j+1]);

    //no neighbors are legal moves, cell is trapped
    if(neighbors.size() == 0)      
        return grid[i][j];

    //calculate lowest cost path between neighboring cells and destination cell
    std::vector<Cell> dest;
    int cheapest(-1);
    for(unsigned i = 0; i < neighbors.size(); ++i){
        int cost = std::abs(neighbors.at(i).getGridRow()- end_i) + std::abs(neighbors.at(i).getGridCol() - end_j);
        //std::cout << neighbors.at(i).getGridRow() << ", " << neighbors.at(i).getGridCol() << ": " << cost << std::endl;
        if(cheapest == -1 || cost < cheapest){
            cheapest = cost;
            dest.clear();
            dest.push_back(neighbors.at(i));
        }
        else if(cost == cheapest)
            dest.push_back(neighbors.at(i));
    }

    Cell c = dest.at(rand()%dest.size());
    return grid[c.getGridRow()][c.getGridCol()];
}

/*
 * returns the closest adjacent empty cell to a given cell
 */
Cell Grid::getAdjacentEmptyCell(const Cell &target, int depth){
    static int max_depth = 4;
    if(depth > max_depth) return Cell();

    int i, j, current_depth;
    i = target.getGridRow();
    j = target.getGridCol();
    current_depth = depth+1;

        //determine which neighbors are legal to move to
    std::vector<Cell> neighbors;
    if(i-1 >= 0){
        if(grid[i-1][j].getState() == EMPTY)
            return grid[i-1][j];
        else neighbors.push_back(grid[i-1][j]);
    }
    if(i+1 < height/cellSize){
        if(grid[i+1][j].getState() == EMPTY)
            return grid[i+1][j];
        else neighbors.push_back(grid[i+1][j]);
    }
    if(j-1 >= 0){
        if(grid[i][j-1].getState() == EMPTY)
            return grid[i][j-1];     
        else neighbors.push_back(grid[i][j-1]);
    }
    if(j+1 < width/cellSize){
        if(grid[i][j+1].getState() == EMPTY)
            return grid[i][j+1];
        else neighbors.push_back(grid[i][j+1]);
    }

    for(unsigned k = 0; k < neighbors.size(); ++k){
        Cell c = getAdjacentEmptyCell(neighbors.at(k), current_depth);
        if(c == Cell()) break;
        else return c;
    }
    return Cell();
}

void Grid::occupyCell(int i, int j, Sprite *occupant){
    grid[i][j].setState(OCCUPIED); 
    grid[i][j].setOccupant(occupant);
}

void Grid::printOccupied(){
    for(int i = 0; i < height/cellSize; ++i){
        for(int j = 0; j < width/cellSize; ++j){
            if(grid[i][j].getState() == OCCUPIED)
                std::cout << i << ", " << j << " occupied" << std::endl;
        }
    }
}
