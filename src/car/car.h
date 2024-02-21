#pragma once
#include <SFML/Graphics.hpp>

class Car {
    private:
        float road;
        float speed, acceleration;
        float x, y;
        sf::RenderWindow *window;
        float rotation;

        int part_of_route; // -1 = undefined
                           //  0 = top straight
                           //  1 = half circle
                           //  2 = bottom straight

        bool smooth_change_road = 0;
        int to_road;
        int rotate_iter = 10000;
        float rotate = 30.0 / rotate_iter; 
        float rstep;
        int iters_r = 0;
        float add_rotation;
        int cur_rotation_type = -1;    // 0 - increase angle
                                       // 1 - decrease angle
        int lst_road = -1;
        time_t changed;

        time_t extreme_stop_time = -1;
        float after_stop_acceleration;
        float *after_stop_speed;

        time_t click_stop_time = -1;
        float mem_acceleration;

        float MAX_SPEED = 0.5;

        time_t stoped_car = -1;

    public:
        Car ();
        Car (sf::RenderWindow *_window, int _type, int _road, float _speed, float _acceleration);

        bool move (float coeff);
        void extreme_stop (double dist, Car car, float coeff);
        double dist (const Car &other);
        void change_road (int road, float coeff);

        ~Car ();

    friend class Manager;
};