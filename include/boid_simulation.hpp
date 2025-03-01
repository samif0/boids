#ifndef BOID_SIMULATION_HPP
#define BOID_SIMULATION_HPP

#include <string>
#include <unordered_map>
#include <SFML/System.hpp>
#include "canvas.hpp"
#include "boid.hpp"

struct boid_simulation_config {
    int window_width;
    int window_height;
    int nboids;
    int window_frame_rate;
    sf::String window_title;
};

class boid_simulation
{
private:
    boid_simulation_config * boid_sim_cfg_;
    std::unordered_map<unsigned int, Boid> boids_;
    Canvas cvs_;
    void handle_single_frame_display(sf::RenderWindow * window);
    void handle_draw_grid(sf::RenderWindow * window);
    void handle_rendering(sf::RenderWindow * window); 
public:
    boid_simulation(boid_simulation_config * boid_sim_cfg);
    ~boid_simulation();
    boid_simulation_config * get_config() { return this->boid_sim_cfg_; }
    void update_window_size(int u_width, int u_height, int u_depth) { 
        this->boid_sim_cfg_->window_width = u_width;
        this->boid_sim_cfg_->window_height = u_height;
        cvs_.update_canvas_size(u_width, u_height, u_depth);
    }
    void start();
    void stop();
    void resume();
    void pause();
};

#endif