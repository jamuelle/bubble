#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>


class Tile
{
public:
    typedef enum{
        north=0,
        east=1,
        south=2,
        west=3
    }dir;
    typedef enum{
        blast=0,
        red=1,
        green=2,
        yellow=3,
        blue=4,
    }state;

private:
    bool fHit;
    state st;
    std::vector<Tile*> neighbour;
int x,y;
public:
void setC(int j,int i){
    x=j;y=i;
}
void printC(){
    std::cout << "("<<x<<"/"<<y<<") ";}

    Tile()
     : fHit(false), st(blast),
       neighbour(std::vector<Tile*>(4))
    {
        for (int i=0;i<4;i++) {
            neighbour[i]=NULL;
        }
    }

    void setNeighbour( Tile::dir d, Tile* t) {
        if ( d < 4 ) {
            neighbour[d] = t;
        }
    }

    Tile* getNeighbour( Tile::dir d) {
        return neighbour[ static_cast<int>(d) ];
    }

    bool hit() {
        if ( st!=Tile::blast) {
            fHit=true;
        }
        return fHit;
    }

    bool gotHit() {
        if (fHit==true) {
            fHit=false;
            return true;
        }
        return false;
    }

    void print() {
//        if (ball!=NULL) {
//            ball->print();
//        } else {
            //std::cout << " ";
            std::cout << static_cast<int>(st);
//        }
    }

    void setState( Tile::state s) {
        st = s;
    }

    bool damage() {
       if (st>0) {
            st = static_cast<Tile::state>(st-1);
            return st==blast;
        }
        return false;
    }

    bool isClear() {
        return st==blast;
    }
};

#endif
