#include <SFML/Graphics.hpp>
#include <SFML/System/Thread.hpp>

#include <iostream>
#include <vector>
#include <cmath>

#include "car/car.h"
#include "manager/manager.h"

const int OUTLINE_THICKNESS = 4;
const int NUMBER_OF_SEGMENTS = 200;
const int NUMBER_OF_LINES = 20;

void updateBackgroundSize (sf::RectangleShape &background, sf::Texture &grassTexture, int screenWidth, int screenHeight) {
    grassTexture.setRepeated(true);
    background.setSize(sf::Vector2f(screenWidth, screenHeight));
    background.setTexture(&grassTexture);
    background.setTextureRect(sf::IntRect(0, 0, screenWidth, screenHeight));
}

std::vector <sf::CircleShape> calculateTorus (int cenX, int cenY, int radius, int width, sf::Color color) {
    std::vector <sf::CircleShape> torus;
    for (int i = NUMBER_OF_SEGMENTS / 4; i < 3 * NUMBER_OF_SEGMENTS / 4; ++i) {
        float angle = i * M_PI / (NUMBER_OF_SEGMENTS / 2);

        float x = cenX + (radius - width / 2) * std::cos(angle);
        float y = cenY + (radius - width / 2) * std::sin(angle);

        sf::CircleShape segment (width / 2);
        segment.setFillColor(color);
        segment.setOrigin(width / 2, width / 2);
        segment.setPosition(x, y);

        torus.emplace_back(segment);
    }
    return torus;
}

sf::RectangleShape drawThickLine (sf::Vector2f start, sf::Vector2f end, int thickness, sf::Color color)
{
    sf::Vector2f lineVector = end - start;
    float length = std::sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);

    sf::RectangleShape rectangle(sf::Vector2f(length, thickness));
    rectangle.setFillColor(color);

    rectangle.setPosition(start);

    float angle = std::atan2(lineVector.y, lineVector.x) * 180 / M_PI;
    rectangle.setRotation(angle);

    return rectangle;
}

std::pair <std::vector <sf::RectangleShape>, std::vector <sf::RectangleShape>> calculateOutline (int cenX, int cenY, int radius, int width, sf::Color color) {
    std::vector <sf::RectangleShape> outer (NUMBER_OF_SEGMENTS);
    std::vector <sf::RectangleShape> inner (NUMBER_OF_SEGMENTS);

    sf::Vector2f lst;
    {
        float angle = NUMBER_OF_SEGMENTS / 4 * M_PI / (NUMBER_OF_SEGMENTS / 2);
        float x = cenX + (radius + OUTLINE_THICKNESS - 1) * std::cos(angle); // -1 just an epsilon to fit perfectly
        float y = cenY + (radius + OUTLINE_THICKNESS - 1) * std::sin(angle); // -1 just an epsilon to fit perfectly
        lst = sf::Vector2f(x, y);
    }

    for (int i = NUMBER_OF_SEGMENTS / 4 + 1; i < 3 * NUMBER_OF_SEGMENTS / 4 + 1; ++i) {
        float angle = i * M_PI / (NUMBER_OF_SEGMENTS / 2);

        float x = cenX + (radius + OUTLINE_THICKNESS - 1) * std::cos(angle); // -1 just an epsilon to fit perfectly
        float y = cenY + (radius + OUTLINE_THICKNESS - 1) * std::sin(angle); // -1 just an epsilon to fit perfectly

        outer[i - NUMBER_OF_SEGMENTS / 4] = drawThickLine(lst, sf::Vector2f(x, y), OUTLINE_THICKNESS, color);
        lst = sf::Vector2f(x, y);
    }

    {
        float angle = NUMBER_OF_SEGMENTS / 4 * M_PI / (NUMBER_OF_SEGMENTS / 2);
        float x = cenX + (radius - width + 0.5) * std::cos(angle); // +0.5 just an epsilon to fit perfectly
        float y = cenY + (radius - width + 0.5) * std::sin(angle); // +0.5 just an epsilon to fit perfectly
        lst = sf::Vector2f(x, y);
    }

    for (int i = NUMBER_OF_SEGMENTS / 4 + 1; i < 3 * NUMBER_OF_SEGMENTS / 4 + 1; ++i) {
        float angle = i * M_PI / (NUMBER_OF_SEGMENTS / 2);

        float x = cenX + (radius - width + 0.5) * std::cos(angle); // +0.5 just an epsilon to fit perfectly
        float y = cenY + (radius - width + 0.5) * std::sin(angle); // +0.5 just an epsilon to fit perfectly

        inner[i - NUMBER_OF_SEGMENTS / 4] = drawThickLine(lst, sf::Vector2f(x, y), OUTLINE_THICKNESS, color);
        lst = sf::Vector2f(x, y);
    }

    return std::make_pair(inner, outer);
}

