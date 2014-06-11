#ifndef GRID__H
#define GRID__H
#include <string>
#include "cell.h"
#include "gamedata.h"

class Grid{
    public:
        static Grid& getInstance();
        ~Grid();
        Cell getCell(int, int);          //get cell by row, col indexing
        Cell getCell(const Vector2f&);   //get cell by world coordinates
        Cell path(const Vector2f&, const Vector2f&);
        Cell getAdjacentEmptyCell(const Cell&, int);
        int getCellSize() const
            { return cellSize; }
        int getWidth() const
            { return width; }
        int getHeight() const
            { return height; }

        void occupyCell(int, int, Sprite *);
        void clearCell(int i, int j)
            { grid[i][j].setState(EMPTY); }

        void printOccupied();
    private:
        std::string name;
        int width;
        int height;
        int cellSize;
        Cell **grid;

        Grid(const string &name = "worldMap");
        Grid(const Grid&);
        Grid& operator=(const Grid&);

        Uint32 getpixel(SDL_Surface *, int, int);
};
#endif
