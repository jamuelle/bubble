#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include "tile.h"

class Bullet
{
    Tile::dir d;
    Tile* tile;

public:
    Bullet( Tile*t, Tile::dir _d)
     : d(_d), tile(t)
    {}

    bool move() {
        Tile* n = tile->getNeighbour( d );
        if ( n ) {
            tile = n;
            if (tile->hit()) {
                //in case there was a hit, destroy the bullet
                return false;
            }
            return true; //don't destroy in case of no hit
        }  //if there is no neighbour, destroy as well
        return false;
    }

    void print() {
        std::cout << static_cast<char>('A');
    }
};


#endif
