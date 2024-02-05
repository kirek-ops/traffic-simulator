#include "manager.h"
#include <cmath>
#include <random>
#include <iostream>

std::mt19937 gen (1337);

std::uniform_int_distribution <int> distribution (0, 2);

Manager::Manager (sf::RenderWindow *_window, std::time_t _start) {
    window = _window;
    start = _start;
    lst_gen = 0;
}

void Manager::create (int road) {
    std::uniform_real_distribution <double> dist (1, 100);
    double speed0 = dist(gen);
    double acceleration = dist(gen);

    std::cout << speed0 << " " << acceleration << std::endl;

    Car newCar (window, 0, road, speed0, acceleration, 10);
    cars.push_back(newCar);
}

const float COUNTDOWN = 1;

void Manager::process () {
    auto timer = std::chrono::system_clock::now();
    std::time_t curTime = std::chrono::system_clock::to_time_t(timer);
    
    if (curTime - lst_gen > COUNTDOWN) {
        int road1 = distribution(gen);
        create(road1); 
        int road2 = distribution(gen);
        while (road2 == road1) road2 = distribution(gen);
        create(road2);
        lst_gen = curTime;
    }

    for (int i = 0; i < cars.size(); ++i) {
        if (!cars[i].move()) {
            std::swap(cars[i], cars.back()); 
            cars.pop_back();
        }
    } 

    sf::sleep(sf::milliseconds(10));
}