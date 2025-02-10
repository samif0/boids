#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Canvas
{
private:
    sf::RenderWindow window_;
public:
    sf::RenderWindow& get_window() { return window_; }
    Canvas(int window_width, int window_height, std::string window_title);
    Canvas();
    ~Canvas();
};
#endif