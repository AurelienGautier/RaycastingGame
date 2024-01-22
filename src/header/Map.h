#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>

#include "Player.h"
#include "Tile.h"
#include "Global.h"

class Map
{
private:
	std::vector<std::vector<Tile>> cells;
	int cellSize;
	std::string path;

	void getMapFromFile();
	void convertMap(std::vector<std::vector<int>> intMap);

	bool canPlayerMove(sf::Vector2f playerPos, sf::Vector2f playerMove);

public:
	Map(std::string mapPath);

	void update(Player& player);
	void movePlayer(Player& player, Direction direction);
	void render(sf::RenderWindow& window, sf::View& view);

	bool isWall(int x, int y);
	
	int getCellsize();

	void changeCell(int cellX, int cellY, CellType cellType);

	void save();
};