void drawTurn (sf::RenderWindow &window, int x, int y, int radius, int width, sf::Color color) { // (x, y) - position of center
    std::vector <sf::CircleShape> torus = calculateTorus(x, y, radius, width, color);
    std::pair <std::vector <sf::RectangleShape>, std::vector <sf::RectangleShape>> innerAndOuter = calculateOutline(x, y, radius, width, sf::Color::Black);
    for (const auto &shape : torus) {
        window.draw(shape);
    }
    for (const auto &shape : innerAndOuter.first) {
        window.draw(shape);
    }
    for (const auto &shape : innerAndOuter.second) {
        window.draw(shape);
    }
}

void drawLines (sf::RenderWindow &window, int screenWidth, int screenHeight, int straightRoadLength, int roadWidth, int center, int radius, int turnX, int turnY) {

}

void drawRoute (sf::RenderWindow &window, int screenWidth, int screenHeight) {
    int center = screenHeight / 2;
    int radius = screenHeight / 4;
    int roadWidth = screenHeight / 8;

    int turnX = screenWidth / 10 + radius;
    int turnY = center;


    sf::RectangleShape topRoad (sf::Vector2f(screenWidth - turnX, roadWidth));
    topRoad.setFillColor(sf::Color(105, 105, 105));
    topRoad.setPosition(turnX, turnY - radius);

    topRoad.setOutlineColor(sf::Color::Black);
    topRoad.setOutlineThickness(OUTLINE_THICKNESS);

    sf::RectangleShape bottomRoad (sf::Vector2f(screenWidth - turnX, roadWidth));
    bottomRoad.setFillColor(sf::Color(105, 105, 105));
    bottomRoad.setPosition(turnX, turnY + radius - roadWidth);

    bottomRoad.setOutlineColor(sf::Color::Black);
    bottomRoad.setOutlineThickness(OUTLINE_THICKNESS);

    window.draw(topRoad);
    window.draw(bottomRoad);
    drawTurn(window, turnX, turnY, radius, roadWidth, sf::Color(105, 105, 105));

    int straightRoadLength = screenWidth - turnX;
    drawLines(window, screenWidth, screenHeight, straightRoadLength, roadWidth, center, radius, turnX, turnY);
}

void renderBackground (sf::RenderWindow &window, int screenWidth, int screenHeight, sf::RectangleShape &background, sf::Texture &grassTexture) {
    window.clear();
    sf::FloatRect visibleArea(0, 0, screenWidth, screenHeight);
    window.setView(sf::View(visibleArea));
    updateBackgroundSize(background, grassTexture, screenWidth, screenHeight);
    window.draw(background);
    drawRoute(window, screenWidth, screenHeight);
}

int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int screenWidth = desktopMode.width;
    int screenHeight = desktopMode.height;

    sf::RenderWindow window (sf::VideoMode(screenWidth, screenHeight), "Traffic Simulator", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture grassTexture;
    try {
        if (!grassTexture.loadFromFile("images/grass.png")) {
            throw std::runtime_error("Failed to load background image");
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    sf::RectangleShape background;
    renderBackground(window, screenWidth, screenHeight, background, grassTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                screenWidth = event.size.width;
                screenHeight = event.size.height;
                renderBackground(window, screenWidth, screenHeight, background, grassTexture);
            }
        }

        window.display();
    }
    return 0;
}