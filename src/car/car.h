#pragma once
#include <SFML/Graphics.hpp>

class Car {
    private:
        int type;
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

    public:
        Car ();
        Car (sf::RenderWindow *_window, int _type, int _road, float _speed, float _acceleration, float _max_speed);

        void setX (float x);
        void setY (float y);
        float getX ();
        float getY ();

        void changeRoad (int road);
        int getRoad ();

        void changeSpeed (float speed);
        float getSpeed ();

        bool move ();

        int get_part_of_route ();

        void extreme_stop ();

        ~Car ();

    friend class Manager;
};