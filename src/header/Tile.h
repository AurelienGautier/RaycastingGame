#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
private:
	int num;
	sf::RectangleShape hitbox;
	sf::Vector2i gridPosition;

public:
	Tile(int num, sf::Vector2f position);

	int getNum();
	sf::RectangleShape getHitbox();
	sf::Vector2f getPosition();

	void setGridPosition(sf::Vector2i gridPosition);
	sf::Vector2i getGridPosition();
};
