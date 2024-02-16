#include <SFML/Graphics.hpp>

class Slider {
    private:
        sf::RectangleShape bar;
        sf::CircleShape slider, boarder, edgeLeft, edgeRight;
        float minVal, maxVal, val;
        sf::RenderWindow *window;
        sf::Text text;
        bool isDragging;
        sf::Vector2f prevMousePos;
        
    public:
        Slider (sf::RenderWindow *_window, float min, float max);
        bool is_on_slider (sf::Vector2f xy);
        void turn_on (sf::Vector2f xy);
        void turn_off ();
        void process ();
        void draw ();

        float get_coeff ();
};