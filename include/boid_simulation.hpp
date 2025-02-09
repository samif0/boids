#include <unordered_map>
#include <string>
#include "Boid.hpp"

#ifndef BOID_SIMULATION_H
#define BOID_SIMULATION_H

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
    void draw();
    std::unordered_map<unsigned int, Boid> boids;
public:
    boid_simulation(boid_simulation_config * boid_sim_cfg);
    ~boid_simulation();
    void start();
    void stop();
    void resume();
    void pause();
};

#endif