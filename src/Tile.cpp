#include "header/Tile.h"

Tile::Tile(int num, sf::Vector2f position)
{
    this->num = num;
    this->hitbox.setSize(sf::Vector2f(16, 16));
    this->hitbox.setPosition(position);

    if (this->num == 1)
        this->hitbox.setFillColor(sf::Color::Red);
    else
        this->hitbox.setFillColor(sf::Color::Black);
}

int Tile::getNum()
{
    return this->num;
}

sf::RectangleShape Tile::getHitbox()
{
    return this->hitbox;
}

sf::Vector2f Tile::getPosition()
{
    return this->hitbox.getPosition();
}

void Tile::setGridPosition(sf::Vector2i gridPosition)
{
    this->gridPosition = gridPosition;
}

sf::Vector2i Tile::getGridPosition()
{
    return this->gridPosition;
}

