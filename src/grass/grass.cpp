#include "grass.h"

Route::Route(sf::RenderWindow *_window, sf::Texture *_grassTexture) {
    window = _window;
    grassTexture = _grassTexture;
    grassSprite = sf::Sprite (*grassTexture);
}

void Route::show () {
    unsigned int i = 0;
    while (i < window->getSize().x) {
        unsigned int j = 0;
        while (j < window->getSize().y) {
            grassSprite.setPosition(i, j);
            window->draw(grassSprite);
            j += grassTexture->getSize().y;
        }
        i += grassTexture->getSize().x;
    }
}