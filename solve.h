#ifndef SOLVE_H
#define SOLVE_H

#include "grid.h"

/*

x x y x g
b b r r b
y g g r y
r y x g g
x y x r x
y x g y r

x Red green yellow blue 

*/
class Solve
{
    Grid grid;

public:
    Solve() :grid(3,3) {//: grid(5,5) {
//        grid.setAt(0, 0, Tile::blast);
//        grid.setAt(0, 1, Tile::blast);
//        grid.setAt(0, 2, Tile::yellow);
//        grid.setAt(0, 3, Tile::blast);
//        grid.setAt(0, 4, Tile::green);
//
//        grid.setAt(1, 0, Tile::blue);
//        grid.setAt(1, 1, Tile::blue);
//        grid.setAt(1, 2, Tile::red);
//        grid.setAt(1, 3, Tile::red);
//        grid.setAt(1, 4, Tile::blue);
//
//        grid.setAt(2, 0, Tile::yellow);
//        grid.setAt(2, 1, Tile::green);
//        grid.setAt(2, 2, Tile::green);
//        grid.setAt(2, 3, Tile::red);
//        grid.setAt(2, 4, Tile::yellow);
//
//        grid.setAt(3, 0, Tile::red);
//        grid.setAt(3, 1, Tile::yellow);
//        grid.setAt(3, 2, Tile::blast);
//        grid.setAt(3, 3, Tile::green);
//        grid.setAt(3, 4, Tile::green);
//
//        grid.setAt(4, 0, Tile::yellow);
//        grid.setAt(4, 1, Tile::blast);
//        grid.setAt(4, 2, Tile::green);
//        grid.setAt(4, 3, Tile::yellow);
//        grid.setAt(4, 4, Tile::red);
//

        grid.setAt(0,1, Tile::red);
        grid.setAt(1,1, Tile::yellow);
        grid.setAt(2,0, Tile::red);
    }

    void go() {

        grid.print();
        run(0);
        grid.print();
    }

    void simulate() {
        while( grid.bulletsOnGrid() ) {
            grid.bulletsMove();
            grid.tilesCheckDamage();
            std::cout << "X";
        }
        std::cout << "done";
    }

    bool run(int level)
    {
        if (level>3) {
            return false;
        }

        //try through all possible positions for this level
        for (int i=0;i<grid.maxX();i++) {
        for (int j=0;j<grid.maxY();j++) {

            GridState state = grid.save();

            grid.tipAt(j,i); // one tip
            simulate();

            if (!grid.ballsOnGrid() ) { //we are done now.
                std::cout << "tip for L: "<<level <<" "<<i<<"/"<<j<<std::endl;
                return true;
            }

            //in case there are still balls on the field,
            //assume this was a right guess and continue
            //one level deeper

            if ( run(level+1) ) {
                //if it was successful, print this tip
                std::cout << "tip for L: "<<level <<" "<<i<<"/"<<j<<std::endl;
                return true; 
            } else {
                //means this path was bad, cont. with the next tip point
                grid.load(state);
            }
        }}
        return false;
    }
};

#endif
