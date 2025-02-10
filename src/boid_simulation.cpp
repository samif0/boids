#include "boid_simulation.hpp"
#include "canvas.hpp"
#include <thread>

boid_simulation::boid_simulation(boid_simulation_config *boid_sim_cfg) : 
    boid_sim_cfg_(boid_sim_cfg),
    cvs_(boid_sim_cfg->window_width, boid_sim_cfg->window_height
        , boid_sim_cfg->window_title)
{
}

boid_simulation::~boid_simulation(){
}

void boid_simulation::handle_rendering(sf::RenderWindow * window)
{
    window->setActive(true);

    while(window->isOpen())
    {
        window->clear();
        window->display();
    }
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
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            window.clear();
            window.display();
        }
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