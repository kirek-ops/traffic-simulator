#include "manager.h"
#include <cmath>
#include <random>
#include <iostream>

Manager::Manager (sf::RenderWindow *_window, std::time_t _start) {
    window = _window;
    start = _start;
}

void Manager::create () {
    std::random_device rd;
    std::mt19937 gen (rd());

    std::uniform_int_distribution <int> distribution (0, 2);

    int road = distribution(gen);
    Car newCar (window, 0, road, 5, 1, 10);

    cars.push_back(newCar);
}

const float COUNTDOWN = 1;

void Manager::process () {
    auto timer = std::chrono::system_clock::now();
    std::time_t curTime = std::chrono::system_clock::to_time_t(timer);
    
    if ((curTime - start) / COUNTDOWN != lst_gen) {
        create();
        lst_gen = (curTime - start) / COUNTDOWN;
    }

    for (int i = 0; i < cars.size(); ++i) {
        if (!cars[i].move()) {
            std::swap(cars[i], cars.back()); 
            cars.pop_back();
        }
        if (cars.size() > 0) {
            sf::sleep(sf::milliseconds(30 / cars.size()));
        }
    } 
}