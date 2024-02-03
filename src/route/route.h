#pragma once
#include <SFML/Graphics.hpp>

class Route {
    private:
        sf::RenderWindow *window;
    public:
        Route (sf::RenderWindow *_window);
        void show ();
};