#include "header/Raycasting.h"

Raycasting::Raycasting(float windowWidth) : 
    maxRayLength(2000),
    horizontalFov(90.f),
	verticalFov(90.f)
{
    this->initRays(windowWidth);
}

Raycasting::~Raycasting()
{
}

/*-------------------------------------------------------------------------------*/

void Raycasting::initRays(float windowWidth)
{
	for (float i = 0; i <= windowWidth; i++)
	{
		Ray newRay;
		newRay.length = this->maxRayLength;
		newRay.hitPoint = sf::Vector2f(0, 0);

		this->rays.push_back(newRay);
	}
}

/*-------------------------------------------------------------------------------*/

void Raycasting::updateRay(int index, float raySize, sf::Vector2f hitPoint, HitType hitType)
{
	this->rays[index].length = raySize;
	this->rays[index].hitPoint = hitPoint;
	this->rays[index].hitType = hitType;
}

/*-------------------------------------------------------------------------------*/

float Raycasting::calculateRayAngle(int rayIndex, Player& player)
{
	float playerFovStart = player.getHorizontalRotation() - this->horizontalFov / 2;
	float rayPerDegree = this->horizontalFov / this->rays.size();

	float angle = playerFovStart + rayPerDegree * rayIndex;

	if(angle < 0) angle += 360;
	else if(angle >= 360) angle -= 360;

	return angle;
}

/*-------------------------------------------------------------------------------*/

void Raycasting::update(Player& player, Map& map)
{
    for (int i = 0; i < this->rays.size(); i++)
	{
		this->rays[i].length = this->maxRayLength;
		this->defineRay(player, i, map);
	}
}

/*-------------------------------------------------------------------------------*/

void Raycasting::defineRay(Player &player, int ray, Map& map)
{
	float rayLength = 0;

	sf::Vector2f startPoint = player.getPosition();

	bool wallMet = false;

	int maxRaySize = this->maxRayLength;

	float angle = this->calculateRayAngle(ray, player);

	float slope = Glb::tangent(angle);

	HitType hitType;

	while (rayLength < maxRaySize && !wallMet)
	{
		sf::Vector2i deltaFactor = this->getDeltaFactor(angle);

		sf::Vector2f cellPos = this->getCellPos(startPoint, deltaFactor, map);

		sf::Vector2f delta = this->getDelta(cellPos, deltaFactor, startPoint, map);

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

		if (rayLength <= maxRaySize && map.isWall(nextCell.x, nextCell.y))
		{
			wallMet = true;
			this->updateRay(ray, rayLength, startPoint, hitType);
		}
	}
}

/*-------------------------------------------------------------------------------*/

sf::Vector2i Raycasting::getDeltaFactor(float angle)
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

sf::Vector2f Raycasting::getDelta(sf::Vector2f cellPos, sf::Vector2i deltaFactor, sf::Vector2f startPoint, Map& map)
{
	sf::Vector2f delta(
		(cellPos.x + deltaFactor.x) * map.getCellsize() - startPoint.x,
		(cellPos.y + deltaFactor.y) * map.getCellsize() - startPoint.y
	);

	if (delta.y <= 0 && delta.y != -map.getCellsize())
		delta.y += map.getCellsize();
	if (delta.x <= 0 && delta.x != -map.getCellsize())
		delta.x += map.getCellsize();

	return delta;
}

/*-------------------------------------------------------------------------------*/

sf::Vector2f Raycasting::getCellPos(sf::Vector2f startPoint, sf::Vector2i deltaFactor, Map& map)
{
	sf::Vector2f cellPos(
		floor(startPoint.x / map.getCellsize()),
		floor(startPoint.y / map.getCellsize())
	);

	if (floor(startPoint.y) == startPoint.y && (int)startPoint.y % map.getCellsize() == 0 && deltaFactor.y == -1)
	{
		cellPos.y--;
	}
	if (floor(startPoint.x) == startPoint.x && (int)startPoint.x % map.getCellsize() == 0 && deltaFactor.x == -1)
	{
		cellPos.x--;
	}

	return cellPos;
}

/*-------------------------------------------------------------------------------*/

void Raycasting::render(sf::RenderWindow& window, Player& player, Map& map)
{
	float projectionDistance = map.getCellsize() / Glb::tangent(this->verticalFov / 2);

	sf::Vector2f screenSize(window.getSize().x, window.getSize().y);

	float floorLevel = screenSize.y / 2 * (1 + Glb::tangent(player.getVerticalRotation()) / Glb::tangent(this->verticalFov / 2));

	// Displaying the sky
	sf::RectangleShape skyShape(sf::Vector2f(screenSize.x, screenSize.y));
	skyShape.setFillColor(sf::Color(0, 120, 255));
	skyShape.setPosition(0, 0);
	window.draw(skyShape);

	// Displaying the floor
	sf::RectangleShape floorShape(sf::Vector2f(screenSize.x, screenSize.y - floorLevel));
	floorShape.setFillColor(sf::Color(0, 255, 0));
	floorShape.setPosition(0, floorLevel);
	window.draw(floorShape);

	// Displaying the walls
	for (int i = 0; i < screenSize.x; i++)
	{
		if (this->rays[i].length < this->maxRayLength)
		{
			float rayAngle = this->horizontalFov * (floor(screenSize.x) / 2 - i) / (screenSize.x - 1);
			float rayProjectionPosition = Glb::tangent(rayAngle) / 2 / Glb::tangent(this->horizontalFov / 2);

			int currentColumn = round(screenSize.x * (0.5f - rayProjectionPosition));
			int nextColumn = screenSize.x;

			if(i < screenSize.x - 1)
			{
				float nextRayAngle = this->horizontalFov * (floor(screenSize.x) / 2 - 1 - i) / (screenSize.x - 1);
				rayProjectionPosition = Glb::tangent(nextRayAngle) / 2 / Glb::tangent(this->horizontalFov / 2);
				nextColumn = round(screenSize.x * (0.5f - rayProjectionPosition));
			}

			float shapeWidth = std::max(1, nextColumn - currentColumn);
			float shapeHeight = screenSize.y * projectionDistance / (this->rays[i].length * Glb::cosine(rayAngle));

			int shapePosX = currentColumn;
			int shapePosY = floorLevel - shapeHeight / 2;

			sf::Sprite shape;
			shape.setTexture(Tile::getTextures()[0]);

			int texturePart = 0;

			if(this->rays[i].hitType == HitType::HORIZONTAL)
			{
				texturePart = this->rays[i].hitPoint.y - floor(this->rays[i].hitPoint.y / map.getCellsize()) * map.getCellsize();
			}
			else
			{
				texturePart = ceil(this->rays[i].hitPoint.x / map.getCellsize()) * map.getCellsize() - this->rays[i].hitPoint.x;
			}

			float part = Tile::getTextures()[0].getSize().x / map.getCellsize();

			shape.setPosition(shapePosX, shapePosY);

			shape.setTextureRect(sf::IntRect(texturePart * part, 0, part, Tile::getTextures()[0].getSize().y));

			shape.setScale(shapeWidth / part, (shapeHeight / map.getCellsize()) / part);

			window.draw(shape);
		}
	}
}

/*-------------------------------------------------------------------------------*/