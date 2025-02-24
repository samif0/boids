#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"
#include "boost/multi_array.hpp"
#include <stdexcept>

inline int const DEFAULT_GRID_SIZE = 10;
inline int const  DEFAULT_NUM_DIMENSION = 2;

class Grid
{
private:
    int ndim_;
    int grid_width_;
    int grid_height_; 
    int grid_depth_;
    bool defaulted_;
    boost::multi_array<Cell, 2> grid2d;
    boost::multi_array<Cell, 3> grid3d;
public:
    Grid();
    Grid(int grid_width, int grid_height, int grid_depth, int ndim);
    ~Grid();
    boost::multi_array<Cell, 2> initialize2d();
    boost::multi_array<Cell, 3> initialize3d();

    Cell& operator()(int x, int y, int z = 0) {
        if (ndim_ == 2) {
            return grid2d[x][y];
        } else if (ndim_ == 3) {
            return grid3d[x][y][z];
        } else {
            throw std::runtime_error("Invalid number of dimensions");
        }
    }


    const Cell& operator()(int x, int y, int z = 0) const{
        if (ndim_ == 2) {
            return grid2d[x][y];
        } else if (ndim_ == 3) {
            return grid3d[x][y][z];
        } else {
            throw std::runtime_error("Invalid number of dimensions");
        }
    }
};

#endif