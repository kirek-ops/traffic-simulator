#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <ctime>

// #include "grass/grass.h"
// #include "route/route.h"

#include "car/car.h"
#include "car_manager/manager.h"

int main () {
    // Variable
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Traffic Simulator");

    sf::Texture backgroundTexture;
    try {
        if (!backgroundTexture.loadFromFile("images/background.png")) {
            throw std::invalid_argument("Failed Loading From File");
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }

    sf::Sprite background (backgroundTexture);

    Manager manager (&window, clock());

    // Running
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        window.draw(background);
        manager.process();

        window.display();
    }
    return 0;
}