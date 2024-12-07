#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <ctime>
z
// #include "grass/grass.h"
// #include "route/route.h"

#include "car/car.h"
#include "car_manager/manager.h"
#include "slider/slider.h"

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
    Slider slider (&window, 0.1, 10);

    // Running
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f click = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    int id = manager.check_car(click.x, click.y);
                    if (id != -1) {
                        manager.stop_car(id);
                    }
                    if (slider.is_on_slider(click)) {
                        slider.turn_on(click);
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                slider.turn_off();
            }
        }

        slider.process();
        manager.set_coeff(slider.get_coeff());

        window.clear();

        window.draw(background);
        manager.process();
        slider.draw();

        window.display();
    }
    return 0;
}
