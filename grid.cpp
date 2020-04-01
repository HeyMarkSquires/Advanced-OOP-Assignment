/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 963356
 * @date March, 2020
 */
#include <sstream>
#include <string>
#include <iostream>
#include "grid.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */

 Grid::Grid():width(0), height(0), total_cells(0), dead_cells(0), alive_cells(0){

 }

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */

 Grid::Grid(int square_size) : width(square_size), height(square_size),
 total_cells(square_size*square_size), dead_cells(square_size*square_size), alive_cells(0){
   int tcells=square_size*square_size;
   std::vector<Cell> cList;
   cList.resize(tcells);
   for (int i=0; i<tcells; i++){
     cList.at(i)=Cell::DEAD;
   }
   this->cellList=cList;
 }

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
 Grid::Grid(int width, int height) : width(width), height(height),
 total_cells(width*height), dead_cells(width*height), alive_cells(0){
   int tcells=width*height;
   std::vector<Cell> cList;
   cList.resize(tcells);
   for (int i=0; i<tcells; i++){
     cList.at(i)=Cell::DEAD;
   }
   this->cellList=cList;
 }

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */

 int Grid::get_width() const{
   return this->width;
 }

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */

 int Grid::get_height() const{
   return this->height;
 }

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */

 int Grid::get_total_cells() const{
   return this->total_cells;
 }

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */

 int Grid::get_alive_cells() const{
   return this->alive_cells;
 }

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */

 int Grid::get_dead_cells() const{
   return this->dead_cells;
 }

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */

void Grid::resize(int square_size){
  int oldWidth=this->get_width();
  int oldHeight=this->get_height();

  std::vector<Cell> newList;
  int newLength=square_size*square_size;
  newList.resize(newLength);
  for (int i=0; i<newLength; i++){
    newList.at(i)=Cell::DEAD;
  }
  //Creating the new cell list
  int v=0;
  //If the size is now bigger overall
  if ((oldWidth*oldHeight)<(width*height)){
    //Creating the new cell list
    for (int i=0; i<oldHeight; i++){
      for (int j=0; j<oldWidth; j++){
        int result=(i*width)+j;
        Cell c=this->get(j, i);
        newList.at(result)=c;
        v++;
      }
    }
  }
  //If the x has decreased
  else if (width<oldWidth){
    for (int i=0; i<height; i++){
      for (int j=0; j<width; j++){
        Cell o=this->get(j, i);
        newList.at(v)=o;
        v++;
      }
    }
  }
  //If the y has decreased
  else if (height<oldHeight){
    for (int i=0; i<height; i++){
      for (int j=0; j<width; j++){
        if (j>=height){
          newList.at(v)=Cell::DEAD;
        }
        else{
          Cell c=this->get(i, j);
          newList.at(v)=c;
        }
        v++;
      }
    }
  }
  int alive=0;
  for (int i=0; i<(height*width); i++){
    if (newList.at(i)==Cell::ALIVE){
      alive++;
    }
  }
  //Updating the grid
  this->height=height;
  this->width=width;
  this->dead_cells=(height*width)-alive;
  this->alive_cells=alive;
  this->total_cells=height*width;
  this->cellList=newList;
}

/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */

