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

	static bool texturesInitialized;
	static std::vector<sf::Texture> wallTextures;

	void updateTileType();
	void initializeTextures();

public:
	Tile(CellType type, sf::Vector2f position);

	CellType getType();
	sf::RectangleShape getHitbox();
	sf::Vector2f getPosition();
	std::vector<sf::Texture> getTextures();

	void setType(CellType type);
	void setGridPosition(sf::Vector2i gridPosition);
	sf::Vector2i getGridPosition();
};
