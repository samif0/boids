#include "resource.hpp"




void Resource::render(sf::RenderWindow& window) {
    sf::CircleShape shape(3.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(this->pos);
    window.draw(shape);
}