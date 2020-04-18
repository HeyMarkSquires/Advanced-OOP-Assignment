/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 963356
 * @date March, 2020
 */
#pragma once

#include "grid.h"
// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
  private:
    int width;
    int height;
    int total_cells;
    int alive_cells;
    int dead_cells;
    Grid currState;
    Grid newState;

    int count_neighbours(int x, int y, bool toroidal);
  public:
    World();
    World(int size);
    World(int width, int height);
    World(Grid grid);
    int get_height() const;
    int get_width() const;
    int get_total_cells() const;
    int get_alive_cells() const;
    int get_dead_cells() const;
    void resize(int square_size);
    void resize(int new_width, int new_height);
    Grid get_state() const;
    void step(bool toroidal);
    void step();
    void advance(int steps, bool toroidal);
    void advance(int steps);
    ~World();


};
