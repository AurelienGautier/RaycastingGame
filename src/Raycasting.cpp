#include "header/Raycasting.h"

Raycasting::Raycasting()
{
}

Raycasting::~Raycasting()
{
}

void Raycasting::update(Player& player, Map& map)
{
}

void Raycasting::render(sf::RenderWindow& window, Player& player, Map& map)
{
	std::vector<Ray> rays = player.getRays();

	float projectionDistance = map.getCellsize() / Glb::tangent(player.getVerticalFov() / 2);

	sf::Vector2f screenSize(window.getSize().x, window.getSize().y);

	float floorLevel = screenSize.y / 2 * (1 + Glb::tangent(player.getVerticalRotation()) / Glb::tangent(player.getVerticalFov() / 2));

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
		if (rays[i].length < player.getMaxRayLength())
		{
			float rayAngle = player.getHorizontalFov() * (floor(screenSize.x) / 2 - i) / (screenSize.x - 1);
			float rayProjectionPosition = Glb::tangent(rayAngle) / 2 / Glb::tangent(player.getHorizontalFov() / 2);

			int currentColumn = round(screenSize.x * (0.5f - rayProjectionPosition));
			int nextColumn = screenSize.x;

			if(i < screenSize.x - 1)
			{
				float nextRayAngle = player.getHorizontalFov() * (floor(screenSize.x) / 2 - 1 - i) / (screenSize.x - 1);
				rayProjectionPosition = Glb::tangent(nextRayAngle) / 2 / Glb::tangent(player.getHorizontalFov() / 2);
				nextColumn = round(screenSize.x * (0.5f - rayProjectionPosition));
			}

			float shapeWidth = std::max(1, nextColumn - currentColumn);
			float shapeHeight = screenSize.y * projectionDistance / (rays[i].length * Glb::cosine(rayAngle));

			int shapePosX = currentColumn;
			int shapePosY = floorLevel - shapeHeight / 2;

			sf::Sprite shape;
			shape.setTexture(Tile::getTextures()[0]);

			int texturePart = 0;

			if(rays[i].hitType == HitType::HORIZONTAL)
			{
				texturePart = rays[i].hitPoint.y - floor(rays[i].hitPoint.y / map.getCellsize()) * map.getCellsize();
			}
			else
			{
				texturePart = ceil(rays[i].hitPoint.x / map.getCellsize()) * map.getCellsize() - rays[i].hitPoint.x;
			}

			float part = Tile::getTextures()[0].getSize().x / map.getCellsize();

			shape.setPosition(shapePosX, shapePosY);

			shape.setTextureRect(sf::IntRect(texturePart * part, 0, part, Tile::getTextures()[0].getSize().y));

			shape.setScale(shapeWidth / part, (shapeHeight / map.getCellsize()) / part);

			window.draw(shape);
		}
	}
}