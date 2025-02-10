#include <SFML/Graphics.hpp>
#include "canvas.hpp"
#include "boid_simulation.hpp"

Canvas::Canvas(int window_width, int window_height, std::string window_title)
{
    sf::VideoMode video_mode(window_width, window_height);
    window_.create(video_mode, window_title); 
}

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}