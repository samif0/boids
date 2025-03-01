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
    int grid_width_;
    int grid_height_; 
    int grid_depth_;
    int ndim_;
    bool defaulted_;
    boost::multi_array<Cell, 2> grid2d;
    boost::multi_array<Cell, 3> grid3d;
public:
    Grid();
    Grid(int grid_width, int grid_height, int grid_depth, int ndim);
    ~Grid();
    int get_grid_width() { return this->grid_width_; }
    int get_grid_height() { return this->grid_height_; }
    int get_grid_depth() { return this->grid_depth_; }
    int get_ndim() { return this->ndim_; }
    bool used_default() { return this->defaulted_; }
    void update_grid_size(int u_width, int u_height, int u_depth) {
        this->grid_width_ = u_width;
        this->grid_height_ = u_height;
        if(this->ndim_ == 2){
            grid2d.resize(boost::extents[grid_width_][grid_height_]);
        } else if(this->ndim_ == 3) {
            this->grid_depth_ = u_depth;
            grid3d.resize(boost::extents[grid_width_][grid_height_][grid_depth_]);
        } else {
            throw std::invalid_argument("Invalid number of dimensions");
        }
    }

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