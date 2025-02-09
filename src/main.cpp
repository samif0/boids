#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <math.h>
#include "boid.hpp"
#include "boid_simulation.hpp"


std::vector<Boid> generateRandomNBoids(int nBoids, float windowWidth, float windowHeight) {
    std::vector<Boid> boids;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(0.0f, windowWidth);
    std::uniform_real_distribution<float> yDist(0.0f, windowHeight);
    std::uniform_real_distribution<float> velDist(-50.0f, 50.0f); 

    for(int i = 0; i < nBoids; i++) {
        float x = xDist(gen);
        float y = yDist(gen);
        Boid boid(x, y);
        sf::Vector2f velocity(velDist(gen), velDist(gen));
        boid.seek(sf::Vector2f(x + velocity.x, y + velocity.y));
        boid.update(0.016f);
        boids.push_back(boid);
    }
    return boids;
}

int main() {

    boid_simulation_config * boid_sim_config = new boid_simulation_config;
    boid_sim_config->nboids = 100;
    boid_sim_config->window_width = 800;
    boid_sim_config->window_height = 800;
    boid_sim_config->window_frame_rate = 60;
    boid_sim_config->window_title = "Boids";
     
    
    boid_simulation boid_sim(boid_sim_config);

   
    //TODO: move into boid simulation because I need to have the simulation draw onto the window.
    sf::RenderWindow window(
        sf::VideoMode(boid_sim_config->window_width, boid_sim_config->window_height),
        boid_sim_config->window_title);
     

    std::vector<Boid> boids = generateRandomNBoids(boid_sim_config->nboids, boid_sim_config->window_width, boid_sim_config->window_height);
    window.setFramerateLimit(boid_sim_config->window_frame_rate);

    delete boid_sim_config;
    boid_sim_config = nullptr;

    // -- replace below with simulation --

    sf::Clock clock;
    bool isMousePressed = false;

    sf::Vector2f initialVelocity(100.0f,100.0f); 

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isMousePressed = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isMousePressed = false;
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for(auto& boid : boids) {
            sf::Vector2f avgVelocity(0, 0);
            int neighborCount = 0;
            
            for(Boid other : boids) {
                if (&other != &boid) {
                    float dx = other.getPosition().x - boid.getPosition().x;
                    float dy = other.getPosition().y - boid.getPosition().y;
                    float distance = std::sqrt(dx*dx + dy*dy);
                    
                    if (distance < 100.0f) {
                        avgVelocity += other.getVelocity();
                        neighborCount++;
                    }
                }
            }

            if (neighborCount > 0) {
                avgVelocity /= static_cast<float>(neighborCount);
                boid.matchVelocity(avgVelocity);
            }

            if (isMousePressed) {
                boid.seek(sf::Vector2f(static_cast<float>(mousePos.x), 
                                     static_cast<float>(mousePos.y)));
            }

            boid.update(deltaTime);
            boid.handleCollision(800.0f, 600.0f);
        }

        window.clear(sf::Color::Black);
        for(Boid boid : boids) {
            boid.render(window);
        }
        window.display();
    }
    return 0;
}