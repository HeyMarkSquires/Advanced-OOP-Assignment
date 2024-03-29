/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 963356
 * @date March, 2020
 */
#include "zoo.h"
#include "grid.h"
#include "world.h"


// Include the minimal number of headers needed to support your implementation.
// #include ...
#include <fstream>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstring>
#include <algorithm>

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider(){
  Grid result(3, 3);
  result.set(1, 0, Cell::ALIVE);
  result.set(2, 1, Cell::ALIVE);
  result.set(0, 2, Cell::ALIVE);
  result.set(1, 2, Cell::ALIVE);
  result.set(2, 2, Cell::ALIVE);
  return result;
}



/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */

Grid Zoo::r_pentomino(){
  Grid result(3, 3);
  result.set(1, 0, Cell::ALIVE);
  result.set(2, 0, Cell::ALIVE);
  result.set(0, 1, Cell::ALIVE);
  result.set(1, 1, Cell::ALIVE);
  result.set(1, 2, Cell::ALIVE);
  return result;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 3x3 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship(){
   Grid result(5, 4);
   result.set(1, 0, Cell::ALIVE);
   result.set(4, 0, Cell::ALIVE);
   result.set(0, 1, Cell::ALIVE);
   result.set(0, 2, Cell::ALIVE);
   result.set(4, 2, Cell::ALIVE);
   result.set(0, 3, Cell::ALIVE);
   result.set(1, 3, Cell::ALIVE);
   result.set(2, 3, Cell::ALIVE);
   result.set(3, 3, Cell::ALIVE);
   return result;
 }

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */

Grid Zoo::load_ascii(std::string path){
  std::ifstream inFile;
  std::string line;
  int width;
  int height;
  inFile.open(path);
  if (!inFile) {
    throw "NOPE";
  }
  inFile>>width;
  inFile>>height;
  if (width<=0 || height<=0){
    throw "NOPE";
  }
  Grid grid(width, height);
  std::getline(inFile, line);
  int y=0;
  int length;
  while (std::getline(inFile, line)){
    length=line.length();
    //If the line isn't of the expected length, throw it
    if (length!=width){
      throw "NOPE";
    }
    for (int x=0; x<width; x++){
      if (line[x]==' '){}
      else if (line[x]=='#'){
        grid.set(x,y, Cell::ALIVE);
      }
      //If the character is neither a '#' or a ' ', throw it
      else{
        throw "NOPE";
      }
    }
    y++;
  }
  inFile.close();
  return grid;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

void Zoo::save_ascii(std::string path, Grid grid){
  std::ofstream outfile;

  outfile.open(path);
  if (!std::ifstream(path).is_open()){
    throw "No file";
  }
  for (int i=0; i<grid.get_width(); i++){
    if (i==0){
      outfile<<grid.get_width();
    }
    else if (i==1){
      outfile<<" ";
    }
    else if (i==2){
      outfile<<grid.get_height();
    }
  }
  outfile<<"\n";
  for (int j=0; j<grid.get_height(); j++){
    for (int i=0; i<grid.get_width(); i++){
      if (grid.get(i, j)==Cell::ALIVE){
        outfile<<"#";
      }
      else{
        outfile<<" ";
      }
    }
    outfile<<"\n";
  }
  outfile.close();
}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */

Grid Zoo::load_binary(std::string path){
  std::streampos size;
  int width=0;
  int height=0;
  std::stringstream stream;

  std::ifstream file(path, std::ios::binary);
  if (!file) {
    file.close();
    throw "Binary file not found"; // terminate with error
  }
  if (file) {
    // get length of file:
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);
    char* buffer=new char [length];
    // read data as a block:
    file.read (buffer,length);
    for (int i=3; i>=0; i--){
      width+=(int) (buffer[i]);
    }
    for (int i=7; i>=4; i--){
      height+=(int) (buffer[i]);
    }
    Grid g(width, height);
    for (int i=8; i<length; i++){
      std::string s=std::bitset<8>(buffer[i]).to_string();
      int n=s.length();
      for (int j=n-1; j>=0; j--){
        stream<<s[j];
      }
    }
    const std::string observed = stream.str();
    //If there are not enough bits, it's malformed
    int numCells=height*width;
    int bitLength=observed.length();
    if (bitLength<numCells){
      delete [] buffer;
      file.close();
      throw "Malformed data";
    }
    int v=0;
    for (int i=0; i<height; i++){
      for (int j=0; j<width; j++){
        if (observed[v]=='1'){
          g.set(j, i, Cell::ALIVE);
        }
        v++;
      }
    }
    file.close();
    delete [] buffer;
    return g;
  }
  else{
    file.close();
    return 0;
  }
}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(std::string path, Grid g){
  std::ofstream outfile;

  outfile.open(path);
  if (!std::ifstream(path).is_open()){
    throw "No file";
  }
  int height=g.get_height();
  int width=g.get_width();
  int bHeight=g.get_height();
  int bWidth=g.get_width();
  std::string h=std::bitset<32>(bHeight).to_string();
  std::string w=std::bitset<32>(bWidth).to_string();
  std::stringstream mstream;
  std::stringstream stream;
  mstream<<w;
  mstream<<h;

  //Converting each of the cells into bit representations
  for (int y=0; y<height; y++){
    for (int x=0; x<width; x++){
      if (g.get(x, y)==Cell::ALIVE){
        stream<<"1";
      }
      else{
        stream<<"0";
      }
    }
  }
  std::string observed = stream.str();
  //Reversing the set of bits and putting it into the main stream
  int p=0;
  int n=observed.length()/8;
  int remain=observed.length()%8;
  if (remain!=0){
    n++;
  }
  for (int i=0; i<remain; i++){
    stream<<"0";
  }
  observed = stream.str();

  std::string s=mstream.str();

  //Getting the width
  std::stringstream stream1;
  for (int i=24; i<32; i++){
    stream1<<s[i];
  }
  std::string out = stream1.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());

  std::stringstream stream2;
  for (int i=16; i<24; i++){
    stream2<<s[i];
  }
  out = stream2.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());

  std::stringstream stream3;
  for (int i=8; i<16; i++){
    stream3<<s[i];
  }
  out = stream3.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());

  std::stringstream stream4;
  for (int i=0; i<8; i++){
    stream4<<s[i];
  }
  out = stream4.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());


  //Getting the height
  std::stringstream stream5;
  for (int i=56; i<64; i++){
    stream5<<s[i];
  }
  out = stream5.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());

  std::stringstream stream6;
  for (int i=48; i<56; i++){
    stream6<<s[i];
  }
  out = stream6.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());

  std::stringstream stream7;
  for (int i=40; i<48; i++){
    stream7<<s[i];
  }
  out = stream7.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());

  std::stringstream stream8;
  for (int i=32; i<40; i++){
    stream8<<s[i];
  }
  out = stream8.str();
  outfile<<(char)((std::bitset<8>(out)).to_ulong());

  for (int y=0; y<n; y++){

    std::stringstream stream9;
    for (int i=7; i>=0; i--){
      stream9<<observed[i+p];
    }
    out = stream9.str();
    outfile<<(char)((std::bitset<8>(out)).to_ulong());
    p+=8;
  }
  outfile.close();
}
