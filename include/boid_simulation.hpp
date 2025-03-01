#ifndef BOID_SIMULATION_HPP
#define BOID_SIMULATION_HPP

#include <string>
#include <unordered_map>
#include <SFML/System.hpp>
#include "resource.hpp"
#include "canvas.hpp"
#include "boid.hpp"

struct boid_simulation_config {
    int window_width;
    int window_height;
    int nboids;
    int window_frame_rate;
    sf::String window_title;
};

struct boid_simulation_state {
    sf::Vector2f last_window_size;
    std::unordered_map<unsigned int, Resource*> resources_;
};

class boid_simulation
{
private:
    boid_simulation_config * boid_sim_cfg_;
    boid_simulation_state * boid_sim_state_;
    //TODO: most likely a better data structure/storage strategy for object updates. do some research here.
    std::unordered_map<unsigned int, Boid*> boids_;
    
    Canvas cvs_;
    //TODO: Consider making the window a class member or maybe better 
    // kept under the canvas though and passed around handle functions; do some best practice research here.
    void handle_update_boids(sf::RenderWindow * window);
    void handle_draw_grid(sf::RenderWindow * window);
    void handle_single_frame_display(sf::RenderWindow * window);
    void handle_rendering(sf::RenderWindow * window); 
public:
    boid_simulation(boid_simulation_config * boid_sim_cfg);
    ~boid_simulation();
    boid_simulation_config * get_config() { return this->boid_sim_cfg_; }
    boid_simulation_state * get_state() { return this->boid_sim_state_; }
    void update_window_size(int u_width, int u_height, int u_depth) { 
        this->boid_sim_cfg_->window_width = u_width;
        this->boid_sim_cfg_->window_height = u_height;
        cvs_.update_canvas_size(u_width, u_height, u_depth);
    }

    bool window_size_changed() {
        return this->boid_sim_state_->last_window_size.x != this->boid_sim_cfg_->window_width ||
               this->boid_sim_state_->last_window_size.y != this->boid_sim_cfg_->window_height;
    }

    void start();
    void stop();
    void resume();
    void pause();
};

#endif