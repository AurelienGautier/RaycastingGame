#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    sf::FloatRect button;
    std::string textString;
    sf::Text text;
    sf::Font font;
    int charSize;

    void initText(std::string Text);
    bool isCursorOn(sf::Vector2f mousePosition);

public:
    Button(sf::Vector2f buttonPosition, std::string text, int buttonCharSize);

    void update();

    void render(sf::RenderWindow& window);

    bool isClicked(sf::Vector2f mousePosition);
};