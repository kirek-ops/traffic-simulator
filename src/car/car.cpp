#include "car.h"

Car::Car () {
    type = 0; road = 0;
    speed = 0; max_speed = 0;
    acceleration = 0;
    x = 0; y = 0;
    cirX = 0; cirY = 0;
}

Car::Car (int _type, int _road, float _speed, float _acceleration, float _max_speed, float _x, float _y, int _cirX, int _cirY) {
    type = _type;
    road = _road;
    speed = _speed;
    acceleration = _acceleration;
    max_speed = _max_speed;
    x = _x;
    y = _y;
    cirX = _cirX; cirY = _cirY;
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

void Car::move () {

}