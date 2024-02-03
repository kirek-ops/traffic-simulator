#pragma once
#include <SFML/Graphics.hpp>

class Route {
    private:
        sf::RenderWindow *window;
        sf::Texture *grassTexture;
        sf::Sprite grassSprite;
    public: 
        Route (sf::RenderWindow *_window, sf::Texture *_grassTexture);
        void show ();
};