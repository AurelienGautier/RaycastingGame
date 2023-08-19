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
	sf::Vector2i gridPosition;
	sf::Vector2f position;

	static bool texturesInitialized;
	static std::vector<sf::Texture> wallTextures;

	void initializeTextures();

public:
	Tile(CellType type, sf::Vector2f position, int size);

	CellType getType();
	sf::Vector2f getPosition();
	static std::vector<sf::Texture>& getTextures();

	void setType(CellType type);
	void setGridPosition(sf::Vector2i gridPosition);
	sf::Vector2i getGridPosition();
};
