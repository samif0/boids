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

    boid_sim.start(); 

    //std::vector<Boid> boids = generateRandomNBoids(boid_sim_config->nboids, boid_sim_config->window_width, boid_sim_config->window_height);

    boid_sim.stop();
    
    delete boid_sim_config;
    boid_sim_config = nullptr;
    return 0;
}