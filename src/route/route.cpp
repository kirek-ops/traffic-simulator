#include "route.h"

Route::Route (sf::RenderWindow *_window) {
    window = _window;
}

void Route::show () {
    const int Radius = (int)(window->getSize().x / 8);
    const int cirX = (int)(window->getSize().x / 4) - Radius;
    const int cirY = (int)(window->getSize().y / 2) - Radius - 100;
    const int RoadWidth = 90;

    sf::CircleShape Road;
    Road.setRadius(Radius);
    Road.setPosition(cirX, cirY);
    Road.setFillColor(sf::Color::Transparent);
    Road.setOutlineColor(sf::Color(128, 128, 128));
    Road.setOutlineThickness(RoadWidth);
    window->draw(Road);
    
    sf::CircleShape BoarderOutside;
    BoarderOutside.setRadius(Radius + RoadWidth);
    BoarderOutside.setPosition(cirX - RoadWidth, cirY - RoadWidth);
    BoarderOutside.setFillColor(sf::Color::Transparent);
    BoarderOutside.setOutlineColor(sf::Color::Black);
    BoarderOutside.setOutlineThickness(3);
    window->draw(BoarderOutside);

    sf::CircleShape BoarderInside;
    BoarderInside.setRadius(Radius);
    BoarderInside.setPosition(cirX, cirY);
    BoarderInside.setFillColor(sf::Color::Transparent);
    BoarderInside.setOutlineColor(sf::Color::Black);
    BoarderInside.setOutlineThickness(3);
    window->draw(BoarderInside);
}