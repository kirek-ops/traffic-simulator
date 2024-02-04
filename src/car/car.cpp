#include "car.h"
#include <iostream>
#include <cmath>

Car::Car () {
    type = -1; road = 0;
    speed = 0; max_speed = 0;
    acceleration = 0;
    x = 0; y = 0;
}

int Radius;
int cirX;
int cirY;
int RoadWidth;
double pi;

Car::Car (sf::RenderWindow *_window, int _type, int _road, float _speed, float _acceleration, float _max_speed) {
    type = _type;
    road = _road;
    speed = _speed;
    acceleration = _acceleration;
    max_speed = _max_speed;
    window = _window;

    
    Radius = (int)(window->getSize().x / 8);
    cirX = (int)(window->getSize().x / 4);
    cirY = (int)(window->getSize().y / 2) - 100;
    RoadWidth = 120;
    pi = std::acos(-1);    
    
    x = (int)(window->getSize().x) - 52;
    y = cirY - Radius - (road + 1) * 3 - road * RoadWidth / 3;
}

void Car::setX (float x) {
    this->x = x;
}

void Car::setY (float y) {
    this->y = y;
}

float Car::getX () {
    return x;
}

float Car::getY () {
    return y;
}

void Car::changeRoad (int road) {
    this->road = road;
}

int Car::getRoad () {
    return road;
}

void Car::changeSpeed (float speed) {
    this->speed = speed;
}

float Car::getSpeed () {
    return speed;
}
