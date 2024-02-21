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
    double acceleration = 0.0002;

    Car newCar (window, 0, road, speed0, acceleration);

    for (int i = 0; i < cars.size(); ++i) {
        if (cars[i].road != road) continue;
        if (cars[i].dist(newCar) < 150) {
            return;
        }
    }

    cars.push_back(newCar);
}

std::pair <double, Car> Manager::check_around (int car, int search_road) {
    std::pair <double, Car> best = {12345678, Car ()};
    for (int i = 0; i < cars.size(); ++i) { 
        if (i == car) continue;
        if ((cars[i].road == search_road && !cars[i].smooth_change_road) || (cars[i].smooth_change_road && cars[i].to_road == search_road)) {
            double d = 12345678;
            if (cars[car].speed > 0) {
                d = cars[i].dist(cars[car]);
            }
            else {
                d = cars[car].dist(cars[i]);
            }
            if (d < 100 && best.first > d) {
                best = std::make_pair(d, cars[i]);
            }
        }
    }
    return best;
}

float Manager::check_change (int car, int search_road) {
    float result = 12345678;
    for (int i = 0; i < cars.size(); ++i) { 
        if (i == car) continue;
        if ((cars[i].road == search_road && !cars[i].smooth_change_road) || (cars[i].smooth_change_road && cars[i].to_road == search_road)) {
            float dist = cars[i].dist(cars[car]);
            if (dist < 80 || cars[car].dist(cars[i]) < 70) {
                return -1;
            }
            if (result > dist) result = dist;
        }
    }
    return result;
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
    cars[id].speed = std::min(cars[id].speed, (float)0.05);
    cars[id].acceleration = 0;
    cars[id].stoped_car = clock() + CLOCKS_PER_SEC * 2;
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
    // else if ((float)(curTime - lst_gen) / CLOCKS_PER_SEC > 1 && !ok) {
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
        auto [d, car] = check_around(i, cars[i].road);
        if (d < 100) {
            if (!cars[i].smooth_change_road) {
                if (cars[i].road == 0) {
                    float dist = check_change(i, 1);
                    if (dist != -1) {
                        cars[i].change_road(1, coeff);
                    }
                    else {
                        cars[i].extreme_stop(d, car, coeff);
                    }
                }
                else if (cars[i].road == 1) {
                    float dist0 = check_change(i, 0);
                    float dist2 = check_change(i, 2);

                    if (cars[i].lst_road == 0 && dist2 != -1) {
                        cars[i].change_road(2, coeff);
                    }
                    else if (cars[i].lst_road == 2 && dist0 != -1) {
                        cars[i].change_road(0, coeff);
                    }
                    else if (dist0 != -1) {
                        cars[i].change_road(0, coeff);
                    }
                    else if (dist2 != -1) {
                        cars[i].change_road(2, coeff);
                    }
                    else {
                        cars[i].extreme_stop(d, car, coeff);
                    }
                }
                else {
                    float dist = check_change(i, 1);
                    if (dist != -1) {
                        cars[i].change_road(1, coeff);
                    }
                    else {
                        cars[i].extreme_stop(d, car, coeff);
                    }
                }
            }
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