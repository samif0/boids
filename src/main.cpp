#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <random>
#include <math.h>
#include "boid.hpp"
#include "boid_simulation.hpp"


int main() {

    boid_simulation_config * boid_sim_config = new boid_simulation_config;
    boid_sim_config->nboids = 100;
    boid_sim_config->window_width = 1920;
    boid_sim_config->window_height = 1080;
    boid_sim_config->window_frame_rate = 60;
    std::string window_title_std_string = "Boids";
    const char * window_title_c_str = window_title_std_string.c_str();
    boid_sim_config->window_title = sf::String(window_title_c_str, std::locale("en_US"));
     
    
    boid_simulation boid_sim(boid_sim_config);

    boid_sim.start(); 
    boid_sim.stop();
    
    delete boid_sim_config;
    boid_sim_config = nullptr;
    return 0;
}