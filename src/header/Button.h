#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    sf::FloatRect button;
    sf::Text text;
    sf::Font font;
    int charSize;

    void initText(std::string Text);
    void setPosition(sf::Vector2f buttonPosition);
    void setSize();

    bool isCursorOn(sf::Vector2f mousePosition);

public:
    Button();
    Button(sf::Vector2f buttonPosition, std::string text, int buttonCharSize);

    void initButton(sf::Vector2f buttonPosition, std::string text, int buttonCharSize);

    void update();

    void render(sf::RenderWindow& window);

    bool isClicked(sf::Vector2f mousePosition);

    sf::Vector2f getPosition();
};