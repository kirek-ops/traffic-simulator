#include "manager.h"
#include <cmath>
#include <random>
#include <iostream>
#include <ctime>

std::mt19937 gen (1337);

std::uniform_int_distribution <int> distribution (0, 2);

Manager::Manager (sf::RenderWindow *_window, std::time_t _start) {
    window = _window;
    start = _start;
    lst_gen = 0;
}

void Manager::create (int road) {
    std::uniform_real_distribution <double> dist (10, 12);
    double speed0 = dist(gen) - 10;
    double acceleration = std::max((double)0.005, dist(gen) - 11.5);

    std::cout << speed0 << " " << acceleration << std::endl;

    Car newCar (window, 0, road, speed0, acceleration, 5);
    cars.push_back(newCar);
}

double dist (float x, float y, float xx, float yy) {
    return (x - xx) * (x - xx) + (y - yy) * (y - yy);
}

bool Manager::is_around_car (int car) {
    for (int i = 0; i < cars.size(); ++i) {
        if (i == car || cars[i].road != cars[car].road) continue;
        if (dist(cars[car].x, cars[car].y, cars[i].x, cars[i].y) <= 15000) {
            cars[car].extreme_stop();
        }
    }
}

void Manager::process () {
    std::time_t curTime = clock();

    if (!lst_gen || (float)(curTime - lst_gen) / CLOCKS_PER_SEC > 0.4) {
        create(rand() % 3);
        lst_gen = curTime;
    }

    for (int i = 0; i < cars.size(); ++i) {
        if (is_around_car(i)) {

        }
        if (!cars[i].move()) {
            std::swap(cars[i], cars.back()); 
            cars.pop_back();
        }
    } 

    sf::sleep(sf::milliseconds(10));
}