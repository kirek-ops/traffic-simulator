#pragma once
#include <SFML/Graphics.hpp>

class Car {
    private:
        float road;
        float speed, acceleration, max_speed;
        float x, y;
        sf::RenderWindow *window;
        float rotation;

        int part_of_route; // -1 = undefined
                           //  0 = top straight
                           //  1 = half circle
                           //  2 = bottom straight

        bool smooth_change_road;
        int to_road;

        time_t extreme_stop_time;
        float after_stop_acceleration;

    public:
        Car ();
        Car (sf::RenderWindow *_window, int _type, int _road, float _speed, float _acceleration, float _max_speed);

        bool move ();
        void extreme_stop (double dist, Car car);
        double dist (const Car &other);

        ~Car ();

    friend class Manager;
};