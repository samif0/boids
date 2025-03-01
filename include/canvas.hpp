#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "grid.hpp"

class Canvas
{
private:
    sf::RenderWindow window_;
    Grid grid_;
public:
    Canvas(int window_width, int window_height, sf::String window_title);
    Canvas();
    ~Canvas();

    sf::RenderWindow& get_window() { return window_; }
    Grid& get_grid() { return grid_; }
    void update_canvas_size(int u_width, int u_height, int u_depth) {
        this->grid_.update_grid_size(u_width, u_height, u_depth);
    }
};
#endif