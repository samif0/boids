#ifndef BOID_SIMULATION_HPP
#define BOID_SIMULATION_HPP

#include <unordered_map>
#include <string>
#include "canvas.hpp"
#include "Boid.hpp"

struct boid_simulation_config {
    int window_width;
    int window_height;
    int nboids;
    int window_frame_rate;
    std::string window_title;
};

class boid_simulation
{
private:
    boid_simulation_config * boid_sim_cfg_;
    std::unordered_map<unsigned int, Boid> boids_;
    Canvas cvs_;
    void handle_rendering(sf::RenderWindow * window);
    void handle_physics();
public:
    boid_simulation(boid_simulation_config * boid_sim_cfg);
    ~boid_simulation();
    void start();
    void stop();
    void resume();
    void pause();
};

#endif