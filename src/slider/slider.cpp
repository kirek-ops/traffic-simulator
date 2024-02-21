#include "slider.h"
#include <iostream>

Slider::Slider (sf::RenderWindow *_window, float min, float max) {
    minVal = min; maxVal = max; window = _window;

    bar.setPosition(sf::Vector2f(40, 40)); 
    bar.setFillColor(sf::Color(196, 196, 196));
    bar.setSize(sf::Vector2f(10, 200));
    bar.setRotation(270);

    edgeLeft.setPosition(sf::Vector2f(35, 30));
    edgeLeft.setFillColor(sf::Color(196, 196, 196));
    edgeLeft.setRadius(5);

    edgeRight.setPosition(sf::Vector2f(235, 30));
    edgeRight.setFillColor(sf::Color(196, 196, 196));
    edgeRight.setRadius(5);
    
    val = 1;
    float range = maxVal - minVal;
    float posx = (val - minVal) / range * bar.getSize().y + edgeLeft.getPosition().x;
    float posy = edgeLeft.getPosition().y - 5;

    slider.setPosition(sf::Vector2f(posx, posy));
    slider.setFillColor(sf::Color(120, 120, 120));
    slider.setRadius(10);
    slider.setOutlineThickness(2);
    slider.setOutlineColor(sf::Color(0, 0, 0));

    isDragging = false;
}

bool Slider::is_on_slider (sf::Vector2f xy) {
    float x = xy.x, y = xy.y;
    if (slider.getGlobalBounds().contains(xy)) {
        return true;
    }
    else {
        return false;
    }
}

void Slider::process () {
    if (isDragging) {
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        float delta = mousePos.x - prevMousePos.x;
        if (slider.getPosition().x + delta <= 235 && slider.getPosition().x + delta >= 35) {
            slider.move(delta, 0);
            val = (maxVal - minVal) * (slider.getPosition().x - edgeLeft.getPosition().x) / 200;
            // std::cout << val << " " << get_coeff() << '\n';
        }
        prevMousePos = mousePos;
    }
}

void Slider::turn_on (sf::Vector2f xy) {
    isDragging = true;
    prevMousePos = xy;
}

void Slider::turn_off () {
    if (isDragging) {
        isDragging = false;
    }
}

void Slider::draw () {
    window->draw(bar);
    window->draw(edgeLeft);
    window->draw(edgeRight);
    window->draw(slider);
    window->draw(text);
}

float Slider::get_coeff () {
    return val;
}