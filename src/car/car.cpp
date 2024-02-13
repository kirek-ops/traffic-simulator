#include "car.h"
#include <iostream>
#include <cmath>

Car::Car () {
    road = 0;
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
    y = cirY - Radius - 20 - road * RoadWidth / 3;
}

void Car::extreme_stop (double dist, Car car) {
    extreme_stop_time = clock() + CLOCKS_PER_SEC * 2 / 3 * (80 - dist) / (car.speed - speed);
    acceleration = (car.speed - speed) / (2 / 3 * (80 - dist) / (car.speed - speed)) + car.acceleration;
    after_stop_acceleration = car.acceleration;
}

double Car::dist (const Car &other) {
    double result = 12345678;
    if (part_of_route == 0) {
        switch (other.part_of_route) {
            case 0:
                result = other.x - x;
                if (result < 0) result = 12345678;
                break;
            case 1: 
                result = (x - cirX) + -atan2((cirX - other.x) / Radius, (cirY - other.y) / Radius) * Radius;
                break;
            case 2: 
                result = Radius * pi + x - cirX + other.x - cirX;
            default:
                break;
        }
    }
    else if (part_of_route == 1) {
        switch (other.part_of_route) {
            case 0:
                result = 12345678;
                break;
            case 1: 
                result = -atan2((cirX - other.x) / Radius, (cirY - other.y) / Radius) * Radius - (-atan2((cirX - x) / Radius, (cirY - y) / Radius) * Radius);
                break;
            case 2:
                result = pi * Radius - (-atan2((cirX - x) / Radius, (cirY - y) / Radius) * Radius) + other.x - cirX;
                break;
            default:
                break;
        }
    }
    else if (part_of_route == 2) {
        switch (other.part_of_route) {
            case 0:
                result = 12345678;
                break;
            case 1: 
                result = 12345678;
                break;
            case 2:
                result = other.x - x;
                break;
            default:
                break;
        }
    }
    else {
        exit(-1);
    }
    return result;
} 

bool Car::move () {
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

    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    sprite.setPosition(x, y);
    sprite.setRotation(rotation);

    sf::CircleShape cen (10); cen.setPosition(cirX, cirY); window->draw(cen);
    
    window->draw(sprite);
    
    float omega;

    switch (part_of_route) {
        case 0:
            x -= speed;
            speed = std::min(max_speed, speed + acceleration);
            break;
        case 1:
            omega = speed / Radius / pi * 180;
            rotation -= omega;
            x = cirX - (Radius + 20 + road * RoadWidth / 3) * std::cos((rotation - 180) / 180 * pi);
            y = cirY - (Radius + 20 + road * RoadWidth / 3) * std::sin((rotation - 180) / 180 * pi);
            speed = std::min(max_speed, speed + acceleration);
            break;
        case 2:
            x += speed;
            speed = std::min(max_speed, speed + acceleration);
            break;
        default:
            exit(-1);
    }

    if (clock() == extreme_stop_time) {
        acceleration = after_stop_acceleration;
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

Car::~Car () {
    
}