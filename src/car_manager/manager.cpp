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
    double acceleration = 0.00003;

    Car newCar (window, 0, road, speed0, acceleration);

    for (int i = 0; i < cars.size(); ++i) {
        if (cars[i].road != road) continue;
        if (cars[i].dist(newCar) < 150) {
            return;
        }
    }

    cars.push_back(newCar);
}

std::pair <double, Car> Manager::check_around (int car) {
    std::pair <double, Car> best = {12345678, Car ()};
    for (int i = 0; i < cars.size(); ++i) { 
        if (cars[i].road != cars[car].road || i == car) continue;
        double d = 12345678;
        if (cars[car].speed > 0) {
            d = cars[i].dist(cars[car]);
        }
        else {
            d = cars[car].dist(cars[i]);
        }
        if (d < 100 && best.first > d) {
            best = {d, cars[i]};
        }
    }
    return best;
}

int Manager::check_car (float x, float y) {
    for (int i = 0; i < cars.size(); ++i) {
        if (abs(x - cars[i].x) < 25 && abs(y - cars[i].y) < 12) {
            return i;
        }
    }
    return -1;
}

void Manager::stop_car (int id) {
    cars[id].speed = std::min(cars[id].speed, (float)0.05 * coeff);
}

void Manager::process () {
    std::time_t curTime = clock();
    
    // testing two cars
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

    if (!lst_gen || (float)(curTime - lst_gen) / CLOCKS_PER_SEC > 0.4) {
        create(rand() % 3); 
        lst_gen = curTime;
    }

    for (int i = 0; i < cars.size(); ++i) {
        auto [d, car] = check_around(i);
        if (d < 100) {
            cars[i].extreme_stop(d, car, coeff);
        }
        if (!cars[i].move(coeff)) {
            cars.erase(cars.begin() + i, cars.begin() + i + 1);
            --i;
        }
    } 
}

void Manager::set_coeff (float _coeff) {
    coeff = _coeff;
}