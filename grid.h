/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author YOUR_STUDENT_NUMBER
 * @date March, 2020
 */
#pragma once
#include <vector>

// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
  private:
    int width;
    int height;
    int total_cells;
    int dead_cells;
    int alive_cells;
    std::vector<Cell> cellList;

    int get_index() const;

  public:
    Grid(); //The default constructor
    Grid(int size); //The constructor for just one argument
    Grid(int width, int height); //The constructor for two arguments
    ~Grid();

    //The member functions
    int get_height() const;
    int get_width() const;
    int get_total_cells() const;
    int get_alive_cells() const;
    int get_dead_cells() const;
    void resize(int x);
    void resize(int x, int y);
    int get_index(int x, int y);
    Cell get(int x, int y);
    //Cell operator()(int x, int y);
    //Cell* operator()(int x, int y);
    Grid crop(int x, int y, int a, int b);
    void set(int x, int y, Cell c);
    void merge(Grid grid, int a, int b);
    void merge(Grid x, int a, int b, bool c);
    Grid rotate(int rotation) const;
};
