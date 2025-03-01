#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <SFML/Graphics.hpp>

class Resource {
    private:
        sf::Vector2f pos;
        bool consumed;
        bool removed;
    public:
        sf::Vector2f get_pos() { return pos; }
        bool is_consumed() { return consumed; }
        bool is_removed() { return removed; }
        //TODO: turn into enum?
        void set_consumed(bool consumed_state) { consumed = consumed_state; }
        void set_removed(bool removed_state) { removed = removed_state; }
        void render(sf::RenderWindow& window);
        Resource(sf::Vector2f pos) {
            this->pos = pos;
            consumed = false;
            removed = false;
        }
        ~Resource() {
            this->pos = sf::Vector2f(0, 0);
        }
};

#endif