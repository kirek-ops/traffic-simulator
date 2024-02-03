#include <SFML/Graphics.hpp>
#include "../car/car.h"
#include <vector>

class Manager {
    private:
        sf::RenderWindow *window;
        std::vector <Car> cars;
    public:
        Manager (sf::RenderWindow *_window);
        void create ();
        void process ();
};