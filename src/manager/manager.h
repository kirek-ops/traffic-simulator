#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <memory>
#include "../car/car.h"

class Manager {
private:
    std::vector <std::unique_ptr <Car>> cars;
public:
    Manager();
    void update ();
    void render (sf::RenderWindow &window);
    void checkClick (const sf::Vector2i &mousePos);
};

#endif
