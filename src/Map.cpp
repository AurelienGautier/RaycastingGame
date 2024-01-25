#include "header/Map.h"
#include <iostream>

Map::Map() : cellSize(32)
{
}

/*-------------------------------------------------------------------------------*/

void Map::loadMap(std::string mapPath)
{
	this->path = mapPath;
	this->cells.clear();

	this->getMapFromFile();
}

/*-------------------------------------------------------------------------------*/

void Map::update(Player& player)
{
}

/*-------------------------------------------------------------------------------*/

void Map::render(sf::RenderWindow& window)
{
	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells[0].size(); j++)
		{
			if(this->cells[i][j].getType() == CellType::WALL)
			{
				sf::Sprite shape;
				shape.setTexture(Tile::getTextures()[0]);
				shape.setScale((float)this->cellSize / (float)Tile::getTextures()[0].getSize().x, (float)this->cellSize / (float)Tile::getTextures()[0].getSize().x);
				
				shape.setPosition(this->cells[i][j].getPosition());

				window.draw(shape);
			}
			else 
			{
				sf::RectangleShape shape(sf::Vector2f(this->cellSize, this->cellSize));
				shape.setFillColor(sf::Color(0, 0, 0));
				shape.setPosition(this->cells[i][j].getPosition());

				window.draw(shape);
			}
		}
	}
}

/*-------------------------------------------------------------------------------*/

void Map::movePlayer(Player& player, Direction direction)
{
	sf::Vector2f move = player.getNextMove(direction);
	sf::Vector2f playerPosition(player.getPosition().x - player.getRadius(), player.getPosition().y - player.getRadius());

	if(canPlayerMove(playerPosition, move))
	{
		player.setPosition(
			player.getPosition().x + move.x,
			player.getPosition().y + move.y
		);
	}
	else if(canPlayerMove(playerPosition, sf::Vector2f(move.x, 0)))
	{
		player.setPosition(
			player.getPosition().x + move.x,
			player.getPosition().y
		);
	}
	else if(canPlayerMove(playerPosition, sf::Vector2f(0, move.y)))
	{
		player.setPosition(
			player.getPosition().x,
			player.getPosition().y + move.y
		);
	}
	else 
	{
		player.setPosition(
			round(player.getPosition().x) ,
			round(player.getPosition().y)  
		);
	}
}

/*-------------------------------------------------------------------------------*/

// Checks the 4 cells touched by the player in the giving position
bool Map::canPlayerMove(sf::Vector2f playerPos, sf::Vector2f playerMove)
{
	sf::Vector2f posAfterMove(playerPos.x + playerMove.x, playerPos.y + playerMove.y);

	float cellX = posAfterMove.x / this->cellSize;
	float cellY = posAfterMove.y / this->cellSize;

	// Checks the up left cell
	int x = floor(cellX);
	int y = floor(cellY);
	if(this->isWall(x, y)) return false;

	// Checks the up right cell
	x = ceil(cellX);
	if(this->isWall(x, y)) return false;

	// Checks the down left cell
	x = floor(cellX);
	y = ceil(cellY);
	if(this->isWall(x, y)) return false;

	// Checks the down right cell
	x = ceil(cellX);
	if(this->isWall(x, y)) return false;

	return true;
}

/*-------------------------------------------------------------------------------*/

void Map::getMapFromFile()
{
	std::ifstream mapFile(this->path);

	char charRead;

	std::vector<std::vector<int>> map;
	std::vector<int> currentLine;

	while(mapFile.get(charRead))
	{
		int number;

		if(charRead >= '0' && charRead <= '9')
		{
			number = charRead - 48;
			currentLine.push_back(number);
		}
		else if (charRead == '\n')
		{
			map.push_back(currentLine);
			currentLine.clear();
		}
	}

	this->convertMap(map);
}

/*-------------------------------------------------------------------------------*/

void Map::convertMap(std::vector<std::vector<int>> intMap)
{
	for (int i = 0; i < intMap.size(); i++)
	{
		this->cells.push_back(std::vector<Tile>());

		for (int j = 0; j < intMap[0].size(); j++)
		{
			Tile newTile((CellType)intMap[i][j], sf::Vector2f(j * this->cellSize, i * this->cellSize), this->cellSize);

			newTile.setGridPosition(sf::Vector2i(i, j));

			this->cells[i].push_back(newTile);
		}
	}
}

/*-------------------------------------------------------------------------------*/

bool Map::isWall(int x, int y)
{
	if(this->cells[y][x].getType() != CellType::EMPTY) return true;
	return false;
}

/*-------------------------------------------------------------------------------*/

int Map::getCellsize()
{
	return this->cellSize;
}

/*-------------------------------------------------------------------------------*/

void Map::changeCell(int cellX, int cellY, CellType cellType)
{
	if(cellX < 0 || cellX > this->cells[0].size()) return;
	if(cellY < 0 || cellY >= this->cells.size()) return;

	this->cells[cellY][cellX].setType(cellType);
}

/*-------------------------------------------------------------------------------*/

void Map::save()
{
	std::ofstream mapFile(this->path);

	for(int i = 0; i < this->cells.size(); i++)
	{
		for(int j = 0; j < this->cells[0].size(); j++)
		{
			mapFile << (int)this->cells[i][j].getType();
		}

		mapFile << std::endl;
	}
}

/*-------------------------------------------------------------------------------*/

