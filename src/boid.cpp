#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <SFML/System.hpp>
#include "boid.hpp"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Boid::Boid(float x, float y) {
    pos = sf::Vector2f(x, y);
    vel = sf::Vector2f(0.0f, 0.0f);
    acc = sf::Vector2f(0.0f, 0.0f);    
    species = rand() % 3; //TODO: Define number of species
}

void Boid::apply_force(const sf::Vector2f& force) {
    acc += force;
}

void Boid::seek(const sf::Vector2f& target, float weight = 1.0f) {
    sf::Vector2f desired = target - pos;
    float magnitude = std::sqrt(desired.x * desired.x + desired.y * desired.y);
    
    if (magnitude > 0) {
        desired = desired / magnitude * max_speed;
        
        sf::Vector2f steer = desired - vel;
        
        float steerMag = std::sqrt(steer.x * steer.x + steer.y * steer.y);
        if (steerMag > max_force) {
            steer = steer / steerMag * max_force;
        }
        
        steer.x *= weight;
        steer.y *= weight;
        
        apply_force(steer);
    }
}

void Boid::flee(const sf::Vector2f& position, float distance, float weight = 1.8f) {
    sf::Vector2f diff = pos - position;
    float d = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    
    if (d < distance) {
        float factor = 1.0f - (d / distance);
        
        sf::Vector2f desired = diff;
        if (d > 0) {
            desired = diff / d * max_speed; // Normalize and scale
        } else {
            desired.x = (float)(rand() % 200 - 100) / 100.0f;
            desired.y = (float)(rand() % 200 - 100) / 100.0f;
            float randomMag = std::sqrt(desired.x * desired.x + desired.y * desired.y);
            if (randomMag > 0) {
                desired = desired / randomMag * max_speed;
            }
        }
        
        sf::Vector2f steer = desired - vel;
        float steerMag = std::sqrt(steer.x * steer.x + steer.y * steer.y);
        if (steerMag > max_force) {
            steer = steer / steerMag * max_force;
        }
        
        steer.x *= weight * factor;
        steer.y *= weight * factor;
        
        apply_force(steer);
    }
}

void Boid::align(const sf::Vector2f& otherVelocity, float weight = 0.5f) {
    sf::Vector2f steer = otherVelocity - vel;
    
    float steerMag = std::sqrt(steer.x * steer.x + steer.y * steer.y);
    if (steerMag > max_force) {
        steer = steer / steerMag * max_force;
    }
    
    steer.x *= weight;
    steer.y *= weight;
    
    apply_force(steer);
}

void Boid::update(float deltaTime) {
    this->vel += this->acc * deltaTime;
    
    this->vel *= 0.995f; // Reduced damping
    
    float velMagnitude = std::sqrt(vel.x * vel.x + vel.y * vel.y);
    if (velMagnitude > max_speed) {
        vel = vel / velMagnitude * max_speed;
    }
    
    if (velMagnitude < max_speed * 0.25f) {
        // if barely moving, add a small boost in current direction
        if (velMagnitude > 0.01f) {
            sf::Vector2f boost = vel / velMagnitude * (max_speed * 0.1f);
            vel += boost;
        } else {
            vel.x += (float)(rand() % 200 - 100) / 100.0f * max_speed * 0.1f;
            vel.y += (float)(rand() % 200 - 100) / 100.0f * max_speed * 0.1f;
        }
    }
    
    this->pos += this->vel * deltaTime; 
    this->acc = sf::Vector2f(0.0f, 0.0f);
}

bool Boid::is_neighbor(const Boid& other, float distance){
    sf::Vector2f diff = pos - other.pos;
    float d = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    return d <= distance;
}

void Boid::render(sf::RenderWindow& window){
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    
    float size = 5.0f;
    triangle.setPoint(0, sf::Vector2f(size * 2, 0));     // Nose/head
    triangle.setPoint(1, sf::Vector2f(-size, size));     // Left corner
    triangle.setPoint(2, sf::Vector2f(-size, -size));    // Right corner
    
    triangle.setOrigin(0, 0);
   
    //TODO: impl smoother rotation
    float angle = 0;
    if (vel.x != 0 || vel.y != 0) {
        angle = std::atan2(vel.y, vel.x) * 180 / M_PI;
    }
    
    triangle.setPosition(pos);
    triangle.setRotation(angle);
    
    sf::Color color;
    switch(species){
        case 0: 
            color = sf::Color::Blue;
            break;
        case 1:
            color = sf::Color::Green;
            break;
        case 2:
            color = sf::Color::Red;
            break;
        default:
            color = sf::Color::White;
    }
    triangle.setFillColor(color);
    window.draw(triangle);
}

sf::Vector2f& Boid::get_position(){

    return this->pos;
}

sf::Vector2f& Boid::get_velocity(){
    return this->vel;
}

sf::Vector2f& Boid::get_acceleration(){
    return this->acc;
}

void Boid::handle_collision(float width, float height){
    if (this->pos.x < 0) this->pos.x = width;
    if (this->pos.x > width) this->pos.x = 0;
    if (this->pos.y < 0) this->pos.y = height;
    if (this->pos.y > height) this->pos.y = 0;
}