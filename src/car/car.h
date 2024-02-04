#pragma once
#include <SFML/Graphics.hpp>

class Car {
    private:
        int type;
        int road;
        float speed, acceleration, max_speed;
        float x, y;
        sf::RenderWindow *window;

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
};