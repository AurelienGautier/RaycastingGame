#include "header/Tile.h"

bool Tile::texturesInitialized = false;
std::vector<sf::Texture> Tile::wallTextures;

Tile::Tile(CellType type, sf::Vector2f position, int size)
{
    if(!Tile::texturesInitialized) this->initializeTextures();

    this->position = position;
    
    this->type = type;
}

void Tile::initializeTextures()
{
    sf::Texture texture;
    texture.loadFromFile("res/textures/wall.png");

    Tile::wallTextures.push_back(texture);

    Tile::texturesInitialized = true;
}

CellType Tile::getType()
{
    return this->type;
}

sf::Vector2f Tile::getPosition()
{
    return this->position;
}

std::vector<sf::Texture>& Tile::getTextures()
{
    return Tile::wallTextures;
}

void Tile::setType(CellType type)
{
    this->type = type;
}

void Tile::setGridPosition(sf::Vector2i gridPosition)
{
    this->gridPosition = gridPosition;
}

sf::Vector2i Tile::getGridPosition()
{
    return this->gridPosition;
}