void Grid::resize(int width, int height){
   int oldWidth=this->get_width();
   int oldHeight=this->get_height();
   std::cout<<width<<", "<<height<<std::endl;
   std::vector<Cell> newList;
   int newLength=width*height;
   newList.resize(newLength);
   for (int i=0; i<newLength; i++){
     newList.at(i)=Cell::DEAD;
   }
   int v=0;
   //If the size is now bigger overall
   if (oldWidth<width && oldHeight<height){
     std::cout<<"Bigger"<<std::endl;
     //Creating the new cell list
     for (int i=0; i<oldHeight; i++){
       for (int j=0; j<oldWidth; j++){
         int result=(i*width)+j;
         Cell c=this->get(j, i);
         newList.at(result)=c;
         v++;
       }
     }
   }
   else if (width<oldWidth && height<oldHeight){
     std::cout<<"Smaller"<<std::endl;
     for (int i=0; i<height; i++){
       for (int j=0; j<width; j++){
         std::cout<<j<<", "<<i<<std::endl;
         Cell o=this->get(j, i);
         newList.at(v)=o;
         v++;
       }
     }
   }
   //If the x has decreased
   else if (width<oldWidth){
     std::cout<<"x decreased"<<std::endl;
     for (int i=0; i<height; i++){
       for (int j=0; j<width; j++){
         Cell o=this->get(j, i);
         newList.at(v)=o;
         v++;
       }
     }
   }
   //If the y has decreased
   else if (height<oldHeight){
     std::cout<<"y decreased"<<std::endl;
     for (int i=0; i<height; i++){
       for (int j=0; j<width; j++){
         Cell o=this->get(j, i);
         newList.at(v)=o;
         v++;
       }
     }
   }
   int alive=0;
   for (int i=0; i<(height*width); i++){
     if (newList.at(i)==Cell::ALIVE){
       alive++;
     }
   }
   //Updating the grid
   this->height=height;
   this->width=width;
   this->dead_cells=(height*width)-alive;
   this->alive_cells=alive;
   this->total_cells=height*width;
   this->cellList=newList;
}
/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */

 int Grid::get_index(int x, int y){
   int w=this->width;
   int result=(y*w)+x;
   return result;
 }

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

 Cell Grid::get(int x, int y) const{
   Cell n;
   int w=this->width;
   int index=(y*w)+x;
   n=(this->cellList).at(index);
   return n;
 }

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
 void Grid::set(int x, int y, Cell c){
   int w=this->get_width();
   int index=(y*w)+x;
   std::vector<Cell> l=this->cellList;
   int currAlive=this->get_alive_cells();
   int currDead=this->get_dead_cells();
   //Getting the current state of the cell

   if (c==Cell::ALIVE){
     currAlive++;
     if (currDead>0){
       currDead--;
     }
     l.at(index)=Cell::ALIVE;
   }
   else if (c==Cell::DEAD){
     if (currAlive>0){
       currAlive--;
     }
     currDead++;
     l.at(index)=Cell::DEAD;
   }

   //Finally, replace the cellList with the new cellList
   this->cellList=l;
   this->alive_cells=currAlive;
   this->dead_cells=currDead;
 }


