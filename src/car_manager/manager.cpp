#include "manager.h"
#include <cmath>
#include <random>
#include <iostream>
#include <ctime>

std::mt19937 gen (1337);

std::uniform_int_distribution <int> distribution (0, 2);

Manager::Manager (sf::RenderWindow *_window, time_t _start) {
    window = _window;
    start = _start;
    lst_gen = 0;
}

void Manager::create (int road) {
    std::uniform_real_distribution <double> dist (0.1, 0.3);
    double speed0 = dist(gen);
    double acceleration = 0.0003;

    Car newCar (window, 0, road, speed0, acceleration);

    for (int i = 0; i < cars.size(); ++i) {
        if (cars[i].road != road) continue;
        if (cars[i].dist(newCar) < 80) {
            return;
        }
    }

    cars.push_back(newCar);
}

std::pair <double, Car> Manager::check_around (int car) {
    std::pair <double, Car> best = {12345678, Car ()};
    for (int i = 0; i < cars.size(); ++i) { 
        if (cars[i].road != cars[car].road || i == car) continue;
        double d = cars[i].dist(cars[car]);
        if (d < 80 && best.first > d) {
            // std::cout << cars[car].speed << " " << cars[i].speed << " " << cars[car].extreme_stop_time << " " << cars[i].extreme_stop_time << std::endl; 
            best = {d, cars[i]};
        }
    }
    return best;
}

int Manager::check_car (int x, int y) {
    for (int i = 0; i < cars.size(); ++i) {
        if (abs(x - cars[i].x) < 30 && abs(y - cars[i].y) < 15) {
            return i;
        }
    }
    return -1;
}

void Manager::stop_car (int id) {
    cars[id].mem_speed = cars[id].speed;
    cars[id].speed = 0.01;
    cars[id].click_stop_time = clock() + CLOCKS_PER_SEC * 2;
}

void Manager::process () {
    std::time_t curTime = clock();
    // static int ok = 0;

    // if (!lst_gen) {
    //     Car car (window, 0, 0, 0.1, 0.00001);
    //     cars.push_back(car);
    //     lst_gen = curTime;
    // }
    // else if ((float)(curTime - lst_gen) / CLOCKS_PER_SEC > 0.6 && !ok) {
    //     Car car (window, 0, 0, 0.2, 0.00001);
    //     cars.push_back(car);
    //     lst_gen = curTime;
    //     ok = 1;
    // }

    if (!lst_gen || (float)(curTime - lst_gen) / CLOCKS_PER_SEC > 0.2) {
        create(rand() % 3); 
        lst_gen = curTime;
    }

    // if (cars.size() > 1) {
    //     std::cout << cars[0].dist(cars[1]) << std::endl;
    // }

    for (int i = 0; i < cars.size(); ++i) {
        auto [d, car] = check_around(i);
        if (d < 80) {
            cars[i].extreme_stop(d, car);
        }
        if (!cars[i].move()) {
            cars.erase(cars.begin() + i, cars.begin() + i + 1);
            --i;
        }
    } 
}