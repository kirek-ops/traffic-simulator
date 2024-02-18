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
        float coeff;

    public:
        Manager (sf::RenderWindow *_window, time_t _start);
        void create (int road);
        void process ();
        std::pair <double, Car> check_around (int car, int search_road);
        bool check_change (int car, int search_road);
        int check_car (float x, float y);
        void stop_car (int id);
        void set_coeff (float coeff);
};