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

void Map::update(Player& player)
{
	this->updateFovContact(player);
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

void Map::movePlayer(Player& player, std::string direction)
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

bool Map::canPlayerMove(sf::Vector2f playerPos, sf::Vector2f playerMove)
{
	sf::Vector2f posAfterMove(playerPos.x + playerMove.x, playerPos.y + playerMove.y);

	float cellX = posAfterMove.x / 16;
	float cellY = posAfterMove.y / 16;

	int x = floor(cellX);
	int y = floor(cellY);
	if(this->cells[y][x].getNum() != 0) return false;

	x = ceil(cellX);
	if(this->cells[y][x].getNum() != 0) return false;

	x = floor(cellX);
	y = ceil(cellY);
	if(this->cells[y][x].getNum() != 0) return false;

	x = ceil(cellX);
	if(this->cells[y][x].getNum() != 0) return false;

	return true;
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

void Map::updateFovContact(Player& player)
{
	std::vector<float> rays = player.getRays();

	for (int i = 0; i < rays.size(); i++)
	{
		float rayLength = 0;
		sf::Vector2f startPoint = player.getPosition();
		bool wallMet = false;
		int raySize = rays[i];

		float angle = (player.getHorizontalRotation() - player.getHorizontalFov() / 2) + (i * player.getHorizontalFov() / rays.size());

		if(angle < 0) angle += 360;
		else if(angle >= 360) angle -= 360;

		float slope = Global::tangent(angle);

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
			// If the next cell is vertical
			else if (deltaX * slope * deltaFactor.y > deltaY * deltaFactor.y) {
				startPoint.x += deltaY / slope;
				startPoint.y += deltaY;

				rayLength += deltaY / Global::sinus(angle);
				nextCellY += deltaFactor.y;
			}
			else // If the next cell is horizontal
			{
				startPoint.x += deltaX;
				startPoint.y += deltaX * slope;

				rayLength += deltaX / Global::cosine(angle);
				nextCellX += deltaFactor.x;
			}

			if (rayLength <= raySize)
			{
				if (this->cells[nextCellY][nextCellX].getNum() == 1)
				{
					wallMet = true;
					player.setRaySize(i, rayLength);
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