#include <SFML/Graphics.hpp>
#include "../car/car.h"
#include <vector>
#include <chrono>
#include <ctime>

class Manager {
    private:
        sf::RenderWindow *window;
        std::vector <Car> cars;
        std::time_t start;
        std::time_t lst_gen = 0;

    public:
        Manager (sf::RenderWindow *_window, std::time_t _start);
        void create (int road);
        void process ();
        bool is_around_car (int car);
};