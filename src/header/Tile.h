#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
private:
	int num;
	sf::RectangleShape hitbox;
	sf::Vector2i gridPosition;

	void updateTileType();

public:
	Tile(int num, sf::Vector2f position);

	int getNum();
	sf::RectangleShape getHitbox();
	sf::Vector2f getPosition();

	void setNum(int num);
	void setGridPosition(sf::Vector2i gridPosition);
	sf::Vector2i getGridPosition();
};
