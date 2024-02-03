#pragma once
#include <SFML/Graphics.hpp>

class Grass {
    private:
        sf::RenderWindow *window;
        sf::Texture *grassTexture;
        sf::Sprite grassSprite;
    public: 
        Grass (sf::RenderWindow *_window, sf::Texture *_grassTexture);
        void show ();
};