#include "header/Button.h"
#include <iostream>

Button::Button(sf::Vector2f buttonPosition, std::string text, int buttonCharSize) :
    textString(text),
    charSize(buttonCharSize)
{
    this->initText(text);

    this->button.top = buttonPosition.y;
    this->button.left = buttonPosition.x;
    this->button.width = this->charSize / 2 * text.size();
    this->button.height = this->charSize * 1.2;
}

void Button::initText(std::string text)
{
    this->font.loadFromFile("res/font/BMgermar.TTF");

    this->text.setString(text);
    this->text.setFont(this->font);
    this->text.setCharacterSize(this->charSize);
}

void Button::update()
{
    this->text.setPosition(this->button.left, this->button.top);
}

void Button::render(std::shared_ptr<sf::RenderWindow> window)
{
    sf::Vector2f mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    this->text.setFillColor(sf::Color::White);

    if(this->isCursorOn(mousePosition))
    {
        sf::RectangleShape rectangle(sf::Vector2f(
            this->button.width, 
            this->button.height
        ));
        
        rectangle.setPosition(this->button.left, this->button.top);

        this->text.setFillColor(sf::Color::Black);

        window->draw(rectangle);
    }

    window->draw(this->text);
}

bool Button::isCursorOn(sf::Vector2f mousePosition)
{
    if(mousePosition.x >= this->button.left
        && mousePosition.x <= this->button.left + this->button.width
        && mousePosition.y >= this->button.top 
        && mousePosition.y <= this->button.top + this->button.height)
    {
        return true;
    }

    return false;
}

bool Button::isClicked(sf::Vector2f mousePosition)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isCursorOn(mousePosition))
    {
        return true;
    }

    return false;
}