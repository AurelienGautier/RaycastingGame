#include "header/Button.h"
#include <iostream>

bool Button::isFontCreated = false;
sf::Font Button::font;

Button::Button(sf::Vector2f buttonPosition, std::string text, int buttonCharSize)
{
    this->initButton(buttonPosition, text, buttonCharSize);
}

Button::Button()
{
    this->initButton(sf::Vector2f(0, 0), "Button", 32);
}

void Button::initButton(sf::Vector2f buttonPosition, std::string text, int buttonCharSize)
{
    this->charSize = buttonCharSize;

    this->initText(text);

    this->setPosition(buttonPosition);

    this->setSize();
}

void Button::initText(std::string text)
{
    if(!Button::isFontCreated)
    {
        Button::font.loadFromFile("res/font/BMgermar.TTF");

        Button::isFontCreated = true;
    }

    this->text.setString(text);
    this->text.setFont(Button::font);
    this->text.setCharacterSize(this->charSize);
}

void Button::update()
{
    this->text.setPosition(this->button.left, this->button.top);
}

void Button::render(sf::RenderWindow& window)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    this->text.setFillColor(sf::Color::White);

    if(this->isCursorOn(mousePosition))
    {
        sf::RectangleShape rectangle(sf::Vector2f(
            this->button.width, 
            this->button.height
        ));
        
        rectangle.setPosition(this->button.left, this->button.top);

        this->text.setFillColor(sf::Color::Black);

        window.draw(rectangle);
    }

    window.draw(this->text);
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

void Button::setPosition(sf::Vector2f buttonPosition)
{
    this->button.top = buttonPosition.y;
    this->button.left = buttonPosition.x;
}

void Button::setSize()
{
    this->button.width = this->charSize / 2 * this->text.getString().getSize();
    this->button.height = this->charSize * 1.2;
}

sf::Vector2f Button::getPosition()
{
    return sf::Vector2f(this->button.left, this->button.top);
}

std::string Button::getText()
{
    return this->text.getString();
}