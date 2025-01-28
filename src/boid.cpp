#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "boid.hpp"
#include <cmath>


Boid::Boid(float x, float y) {
    pos = sf::Vector2f(x, y);
    vel = sf::Vector2f(0.0f, 0.0f);
    acc = sf::Vector2f(1.0f, 0.0f);
}

/*
* TODO: impl 
*/
void Boid::seek(const sf::Vector2f& target){
    sf::Vector2f desired = target - pos;
    float magnitude = std::sqrt(desired.x * desired.x + desired.y * desired.y);
    
    if (magnitude > 0) {
        desired = desired / magnitude * maxSpeed;
        sf::Vector2f steer = desired - vel;
        // Limit steering force
        float steerMag = std::sqrt(steer.x * steer.x + steer.y * steer.y);
        if (steerMag > maxSpeed) {
            steer = steer / steerMag * maxSpeed;
        }
        acc += steer;
    }
}
void Boid::flee(const sf::Vector2f& position, float distance){
    sf::Vector2f diff = pos - position;
    float d = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    
    if (d < distance) {
        sf::Vector2f desired = diff / d * maxSpeed;
        sf::Vector2f steer = desired - vel;
        float steerMag = std::sqrt(steer.x * steer.x + steer.y * steer.y);
        if (steerMag > maxSpeed) {
            steer = steer / steerMag * maxSpeed;
        }
        acc += steer;
    }
}
void Boid::matchVelocity(const sf::Vector2f& averageVelocity){
    sf::Vector2f steer = averageVelocity - vel;
    float steerMag = std::sqrt(steer.x * steer.x + steer.y * steer.y);
    if (steerMag > maxSpeed) {
        steer = steer / steerMag * maxSpeed;
    }
    acc += steer * 0.5f; // Reduced influence for smoother movement
}
void Boid::update(float deltaTime){
    this->vel += this->acc * deltaTime;
    this->vel *= 0.99f; // Friction/damping
    if (this->vel.x > maxSpeed) this->vel.x = maxSpeed;
    if (this->vel.y > maxSpeed) this->vel.y = maxSpeed;
    
    this->pos += this->vel * deltaTime;
    this->acc = sf::Vector2f(0.0f, 0.0f);
}
void Boid::render(sf::RenderWindow& window){
    sf::CircleShape shape(10.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(this->pos);
    window.draw(shape);
}
const sf::Vector2f& Boid::getPosition(){
    return this->pos;
}
const sf::Vector2f& Boid::getVelocity(){
    return this->vel;
}
const sf::Vector2f& Boid::getAcceleration(){
    return this->acc;
}
void Boid::handleCollision(float width, float height){
    if (this->pos.x < 0) this->pos.x = width;
    if (this->pos.x > width) this->pos.x = 0;
    if (this->pos.y < 0) this->pos.y = height;
    if (this->pos.y > height) this->pos.y = 0;
}