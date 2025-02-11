#include "grid.hpp"

Grid
::Grid
()
    : grid_width_(DEFAULT_GRID_SIZE),
      grid_height_(DEFAULT_GRID_SIZE), 
      grid_depth_(0), 
      ndim_(DEFAULT_NUM_DIMENSION), 
      defaulted_(true)
{
    grid2d.resize(boost::extents[grid_width_][grid_height_]);
}

Grid
::Grid
(int grid_width, int grid_height, int grid_depth, int ndim) 
    : grid_width_(grid_width), 
      grid_height_(grid_height), 
      grid_depth_(grid_depth), 
      ndim_(ndim),
      defaulted_(false)
{
    if(ndim_ == 2){
        grid2d.resize(boost::extents[grid_width_][grid_height_]);
    } else if(ndim_ == 3) {
        grid3d.resize(boost::extents[grid_width_][grid_height_][grid_depth_]);
    } else {
        throw std::invalid_argument("Invalid number of dimensions");
    }
}

Grid
::~Grid
()
{
}