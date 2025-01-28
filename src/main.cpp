#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "boid.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
    window.setFramerateLimit(60);

    Boid boid(300,300);

    sf::Clock clock;

    sf::Vector2f initialVelocity(100.0f,100.0f);

    while (window.isOpen()) {
        sf::Event event;
        float deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();    
        }


        boid.matchVelocity(initialVelocity);
        boid.update(deltaTime);
        boid.handleCollision(800, 600);
        
        window.clear(sf::Color::Black);
        boid.render(window);
        window.display();
    }
    return 0;
}