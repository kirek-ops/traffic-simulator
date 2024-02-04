#include "route.h"
#include <cmath>

Route::Route (sf::RenderWindow *_window) {
    window = _window;
}

void Route::show () {
    const int Radius = (int)(window->getSize().x / 8);
    const int cirX = (int)(window->getSize().x / 4);
    const int cirY = (int)(window->getSize().y / 2) - 100;
    const int RoadWidth = 120;
    const double pi = std::acos(-1);

    
    sf::ConvexShape Road, Outside, Inside;
    const int iters = 52;
    
    // Road
    {
        Road.setPointCount(iters);
        Road.setPoint(0, sf::Vector2f(window->getSize().x, cirY + Radius));
        for (int it = 1; it <= iters - 2; ++it) {
            float angle = it * (180.0 / (iters - 1)) + 90.0;
            float x = cirX + Radius * std::cos(angle * pi / 180.0);
            float y = cirY + Radius * std::sin(angle * pi / 180.0);
            Road.setPoint(it, sf::Vector2f(x, y));
        }
        Road.setPoint(51, sf::Vector2f(window->getSize().x, cirY - Radius));
        Road.setFillColor(sf::Color::Transparent);
        Road.setOutlineThickness(RoadWidth);
        Road.setOutlineColor(sf::Color(128, 128, 128));
    }

    // Outside Boarder
    {
        Outside.setPointCount(iters);
        Outside.setPoint(0, sf::Vector2f(window->getSize().x, cirY + Radius));
        for (int it = 1; it <= iters - 2; ++it) {
            float angle = it * (180.0 / (iters - 1)) + 90.0;
            float x = cirX + Radius * std::cos(angle * pi / 180.0);
            float y = cirY + Radius * std::sin(angle * pi / 180.0);
            Outside.setPoint(it, sf::Vector2f(x, y));
        }
        Outside.setPoint(51, sf::Vector2f(window->getSize().x, cirY - Radius));
        Outside.setFillColor(sf::Color::Transparent);
        Outside.setOutlineThickness(5);
        Outside.setOutlineColor(sf::Color::Black);
    }

    // Inside Boarder
    {
        Inside.setPointCount(iters);
        Inside.setPoint(0, sf::Vector2f(window->getSize().x, cirY + Radius + RoadWidth));
        for (int it = 1; it <= iters - 2; ++it) {
            float angle = it * (180.0 / (iters - 1)) + 90.0;
            float x = cirX + (Radius + RoadWidth) * std::cos(angle * pi / 180.0);
            float y = cirY + (Radius + RoadWidth) * std::sin(angle * pi / 180.0);
            Inside.setPoint(it, sf::Vector2f(x, y));
        }
        Inside.setPoint(51, sf::Vector2f(window->getSize().x, cirY - Radius - RoadWidth));
        Inside.setFillColor(sf::Color::Transparent);
        Inside.setOutlineThickness(5);
        Inside.setOutlineColor(sf::Color::Black);
    }

    window->draw(Road);
    window->draw(Outside);
    window->draw(Inside);

    // Road Markers
    {
        int x = cirX;
        int y = cirY - Radius - RoadWidth / 3;
        while (x + 20 < (int)window->getSize().x) {
            sf::VertexArray segment (sf::Lines, 2);
            segment[0].position = sf::Vector2f(x, y);
            segment[0].color = sf::Color::White;
            segment[1].position = sf::Vector2f(x + 20, y);
            segment[1].color = sf::Color::White;
            window->draw(segment);
            x += 40;
        }

        x = cirX;
        y = cirY - Radius - 2 * RoadWidth / 3;
        while (x + 20 < (int)window->getSize().x) {
            sf::VertexArray segment (sf::Lines, 2);
            segment[0].position = sf::Vector2f(x, y);
            segment[0].color = sf::Color::White;
            segment[1].position = sf::Vector2f(x + 20, y);
            segment[1].color = sf::Color::White;
            window->draw(segment);
            x += 40;
        }

        int cur = 20;
        while (cur < pi * Radius) {
            sf::VertexArray segment (sf::Lines, 2);
            float angle = cur / (pi * Radius) * 180.0 + 90.0;
            float x = cirX + (Radius + RoadWidth / 3) * std::cos(angle * pi / 180.0);
            float y = cirY + (Radius + RoadWidth / 3) * std::sin(angle * pi / 180.0);
            segment[0].position = sf::Vector2f(x, y);
            segment[0].color = sf::Color::White;
            
            cur += 20;
            angle = cur / (pi * Radius) * 180.0 + 90.0;
            x = cirX + (Radius + RoadWidth / 3) * std::cos(angle * pi / 180.0);
            y = cirY + (Radius + RoadWidth / 3) * std::sin(angle * pi / 180.0);
            segment[1].position = sf::Vector2f(x, y);
            segment[1].color = sf::Color::White;
            
            window->draw(segment);
            cur += 20;
        }

        cur = 20;
        while (cur < pi * Radius) {
            sf::VertexArray segment (sf::Lines, 2);
            float angle = cur / (pi * Radius) * 180.0 + 90.0;
            float x = cirX + (Radius + 2 * RoadWidth / 3) * std::cos(angle * pi / 180.0);
            float y = cirY + (Radius + 2 * RoadWidth / 3) * std::sin(angle * pi / 180.0);
            segment[0].position = sf::Vector2f(x, y);
            segment[0].color = sf::Color::White;
            
            cur += 20;
            angle = cur / (pi * Radius) * 180.0 + 90.0;
            x = cirX + (Radius + 2 * RoadWidth / 3) * std::cos(angle * pi / 180.0);
            y = cirY + (Radius + 2 * RoadWidth / 3) * std::sin(angle * pi / 180.0);
            segment[1].position = sf::Vector2f(x, y);
            segment[1].color = sf::Color::White;
            
            window->draw(segment);
            cur += 20;
        }

        x = cirX;
        y = cirY + Radius + RoadWidth / 3;
        while (x + 20 < (int)window->getSize().x) {
            sf::VertexArray segment (sf::Lines, 2);
            segment[0].position = sf::Vector2f(x, y);
            segment[0].color = sf::Color::White;
            segment[1].position = sf::Vector2f(x + 20, y);
            segment[1].color = sf::Color::White;
            window->draw(segment);
            x += 40;
        }

        x = cirX;
        y = cirY + Radius + 2 * RoadWidth / 3;
        while (x + 20 < (int)window->getSize().x) {
            sf::VertexArray segment (sf::Lines, 2);
            segment[0].position = sf::Vector2f(x, y);
            segment[0].color = sf::Color::White;
            segment[1].position = sf::Vector2f(x + 20, y);
            segment[1].color = sf::Color::White;
            window->draw(segment);
            x += 40;
        }
    }

}