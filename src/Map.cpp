#include "header/Map.h"

Map::Map(std::string mapPath) : 
	path(mapPath),
	cellSize(32)
{
	this->getMapFromFile();
}

/*-------------------------------------------------------------------------------*/

void Map::update(Player& player)
{
	this->updateFovContact(player);
}

/*-------------------------------------------------------------------------------*/

void Map::render(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);

	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells[0].size(); j++)
		{
			window.draw(this->cells[i][j].getHitbox());
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
	if(this->isWall(this->cells[y][x])) return false;

	// Checks the up right cell
	x = ceil(cellX);
	if(this->isWall(this->cells[y][x])) return false;

	// Checks the down left cell
	x = floor(cellX);
	y = ceil(cellY);
	if(this->isWall(this->cells[y][x])) return false;

	// Checks the down right cell
	x = ceil(cellX);
	if(this->isWall(this->cells[y][x])) return false;

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

void Map::updateFovContact(Player& player)
{
	std::vector<Ray> rays = player.getRays();

	for (int i = 0; i < rays.size(); i++)
	{
		this->defineRay(player, i);
	}
}

/*-------------------------------------------------------------------------------*/

void Map::defineRay(Player &player, int ray)
{
	float rayLength = 0;

	sf::Vector2f startPoint = player.getPosition();

	bool wallMet = false;

	int maxRaySize = player.getMaxRayLength();

	float angle = player.calculateRayAngle(ray);

	float slope = Glb::tangent(angle);

	HitType hitType;

	while (rayLength < maxRaySize && !wallMet)
	{
		sf::Vector2i deltaFactor = this->getDeltaFactor(angle);

		sf::Vector2f cellPos = this->getCellPos(startPoint, deltaFactor);

		sf::Vector2f delta = this->getDelta(cellPos, deltaFactor, startPoint);

		sf::Vector2f nextCell(cellPos);

		// For vertical angles
		if (floor(angle) == 90 || floor(angle) == 270)
		{
			startPoint.y += delta.y;
			
			rayLength += delta.y * deltaFactor.y;
			nextCell.y += deltaFactor.y;

			hitType = HitType::VERTICAL;
		}
		// If the next cell is vertical
		else if (delta.x * slope * deltaFactor.y > delta.y * deltaFactor.y)
		{
			startPoint.x += delta.y / slope;
			startPoint.y += delta.y;

			rayLength += delta.y / Glb::sinus(angle);
			nextCell.y += deltaFactor.y;

			hitType = HitType::VERTICAL; 
		}
		else // If the next cell is horizontal
		{
			startPoint.x += delta.x;
			startPoint.y += delta.x * slope;

			rayLength += delta.x / Glb::cosine(angle);
			nextCell.x += deltaFactor.x;

			hitType = HitType::HORIZONTAL;
		}

		if (rayLength <= maxRaySize && this->isWall(this->cells[nextCell.y][nextCell.x]))
		{
			wallMet = true;
			player.updateRay(ray, rayLength, startPoint, hitType);
		}
	}
}

/*-------------------------------------------------------------------------------*/

sf::Vector2i Map::getDeltaFactor(float angle)
{
	sf::Vector2i deltaFactor;

	if (angle >= 0 && angle < 90)
	{
		deltaFactor.x = 1;
		deltaFactor.y = 1;
	}
	else if (angle >= 90 && angle < 180)
	{
		deltaFactor.x = -1;
		deltaFactor.y = 1;
	}
	else if (angle >= 180 && angle < 270)
	{
		deltaFactor.x = -1;
		deltaFactor.y = -1;
	}
	else if (angle >= 270 && angle < 360)
	{
		deltaFactor.x = 1;
		deltaFactor.y = -1;
	}

	return deltaFactor;
}

/*-------------------------------------------------------------------------------*/

sf::Vector2f Map::getDelta(sf::Vector2f cellPos, sf::Vector2i deltaFactor, sf::Vector2f startPoint)
{
	sf::Vector2f delta(
		(cellPos.x + deltaFactor.x) * this->cellSize - startPoint.x,
		(cellPos.y + deltaFactor.y) * this->cellSize - startPoint.y
	);

	if (delta.y <= 0 && delta.y != -cellSize)
		delta.y += this->cellSize;
	if (delta.x <= 0 && delta.x != -cellSize)
		delta.x += this->cellSize;

	return delta;
}

/*-------------------------------------------------------------------------------*/

sf::Vector2f Map::getCellPos(sf::Vector2f startPoint, sf::Vector2i deltaFactor)
{
	sf::Vector2f cellPos(
		floor(startPoint.x / this->cellSize),
		floor(startPoint.y / this->cellSize)
	);

	if (floor(startPoint.y) == startPoint.y && (int)startPoint.y % cellSize == 0 && deltaFactor.y == -1)
	{
		cellPos.y--;
	}
	if (floor(startPoint.x) == startPoint.x && (int)startPoint.x % cellSize == 0 && deltaFactor.x == -1)
	{
		cellPos.x--;
	}

	return cellPos;
}

/*-------------------------------------------------------------------------------*/

bool Map::isWall(Tile cell)
{
	if(cell.getType() != CellType::EMPTY) return true;
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