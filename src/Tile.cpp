#include "header/Tile.h"

Tile::Tile(CellType type, sf::Vector2f position)
{
    this->type = type;
    this->hitbox.setSize(sf::Vector2f(16, 16));
    this->hitbox.setPosition(position);

    this->updateTileType();
}

void Tile::updateTileType()
{
    if (this->type == CellType::WALL)
        this->hitbox.setFillColor(sf::Color::Red);
    else if (this->type == CellType::EMPTY)
        this->hitbox.setFillColor(sf::Color::Black);
}

CellType Tile::getType()
{
    return this->type;
}

sf::RectangleShape Tile::getHitbox()
{
    return this->hitbox;
}

sf::Vector2f Tile::getPosition()
{
    return this->hitbox.getPosition();
}

void Tile::setType(CellType type)
{
    this->type = type;

    this->updateTileType();
}

void Tile::setGridPosition(sf::Vector2i gridPosition)
{
    this->gridPosition = gridPosition;
}

sf::Vector2i Tile::getGridPosition()
{
    return this->gridPosition;
}

