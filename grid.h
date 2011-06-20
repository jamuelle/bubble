#ifndef GRID_H
#define GRID_H

#include <list>
#include <stack>

#include "tile.h"
#include "bullet.h"

class GridState
{
    std::list<Tile> tiles;

public:
    GridState(std::list<Tile>& t)
    //hmhm : reserve space for the list in initializiation?
    {
    //std::cout << "ctor" << std::endl;
        save( t );
    }

    void load(std::list<Tile>& t) {
        std::list<Tile>::iterator itSrc = tiles.begin();
        std::list<Tile>::iterator itDst = t.begin();
        for (; itSrc != tiles.end() ; itSrc++, itDst++) {
            *itDst = *itSrc;
        }
    }

    void save(std::list<Tile>& t) {
        std::list<Tile>::iterator it = t.begin();
        for (; it != t.end() ; it++) {
            tiles.push_back( *it );
        }
    }
};


class Grid
{
    int x;
    int y;

    std::list<Tile> tiles;
    std::list<Bullet> bullets;

    std::vector<std::vector<Tile*> > grid;

public:
    Grid(int _x, int _y)
     : x(_x), y(_y),
       grid( std::vector<std::vector<Tile*> >(_y,std::vector<Tile*>(_x)))
    {
        for(int j=0;j<_y;j++) {
            for(int i=0;i<_x;i++) {
                tiles.push_back( Tile() );
                grid[j][i] = &(tiles.back());
grid[j][i]->setC( j,i);
            }
        }

        for(int j=0;j<_y;j++) {
            for(int i=0;i<_x;i++) {
                if ( j-1 >= 0)
                    grid[j][i]->setNeighbour( Tile::north, grid[j-1][i]);
                if (i+1 < _x)
                    grid[j][i]->setNeighbour( Tile::east,  grid[j][i+1]);
                if (j+1 < _y)
                    grid[j][i]->setNeighbour( Tile::south,  grid[j+1][i]);
                if (i-1 >= 0)
                    grid[j][i]->setNeighbour( Tile::west,  grid[j][i-1]);
//Tile *t;std::cout << "@"<<j<<"/"<<i<<std::endl;
//t = grid[j][i]->getNeighbour( Tile::north );
//if(t){t->printC();}else{std::cout<<"(x/x)";}
//t = grid[j][i]->getNeighbour( Tile::east );
//if(t){t->printC();}else{std::cout<<"(x/x)";}
//t = grid[j][i]->getNeighbour( Tile::south );
//if(t){t->printC();}else{std::cout<<"(x/x)";}
//t = grid[j][i]->getNeighbour( Tile::west );
//if(t){t->printC();}else{std::cout<<"(x/x)";}
            }
        }
    }

    int maxX(){return x;}
    int maxY(){return y;}

    void setAt(int y, int x, Tile::state c) {
        grid[y][x]->setState( c );
    }
    void tipAt(int x, int y) {
        damageTile(grid[y][x]);
    }

    void init1() {
        tiles.front().setState( Tile::red );
        tiles.back().setState( Tile::red );
    }

    bool ballsOnGrid() {
        //hmhm, this is probably slow. Maybe optimize it
        std::list<Tile>::iterator it = tiles.begin();
        for (; it != tiles.end() ; it++) {
            if (!it->isClear()) {
                return true;
            }
        }
        return false;
//        return balls.size() != 0;
    }
    bool bulletsOnGrid() {
        return bullets.size() != 0;
    }

    //"damage this tile"
    bool damageTile(Tile* t) {
        if ( t->damage() ) {
            bullets.push_back( Bullet( t, Tile::north ) );
            bullets.push_back( Bullet( t, Tile::east  ) );
            bullets.push_back( Bullet( t, Tile::south ) );
            bullets.push_back( Bullet( t, Tile::west  ) );
        }
    }

    void bulletsMove() {
        //hmhm, this is probably slow. Maybe optimize it
        std::list<Bullet>::iterator it = bullets.begin();
        for (; it != bullets.end() ; it++) {
            if ( !it->move() ) {
                it = bullets.erase( it );
            }
        }
    }

    void tilesCheckDamage() {
        std::list<Tile>::iterator it = tiles.begin();
        for (; it != tiles.end() ; it++) {
            if (it->gotHit()) {
                damageTile( &(*it) ); //it->damage();
            }
        }
    }

    void print() {
        std::cout << std::endl;
        for(int j=0;j<y;j++) {
            for(int i=0;i<x;i++) {
                grid[j][i]->print();
            }
            std::cout << std::endl;
        }
    }

    GridState save() {
        return GridState( tiles );//states.push( GridState( tiles ) );
    }
    void load(GridState &st) {
        st.load( tiles );
        //states.top().load( tiles );
        //states.pop();
    }
};

#endif
