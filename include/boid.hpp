#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>


class Boid {
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    unsigned int species;
    float max_speed = 50.0f;
    float max_force = 5.0f;
    float current_rotation;

public:
    Boid(float x, float y);
    void apply_force(const sf::Vector2f& force);
    void seek(const sf::Vector2f& target, float weight);
    void flee(const sf::Vector2f& position, float distance, float weight);
    void align(const sf::Vector2f& average_velocity, float weight);
    void update(float delta_time);
    bool is_neighbor(const Boid& other, float distance);
    void render(sf::RenderWindow& window, float delta_time);
    sf::Vector2f& get_position();
    sf::Vector2f& get_velocity();
    sf::Vector2f& get_acceleration();
    float get_max_speed() { return max_speed; }
    unsigned int get_species() { return species; }
    void handle_collision(float width, float height);
};

#endif