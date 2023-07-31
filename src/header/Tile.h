#pragma once
#include <SFML/Graphics.hpp>

enum class CellType
{
	EMPTY = 0,
	WALL
};

class Tile
{
private:
	CellType type;
	sf::RectangleShape hitbox;
	sf::Vector2i gridPosition;

	void updateTileType();

public:
	Tile(CellType type, sf::Vector2f position);

	CellType getType();
	sf::RectangleShape getHitbox();
	sf::Vector2f getPosition();

	void setType(CellType type);
	void setGridPosition(sf::Vector2i gridPosition);
	sf::Vector2i getGridPosition();
};
