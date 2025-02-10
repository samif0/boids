#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>

class Boid {
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float maxSpeed = 100.0f;

public:
    Boid(float x, float y);
    void seek(const sf::Vector2f& target);
    void flee(const sf::Vector2f& position, float distance);
    void matchVelocity(const sf::Vector2f& averageVelocity);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    sf::Vector2f& getPosition();
    sf::Vector2f& getVelocity();
    sf::Vector2f& getAcceleration();
    void handleCollision(float width, float height);
};

#endif