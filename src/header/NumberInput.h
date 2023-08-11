#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class NumberInput
{
private:
    int value;
    sf::Text textValue;
    sf::Vector2f position;
    sf::Font font;

    Button rightArrow;
    Button leftArrow;
    
public:
    NumberInput(sf::Vector2f thePosition);

    void update(sf::Vector2f mousePosition);
    void render(sf::RenderWindow& window);
};