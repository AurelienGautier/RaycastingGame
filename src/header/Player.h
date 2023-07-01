#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

#include "Tile.h"

class Player
{
private:
	sf::CircleShape hitbox;
	float speed;
	float radius;
	std::vector<sf::RectangleShape> rays;
	float fov;
	float verticalFov;
	float const maxRayLength = 192;

public:
	Player(float windowWidth);

	void render(std::shared_ptr<sf::RenderWindow> window, sf::View& view);
	void update();

	sf::Vector2f move(std::string direction);
	void rotate(float sens);

	float getSpeed();

	void setRadius(float radius);
	float getRadius();

	sf::CircleShape getHitbox();

	sf::Vector2f getPosition();
	void setPosition(float x, float y);

	void initRays(float windowWidth);

	std::vector<sf::RectangleShape> getRays();
	void setRay(int index, sf::RectangleShape ray);
	void setRaySize(int index, float raySize);
	float getMaxRayLength();

	float getFov();
	float getVerticalFov();

};

