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
    sf::RenderWindow& get_window() { return window_; }
    Canvas(int window_width, int window_height, sf::String window_title);
    Canvas();
    ~Canvas();
};
#endif