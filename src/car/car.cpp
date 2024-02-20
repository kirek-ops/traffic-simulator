#include "car.h"
#include <iostream>
#include <cmath>

Car::Car () {
    road = 0;
    speed = 0;
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

Car::Car (sf::RenderWindow *_window, int _type, int _road, float _speed, float _acceleration) {
    road = _road;
    speed = _speed;
    acceleration = _acceleration;
    window = _window;
    rotation = 270;
    smooth_change_road = 0; to_road = -1;
    rotate_iter = 500;
    changed = -CLOCKS_PER_SEC;
    xystep = 0;

    Radius = (int)(window->getSize().x / 8);
    cirX = (int)(window->getSize().x / 4);
    cirY = (int)(window->getSize().y / 2) - 100;
    RoadWidth = 120;
    pi = std::acos(-1); 

    part_of_route = 0;   
    
    x = (int)(window->getSize().x) - 52;
    y = cirY - Radius - 20 - road * RoadWidth / 3;
}

void Car::extreme_stop (double dist, Car car, float coeff) {
    double time = 2 * (65 - dist) / (car.speed * coeff - speed * coeff);
    if (time < 0.0000000001) return;
    acceleration = (car.speed * coeff - speed * coeff) / time + car.acceleration;
    extreme_stop_time = clock() + time;
    after_stop_acceleration = car.acceleration;
    after_stop_speed = &car.speed;
}

double Car::dist (const Car &other) { // 12345678 invalid result
    double result = 12345678;
    if (part_of_route == 0) {
        switch (other.part_of_route) {
            case 0:
                result = other.x - x;
                if (result < 0) result = 12345678;
                break;
            case 1: 
                result = 12345678;
                break;
            case 2: 
                result = 12345678;
            default:
                break;
        }
    }
    else if (part_of_route == 1) {
        switch (other.part_of_route) {
            case 0:
                result = other.x - cirX + (270 - rotation) / 180 * pi * Radius;
                break;
            case 1: 
                result = (other.rotation - rotation) / 180 * pi * Radius;
                if (result < 0) result = 12345678;
                break;
            case 2:
                result = 12345678;
                break;
            default:
                break;
        }
    }
    else if (part_of_route == 2) {
        switch (other.part_of_route) {
            case 0:
                result = pi * Radius + x + other.x - cirX * 2;
                break;
            case 1: 
                result = x - cirX + (other.rotation - 90) / 180 * pi * Radius;
                break;
            case 2:
                result = x - other.x;
                if (result < 0) result = 12345678;
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
 
void Car::change_road (int target_road, float coeff) {
    rotate_iter = 60 / coeff;
    to_road = target_road;
    smooth_change_road = 1;
    iters_r = rotate_iter;
    iters_y = rotate_iter * 2;
    xystep = (float)RoadWidth / 3 / iters_y * (to_road > road ? -1 : +1);
    cur_rotation_type = 0;
    rotate = 20.0 / rotate_iter / coeff * (to_road > road ? -1 : +1);;

    changed = clock();
}

bool Car::move (float coeff) {
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

    window->draw(sprite);

    speed *= coeff; acceleration *= coeff;

    float omega;

    if (smooth_change_road) {
        if (cur_rotation_type == 0) {
            if (iters_r > 0) {
                iters_r--;
                rotation += rotate;
            }
            else {
                cur_rotation_type = 1;
                iters_r = rotate_iter;
            }
        }
        else if (cur_rotation_type == 1) {
            if (iters_r > 0) {
                iters_r--;
                rotation -= rotate;
            }
            else {
                cur_rotation_type = -1;
                smooth_change_road = 0;
                road = to_road;

                if (part_of_route == 0) {
                    y = cirY - Radius - 20 - road * RoadWidth / 3;
                }
                if (part_of_route == 1) {
                    x = cirX - (Radius + 20 + road * RoadWidth / 3) * std::cos((rotation - 180) / 180 * pi);
                    y = cirY - (Radius + 20 + road * RoadWidth / 3) * std::sin((rotation - 180) / 180 * pi);
                }
                if (part_of_route == 2) {
                    y = cirY + Radius + 20 + road * RoadWidth / 3;
                }

                speed = std::max(0.15, 0.2 * speed);
                xystep = 0;
            }
        }
    }
    
    switch (part_of_route) {
        case 0:
            x -= speed;
            speed = std::max((float)0, speed + acceleration);
            if (smooth_change_road) {
                y += xystep;
            }
            break;
        case 1:
            omega = speed / Radius / pi * 180;
            rotation -= omega;
            x = cirX - (Radius + 20 + road * RoadWidth / 3) * std::cos((rotation - 180) / 180 * pi);
            y = cirY - (Radius + 20 + road * RoadWidth / 3) * std::sin((rotation - 180) / 180 * pi);
            speed = std::max((float)0, speed + acceleration);
            break;
        case 2:
            x += speed;
            speed = std::max((float)0, speed + acceleration);
            if (smooth_change_road) {
                y -= xystep;
            }
            break;
        default:
            exit(-1);
    }

    speed /= coeff; acceleration /= coeff;

    if (clock() >= extreme_stop_time && extreme_stop_time != -1) {
        acceleration = after_stop_acceleration;
        if (acceleration == 0) acceleration = 0.0003;
        speed = *after_stop_speed;
        if (speed <= 0.00001) speed = 0.1;
        extreme_stop_time = -1;
    }
    if (clock() >= stoped_car && stoped_car != -1) {
        acceleration = 0.0002;
        stoped_car = -1;
    }


    // change part of route
    if (x - speed < cirX && y < cirY && part_of_route != 1) {
        part_of_route = 1;
    }
    else if (x > cirX && y > cirY && part_of_route != 2) {
        part_of_route = 2;
    }
    else if (x > window->getSize().x) {
        part_of_route = -1;
        return 0;
    }

    return 1;
}

Car::~Car () {
    
}