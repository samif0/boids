#include "boid_simulation.hpp"
#include "canvas.hpp"
#include <iostream>

boid_simulation::boid_simulation(boid_simulation_config *boid_sim_cfg) : 
    boid_sim_cfg_(boid_sim_cfg),
    cvs_(boid_sim_cfg->window_width, boid_sim_cfg->window_height
        , boid_sim_cfg->window_title)
{
}

boid_simulation::~boid_simulation(){
}


void boid_simulation::handle_draw_grid(sf::RenderWindow * window)
{
    Grid * grid = &(this->cvs_.get_grid());
    int width = grid->get_grid_width();
    int height = grid->get_grid_height();

    //TODO: parameterize
    int cell_width = 10;
    float line_thickness = 1.0f; 
    sf::Color grid_color(180, 180, 180, 100);

    int horizontal_cells = width / cell_width;
    int vertical_cells = height / cell_width;


    //TODO: what is a vertex array?
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
    window->setView(sf::View(sf::FloatRect(0, 0, this->boid_sim_cfg_->window_width, this->boid_sim_cfg_->window_height))); 

    auto [x, y] = window->getSize();
    this->update_window_size(x, y, 0); //TODO: update when I build out support for z axis.
    
    handle_draw_grid(window);
    window->display();
}

void boid_simulation::handle_rendering(sf::RenderWindow * window)
{
    
    handle_single_frame_display(window);
}

void boid_simulation::start()
{
    sf::RenderWindow& window = cvs_.get_window();
 
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