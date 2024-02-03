#pragma once
#include <SFML/Graphics.hpp>

class Car {
    private:
        int type;
        int road;
        float speed, acceleration, max_speed;
        float x, y;
        int cirX, cirY;

    public:
        Car ();
        Car (int _type, int _road, float _speed, float _acceleration, float _max_speed, float _x, float _y, int _cirX, int _cirY);

        void setX (float x);
        void setY (float y);
        float getX ();
        float getY ();

        void changeRoad (int road);
        int getRoad ();

        void changeSpeed (float speed);
        float getSpeed ();

        void move ();
};