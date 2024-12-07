#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <ctime>

#include "car/car.h"
#include "manager/manager.h"

void updateBackgroundSize(sf::Sprite &background, int screenWidth, int screenHeight) {
    // Directly scale to exactly match window dimensions
    background.setScale(
            static_cast<float>(screenWidth) / background.getTexture()->getSize().x,
            static_cast<float>(screenHeight) / background.getTexture()->getSize().y
    );

    background.setPosition(0, 0);
}

int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int screenWidth = desktopMode.width;
    int screenHeight = desktopMode.height;

    sf::RenderWindow window (sf::VideoMode(screenWidth, screenHeight), "Traffic Simulator", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    try {
        if (!backgroundTexture.loadFromFile("images/background.png")) {
            throw std::runtime_error("Failed to load background image");
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    sf::Sprite background(backgroundTexture);
    updateBackgroundSize(background, screenWidth, screenHeight);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                screenWidth = event.size.width;
                screenHeight = event.size.height;
                updateBackgroundSize(background, screenWidth, screenHeight);
            }
        }

        window.clear();
        window.draw(background);
        window.display();
    }
    return 0;
}