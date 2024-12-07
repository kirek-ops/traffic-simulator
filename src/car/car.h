#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <memory>

class Car {
private:
    void move ();

    sf::RectangleShape shape;
    float x, y;
    float speed;
    bool moving;
    std::thread moveThread;
    std::mutex carMutex;

public:
    Car(float x, float y, float speed);

    void update ();
    void render (sf::RenderWindow &window);
    bool isClicked (const sf::Vector2i &mousePos);

    void start ();
    void stop ();

    void startThread ();
    void stopThread ();

    bool isMoving () const { return moving; }

    // Disable copying and moving of the Car
    Car (const Car &) = delete;
    Car & operator = (const Car &) = delete;
    Car (Car &&) = delete;
    Car & operator = (Car &&) = delete;
};

#endif
