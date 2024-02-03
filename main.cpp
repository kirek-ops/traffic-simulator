#include <SFML/Graphics.hpp>
#include "src/grass/grass.h"
#include "src/route/route.h"
#include <iostream>

int main () {
    // Variable
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Traffic Simulator");

    sf::Texture grassTexture;
    try {
        if (!grassTexture.loadFromFile("images/grass.png")) {
            throw std::invalid_argument("Failed Loading From File");
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }

    Grass grass (&window, &grassTexture);
    Route route (&window);

    // Running
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        grass.show(); route.show(); 
        window.display();
    }
    return 0;
}