#include "header/Map.h"
#include <iostream>

Map::Map()
{
	this->convertMap ( 
		{ {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		} }
	);
}

/*-------------------------------------------------------------------------------*/

void Map::update()
{
}

/*-------------------------------------------------------------------------------*/

void Map::render(std::shared_ptr<sf::RenderWindow> window, sf::View& view)
{
	window->setView(view);

	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells[0].size(); j++)
		{
			window->draw(this->cells[i][j].getHitbox());
		}
	}
}

/*-------------------------------------------------------------------------------*/

void Map::movePlayer(std::shared_ptr<Player> player, std::string direction)
{
	sf::Vector2f move = player->move(direction);

	float playerHitboxExcess = player->getHitbox().getRadius() / 2;

	sf::Vector2f newPlayerPos(this->getPlayerNewPos(player->getPosition(), move));

	player->setPosition(newPlayerPos.x, newPlayerPos.y);
}

/*-------------------------------------------------------------------------------*/

sf::Vector2f Map::getPlayerNewPos(sf::Vector2f playerPos, sf::Vector2f playerMove)
{
	sf::Vector2f newPlayerPos(playerPos);

	float newX = playerPos.x + playerMove.x;
	float newY = playerPos.y + playerMove.y;

	int cellX = floor(newX / 16);
	int cellY = floor(newY / 16);

	if(this->cells[cellY][cellX].getNum() != 1)
	{
		newPlayerPos.x = newX;
		newPlayerPos.y = newY;
	}

	return newPlayerPos;
}

/*-------------------------------------------------------------------------------*/

void Map::convertMap(std::vector<std::vector<int>> intMap)
{
	for (int i = 0; i < intMap.size(); i++)
	{
		this->cells.push_back(std::vector<Tile>());

		for (int j = 0; j < intMap[0].size(); j++)
		{
			Tile newTile(intMap[i][j], sf::Vector2f(j * this->cellSize, i * this->cellSize));

			newTile.setGridPosition(sf::Vector2i(i, j));

			this->cells[i].push_back(newTile);
		}
	}
}

/*-------------------------------------------------------------------------------*/

void Map::updateFovContact(std::shared_ptr<Player> player)
{
	std::vector<sf::RectangleShape> rays = player->getRays();

	for (int i = 0; i < rays.size(); i++)
	{
		float rayLength = 0;
		sf::Vector2f startPoint = player->getPosition();
		bool wallMet = false;
		int raySize = rays[i].getSize().x;

		float angle = rays[i].getRotation();
		float slope = tan(angle * 3.14f / 180.0f);

		while (rayLength < raySize && !wallMet) 
		{
			sf::Vector2f deltaFactor = this->getDeltaFactor(angle);

			int cellPosX = floor(startPoint.x / this->cellSize);
			int cellPosY = floor(startPoint.y / this->cellSize);

			if (floor(startPoint.y) == startPoint.y && (int)startPoint.y % cellSize == 0 && deltaFactor.y == -1)
			{
				cellPosY--;
			}
			if (floor(startPoint.x) == startPoint.x && (int)startPoint.x % cellSize == 0 && deltaFactor.x == -1)
			{
				cellPosX--;
			}

			float deltaX = (cellPosX + deltaFactor.x) * this->cellSize - startPoint.x;
			float deltaY = (cellPosY + deltaFactor.y) * this->cellSize - startPoint.y;

			if (deltaY < 0 && deltaY != -cellSize) deltaY += this->cellSize;
			if (deltaX < 0 && deltaX != -cellSize) deltaX += this->cellSize;

			int nextCellX = cellPosX;
			int nextCellY = cellPosY;

			if (floor(angle)== 90 || floor(angle) == 270)
			{
				startPoint.y += deltaY;
				rayLength += deltaY * deltaFactor.y;
				nextCellY += deltaFactor.y;
			}
			// Si la prochaine case est verticale
			else if (deltaX * slope * deltaFactor.y > deltaY * deltaFactor.y) {
				startPoint.x += deltaY / slope;
				startPoint.y += deltaY;

				rayLength += deltaY / sin(angle * 3.14f / 180.0f);
				nextCellY += deltaFactor.y;
			}
			else // Si la prochaine case est horizontale
			{
				startPoint.x += deltaX;
				startPoint.y += deltaX * slope;

				rayLength += deltaX / cos(angle * 3.14f / 180.0f);
				nextCellX += deltaFactor.x;
			}

			if (rayLength <= raySize)
			{
				if (this->cells[nextCellY][nextCellX].getNum() == 1)
				{
					wallMet = true;
					player->setRaySize(i, rayLength);
				}
			}
		}
	}
}

/*-------------------------------------------------------------------------------*/

sf::Vector2f Map::getDeltaFactor(float angle)
{
	sf::Vector2f delta;

	if (angle >= 0 && angle < 90)
	{
		delta.x = 1;
		delta.y = 1;
	}
	else if (angle >= 90 && angle < 180)
	{
		delta.x = -1;
		delta.y = 1;
	}
	else if (angle >= 180 && angle < 270)
	{
		delta.x = -1;
		delta.y = -1;
	}
	else if (angle >= 270 && angle < 360)
	{
		delta.x = 1;
		delta.y = -1;
	}

	return delta;
}

/*-------------------------------------------------------------------------------*/