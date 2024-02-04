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
        int lst_gen = -1;
    public:
        Manager (sf::RenderWindow *_window, std::time_t _start);
        void create ();
        void process ();
};