/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell& Grid::operator()(int x, int y){
  int index=this->get_index(x, y);
  //Feels cheaty...
  int d=this->get_dead_cells();
  int a=this->get_alive_cells();
  if (this->get(x,y)==Cell::ALIVE){
    a--;
    d++;
  }
  else{
    a++;
    d--;
  }
  this->dead_cells=d;
  this->alive_cells=a;
  Cell& c=(this->cellList).at(index);
  return c;
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell Grid::operator()(int x, int y) const{
   Cell result;
   result=this->get(x, y);
   return result;
}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */

Grid Grid::crop(int x0, int y0, int x1, int y1){
  std::vector<Cell> currList=this->cellList;
  int height;
  int width;
  if (x0<x1){
    width=x1-x0;
  }
  else{
    width=x0-x1;
  }
  if (y0<y1){
    height=x1-x0;
  }
  else{
    height=y0-y1;
  }
  Grid* g=new Grid(width, height);
  int newLength=width*height;
  std::vector<Cell> newList;
  newList.resize(newLength);
  int totalAlive=0;
  int totalDead=0;
  int newIndex=0;

  //Making sure we move in the correct y direction
  if (y0<y1){
    for (int i=y0; i<y1; i++){
      if (x0<x1){
        for (int j=x0; j<x1; j++){
          Cell cell=this->get(j, i);
          if (cell==Cell::ALIVE){
            totalAlive++;
          }
          else{
            totalDead++;
          }
          newList.at(newIndex)=cell;
          newIndex++;
        }
      }
      else{
        for (int j=x1; j<x0; j++){
          Cell cell=this->get(j, i);
          if (cell==Cell::ALIVE){
            totalAlive++;
          }
          else{
            totalDead++;
          }
          newList.at(newIndex)=cell;
          newIndex++;
        }
      }
    }
  }
  else{
    for (int i=y1; i<y0; i++){
      if (x0<x1){
        for (int j=x0; j<x1; j++){
          Cell cell=this->get(j, i);
          if (cell==Cell::ALIVE){
            totalAlive++;
          }
          else{
            totalDead++;
          }
          newList.at(newIndex)=cell;
          newIndex++;
        }
      }
      else{
        for (int j=x1; j<x0; j++){
          Cell cell=this->get(j, i);
          if (cell==Cell::ALIVE){
            totalAlive++;
          }
          else{
            totalDead++;
          }
          newList.at(newIndex)=cell;
          newIndex++;
        }
      }
    }
  }
  g->dead_cells=totalDead;
  g->alive_cells=totalAlive;
  g->cellList=newList;
  return *g;
}

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */

void Grid::merge(Grid other, int x0, int y0){
  std::vector<Cell> otherCellList=other.cellList;
  std::vector<Cell> myCellList=this->cellList;
  int totalDead=this->get_dead_cells();
  int totalAlive=this->get_alive_cells();
  int otherHeight=other.get_height();
  int otherWidth=other.get_width();
  int index=0;
  int myIndex;
  for (int i=y0; i<otherHeight+y0; i++){
    for (int j=x0; j<otherWidth+x0; j++){
      myIndex=this->get_index(j, i);

      Cell c=otherCellList.at(index);
      //Increasing the dead count if required
      if (c==Cell::DEAD && myCellList.at(myIndex)==Cell::ALIVE){
        totalDead++;
        totalAlive--;
      }
      else if (c==Cell::ALIVE && myCellList.at(myIndex)==Cell::DEAD){
        totalDead--;
        totalAlive++;
      }
      myCellList.at(myIndex)=c;
      index++;
    }
  }

  this->cellList=myCellList;
  this->alive_cells=totalAlive;
  this->dead_cells=totalDead;

}

void Grid::merge(Grid other, int x0, int y0, bool alive_only){
  std::vector<Cell> otherCellList=other.cellList;
  std::vector<Cell> myCellList=this->cellList;
  int totalDead=this->get_dead_cells();
  int totalAlive=this->get_alive_cells();
  int otherHeight=other.get_height();
  int otherWidth=other.get_width();
  int index=0;
  int myIndex;
  for (int i=y0; i<otherHeight+y0; i++){
    for (int j=x0; j<otherWidth+x0; j++){
      myIndex=this->get_index(j, i);

      Cell c=otherCellList.at(index);
      //If alive_only is true, kill the merged cells that are alive
      if (alive_only){
        if (c==Cell::DEAD && myCellList.at(myIndex)==Cell::ALIVE){
          totalDead++;
          totalAlive--;
          myCellList.at(myIndex)=c;
        }
      }
      else{
        if (c==Cell::DEAD && myCellList.at(myIndex)==Cell::ALIVE){
          totalDead++;
          totalAlive--;
        }
        else if (c==Cell::ALIVE && myCellList.at(myIndex)==Cell::DEAD){
          totalDead--;
          totalAlive++;
        }
        myCellList.at(myIndex)=c;
      }
      //Increasing the dead count if required

      index++;
    }
  }

  this->cellList=myCellList;
  this->alive_cells=totalAlive;
  this->dead_cells=totalDead;
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */

Grid Grid::rotate(int rotation) const{
  int newHeight;
  int newWidth;
  int oldHeight=this->height;
  int oldWidth=this->width;
  int totalAlive=this->get_alive_cells();
  int totalDead=this->get_dead_cells();
  std::vector<Cell> newCellList;
  newCellList.resize(oldHeight*oldWidth);
  int index=0;
  //0 degrees, nothing changes
  if (rotation%4==0){
    newHeight=this->height;
    newWidth=this->width;
    newCellList=this->cellList;

  }
  //90 degrees (Fin)
  else if (rotation%4==1 || rotation%4==-3){
    newHeight=this->width;
    newWidth=this->height;
    for (int i=0; i<newHeight; i++){
      for (int j=newWidth-1; j>=0; j--){
        Cell c=this->get(i, j);
        newCellList.at(index)=c;
        index++;
      }
    }
  }
  //180 degrees (Fin)
  else if (rotation%4==2 || rotation%4==-2){
    newHeight=this->height;
    newWidth=this->width;
    for (int i=newHeight-1; i>=0; i--){
      for (int j=newWidth-1; j>=0; j--){
        Cell c=this->get(j, i);
        newCellList.at(index)=c;
        index++;
      }
    }
  }
  //270 degrees (Fin)
  else if (rotation%4==3 || rotation%4==-1){
    newHeight=this->width;
    newWidth=this->height;
    for (int i=newHeight-1; i>=0; i--){
      for (int j=0; j<newWidth; j++){
        Cell c=this->get(i, j);
        newCellList.at(index)=c;
        index++;
      }
    }
  }
  Grid result(newWidth, newHeight);
  result.cellList=newCellList;
  result.alive_cells=totalAlive;
  result.dead_cells=totalDead;
  return result;
}

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */

std::ostream& operator<<(std::ostream& stream, const Grid& grid){
   int height=grid.get_height();
   int width=grid.get_width();
   stream<<"+";
   for (int i=0; i<width; i++){
     stream<<"-";
   }
   stream<<"+\n";
   //Contents
   for (int i=0; i<height; i++){
     stream<<"|";
     for (int j=0; j<width; j++){
       Cell c=grid.get(j, i);
       stream<<(char)c;
     }
     stream<<"|\n";
   }
   //The bottom line
   stream<<"+";
   for (int i=0; i<width; i++){
     stream<<"-";
   }
   stream<<"+\n";

   return stream;
}

Grid::~Grid(){ }
