#include <SFML/Graphics.hpp>
#include "../car/car.h"
#include <vector>
#include <chrono>
#include <ctime>

class Manager {
    private:
        sf::RenderWindow *window;
        std::vector <Car> cars;
        time_t start;
        time_t lst_gen = 0;

    public:
        Manager (sf::RenderWindow *_window, time_t _start);
        void create (int road);
        void process ();
        std::pair <double, Car> check_around (int car);
};