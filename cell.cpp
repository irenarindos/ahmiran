#include "cell.h"
#include <iostream>

Cell& Cell::operator=(const Cell& src){
    topLeft = src.topLeft;
    side = src.side;
    state = src.state;
    occupant = src.occupant;
    i = src.i;
    j = src.j;
    return *this;
}

void Cell::setState(int newState){
    state = newState; 
    if(state != OCCUPIED)
        occupant = NULL;
}

bool Cell::operator==(const Cell &other) const {
    if(this->topLeft == other.topLeft) return true;
    return false;
}

void Cell::print(){
    std::cout << "Top Left Corner: " << topLeft[0] << ", " << topLeft[1] << std::endl;
    std::cout << "Side Length: " << side << std::endl;
    std::cout << "Grid loc: " << i << ", " << j << std::endl;
}

