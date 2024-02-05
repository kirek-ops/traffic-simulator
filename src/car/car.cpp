#include "car.h"
#include <iostream>
#include <cmath>

Car::Car () {
    type = -1; road = 0;
    speed = 0; max_speed = 0;
    acceleration = 0;
    x = 0; y = 0;
    part_of_route = -1;
    smooth_change_road = 0; to_road = -1;
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
    rotation = 270;
    smooth_change_road = 0; to_road = -1;

    Radius = (int)(window->getSize().x / 8);
    cirX = (int)(window->getSize().x / 4);
    cirY = (int)(window->getSize().y / 2) - 100;
    RoadWidth = 120;
    pi = std::acos(-1); 

    part_of_route = 0;   
    
    x = (int)(window->getSize().x) - 52;
    y = cirY - Radius - 10 - road * RoadWidth / 3;
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
    to_road = road;
    smooth_change_road = 1;
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

bool Car::move () {
    if (type == 0) {
        sf::Texture texture;
        try {
            if (!texture.loadFromFile("images/car1.png")) {
                throw std::invalid_argument("Failed Loading From File");
            }
        }
        catch (const std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            exit(-1);
        }

        sf::Sprite sprite (texture);
        sprite.setPosition(x, y);
        sprite.setRotation(rotation);
        window->draw(sprite);
        
        if (part_of_route == 0) {
            x -= speed;
            speed = std::min(max_speed, speed + acceleration);
        }
        else if (part_of_route == 1) {
            float omega = speed / Radius / pi * 180;
            rotation -= omega;
            x = cirX - (Radius + 5 + road * RoadWidth / 3) * std::cos((rotation - 180) / 180 * pi);
            y = cirY - (Radius + 10 + road * RoadWidth / 3) * std::sin((rotation - 180) / 180 * pi);
            speed = std::min(max_speed, speed + acceleration);
        }
        else if (part_of_route == 2) {
            x += speed;
            speed = std::min(max_speed, speed + acceleration);
        }
        else {
            exit(-1);
        }

        // change part of route
        if (x - speed < cirX && y < cirY && part_of_route != 1) {
            part_of_route = 1;
        }
        else if (x > cirX && y > cirY && part_of_route != 2) {
            part_of_route = 2;
            rotation = 90;
        }
        else if (x > window->getSize().x) {
            part_of_route = -1;
            return 0;
        }

        return 1;
    }
}

Car::~Car () {
    
}