#ifndef CELL__H
#define CELL__H
#include "vector2f.h"
#include "sprite.h"

#define EMPTY 0
#define OCCUPIED 1
#define INANIMATE 2

/*
 * assumes a top left origin
 */

class Cell{
    public:
        Cell():
            topLeft(), 
            side(0), 
            state(EMPTY), 
            occupant(NULL),
            i(0), j(0){}
        Cell(const Cell& src): 
            topLeft(src.topLeft),
            side(src.side), 
            state(src.state),
            occupant(src.occupant),
            i(src.i), j(src.j){}
        ~Cell(){ occupant = NULL; }
        int getState() const
            { return state; }
        void setState(int newState);
        void setCorner(int x, int y){
            topLeft = Vector2f(static_cast<float>(x), static_cast<float>(y));
        }
        void setSideLength(int len)
            { side = len; }
        Sprite* getOccupant() const{ return occupant; }
        void setOccupant(Sprite *s){ occupant = s; }
        Vector2f getCenter() const{ 
            return Vector2f(topLeft[0]+static_cast<float>(side)/2, 
                            topLeft[1]+static_cast<float>(side)/2);
        }
        int getCornerX() const{
            return static_cast<int>(topLeft[0]);
        }
        int getCornerY() const{
            return static_cast<int>(topLeft[1]);
        }
        Cell& operator=(const Cell&src);
        void setGridPosition(int i, int j){ this->i = i; this->j = j; }
        int getGridCol() const{ return j; }
        int getGridRow() const{ return i; }
        void print();
        bool operator==(const Cell&) const;
    private:
        Vector2f topLeft;
        int side;
        int state;
        Sprite *occupant;
        int i;
        int j;
};
#endif
