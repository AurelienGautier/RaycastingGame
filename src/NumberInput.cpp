#include "header/NumberInput.h"

NumberInput::NumberInput(sf::Vector2f thePosition) : 
    value(0),
    position(thePosition),
    rightArrow(sf::Vector2f(thePosition.x + 40 + 16, thePosition.y), std::string(1, (char)62), 32),
    leftArrow(sf::Vector2f(thePosition.x + 40, thePosition.y), std::string(1, (char)60), 32)
{
    this->font.loadFromFile("res/font/BMgermar.TTF");

    this->textValue.setFont(this->font);
    this->textValue.setPosition(this->position);
}

void NumberInput::update(sf::Vector2f mousePosition)
{
    this->textValue.setString(std::to_string(this->value));

    this->rightArrow.update();
    this->leftArrow.update();

    if(this->rightArrow.isClicked(mousePosition))
        this->value++;
    else if(this->leftArrow.isClicked(mousePosition))
        this->value--;

}

void NumberInput::render(sf::RenderWindow& window)
{
    window.draw(this->textValue);

    this->rightArrow.render(window);
    this->leftArrow.render(window);
}