#include "resource.hpp"
#include "boid_simulation.hpp"
#include "canvas.hpp"
#include <iostream>
#include <random>
#include <unordered_map>

// helpers 
float magnitude(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalize(const sf::Vector2f& v) {
    float mag = magnitude(v);
    if (mag > 0) {
        return v / mag;
    }
    return v;
}

void limit(sf::Vector2f& v, float max) {
    float mag = magnitude(v);
    if (mag > max) {
        v = v / mag * max;
    }
}

float calculate_distance(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    sf::Vector2f diff = v1 - v2;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}


boid_simulation::boid_simulation(boid_simulation_config *boid_sim_cfg) : 
    boid_sim_cfg_(boid_sim_cfg),
    cvs_(boid_sim_cfg->window_width, boid_sim_cfg->window_height
        , boid_sim_cfg->window_title)
{
    boid_sim_state_ = new boid_simulation_state();
    boid_sim_state_->last_window_size = sf::Vector2f(boid_sim_cfg->window_width, boid_sim_cfg->window_height);
}

boid_simulation::~boid_simulation(){
}


void boid_simulation::handle_update_boids(sf::RenderWindow * window){
    for(auto boid_pair : this->boids_) {
        Boid * boid = boid_pair.second;

        sf::Vector2f separation_force(0, 0);
        sf::Vector2f alignment_force(0, 0);
        sf::Vector2f cohesion_force(0, 0);
        
        int separation_count, alignment_count, cohesion_count = 0;

        sf::Vector2f average_pos(0, 0);
        sf::Vector2f average_vel(0, 0);


        //TODO: optimize by bucketizing regions of the environment providing 
        // a smaller search space and introducing locality
        for(auto boid_pair_in : this->boids_) {
            Boid * other = boid_pair_in.second;
            if(boid != other){
                if(boid->is_neighbor(*other, 20.0)) {
                    // Separation - higher weight for same species (flock members)
                    if(boid->get_species() == other->get_species()) {
                        boid->flee(other->get_position(), 35.0, 6);
                    } else {
                        // Different species - stronger avoidance
                        boid->flee(other->get_position(), 50.0, 7); 
                    }
                    
                    // Alignment - only with same species
                    if(boid->get_species() == other->get_species()) {
                        boid->align(other->get_velocity(), 5);
                    }
                    
                    // Cohesion - stronger with same species
                    if(boid->get_species() == other->get_species()) {
                        boid->seek(other->get_position(), 3);
                    } else {
                        // weak attraction to different species (curiosity)
                        boid->seek(other->get_position(), 0.2f);
                    }
                }
            }
        }

        Resource * closest_resource = nullptr;
        float closest_dist = FLT_MAX;
        for(auto res_pair : this->boid_sim_state_->resources_) {
            Resource * resource = res_pair.second;

            //TODO: better measurement of distance and resource collision
            // needs to be formulated maybe based on shape size an
            float x_diff = std::abs(resource->get_pos().x - boid->get_position().x);
            float y_diff = std::abs(resource->get_pos().y - boid->get_position().y);
            float dist = std::sqrt((x_diff * x_diff) + (y_diff * y_diff));


            
            if(dist <= 2){
                resource->set_consumed(true);
                resource->set_removed(true); 
            }

            if(!(resource->is_consumed() || resource->is_removed())){
                if(dist < closest_dist){ 
                    closest_dist = dist;
                    closest_resource = resource;
                }
                resource->render(*window);
            }
            
        }

        //TODO: get closest resource (maybe let boid determine which resource is most feasible) with other determinants than proximity
        //TODO: add aggregate availabile variable, add depletion status as well for resources that have durability.
        if(closest_resource && !(closest_resource->is_consumed() || closest_resource->is_removed())){
            boid->seek(closest_resource->get_pos(), 3);
        }

        boid->update(0.016f);
        boid->handle_collision(this->boid_sim_cfg_->window_width, this->boid_sim_cfg_->window_height);
        boid->render(*window, 0.016f);
    }
}

void boid_simulation::handle_draw_grid(sf::RenderWindow * window)
{
    Grid * grid = &(this->cvs_.get_grid());
    int width = grid->get_grid_width();
    int height = grid->get_grid_height();

    //TODO: parameterize
    int cell_width = 5;
    float line_thickness = 1.0f; 
    sf::Color grid_color(180, 180, 180, 100);

    int horizontal_cells = width / cell_width;
    int vertical_cells = height / cell_width;

    sf::VertexArray lines(sf::Quads);
 
    //create horizontal lines
    for(int y = 0; y <= vertical_cells; y++){
        float y_pos = y * cell_width;
        lines.append(sf::Vertex(sf::Vector2f(0, y_pos), grid_color));
        lines.append(sf::Vertex(sf::Vector2f(width, y_pos), grid_color));
        lines.append(sf::Vertex(sf::Vector2f(width, y_pos + line_thickness), grid_color));
        lines.append(sf::Vertex(sf::Vector2f(0, y_pos + line_thickness), grid_color));
    }

    //create vertical lines
    for(int x = 0; x <= horizontal_cells; x++){
        float x_pos = x * cell_width;
        lines.append(sf::Vertex(sf::Vector2f(x_pos, 0), grid_color));
        lines.append(sf::Vertex(sf::Vector2f(x_pos, height), grid_color));
        lines.append(sf::Vertex(sf::Vector2f(x_pos + line_thickness, height), grid_color));
        lines.append(sf::Vertex(sf::Vector2f(x_pos + line_thickness, 0), grid_color));
    }
 
    window->draw(lines);
}

void boid_simulation::handle_single_frame_display(sf::RenderWindow * window)
{   
    window->clear(sf::Color::Black);

    /* Check and Update Simulation State */
    if(this->window_size_changed()){
        auto [x, y] = window->getSize();
        //TODO: update when I build out support for z axis.
        this->update_window_size(x, y, 0); 
        window->setView(sf::View(sf::FloatRect(0, 0, this->boid_sim_cfg_->window_width, this->boid_sim_cfg_->window_height))); 

    }

    /* Rendering */
    //TODO: turn grid into texture to improve perfomance 
    handle_draw_grid(window);
    handle_update_boids(window); 

    window->display();
}

void boid_simulation::handle_rendering(sf::RenderWindow * window)
{
    
    handle_single_frame_display(window);
}

void boid_simulation::start()
{
    sf::RenderWindow& window = cvs_.get_window();

    /* TODO: create better init; init boids */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(0.0f, this->boid_sim_cfg_->window_width);
    std::uniform_real_distribution<float> yDist(0.0f, this->boid_sim_cfg_->window_height);
    std::uniform_real_distribution<float> velDist(-100.0f, 100.0f); 

    for(unsigned int i = 0; i < 500; i++) {
        float x = xDist(gen);
        float y = yDist(gen);
        Boid * boid = new Boid(x, y);
        sf::Vector2f velocity(velDist(gen), velDist(gen));
        boid->render(window, 0.0016f); //TODO: calculate delta time based on target fps
        this->boids_[i] = boid;
        
    }

    /* TODO: create better init; init resources */
    for(unsigned int i = 0; i < 0; i++) {
        float x = xDist(gen);
        float y = yDist(gen);
        Resource * resource = new Resource(sf::Vector2f(x, y));
        resource->render(window);
        this->boid_sim_state_->resources_[i] = resource;
    }
 
    /*
   
    if boid simulation ever gets computationally expensive 
    move to multithreaded and shared memory approach

    std::thread thread([this, &window]() {
     
        handle_rendering(&window);
    });
    */

    window.setActive(true);

    window.setFramerateLimit(this->boid_sim_cfg_->window_frame_rate);

    // TODO: add vsync option later
    //window.setVerticalSyncEnabled(true); // Synchronizes with monitor refresh rate


    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        handle_rendering(&window); 
    }
}

void boid_simulation::stop()
{
}

void boid_simulation::resume()
{
}

void boid_simulation::pause()
{
}