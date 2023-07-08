#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <algorithm>

#include "Tile.h"
#include "Global.h"

class Player
{
private:
	// Attributes
	sf::CircleShape hitbox;
	float radius;
	std::vector<float> rays;
	float horizontalFov;
	float verticalFov;
	float const maxRayLength = 192;
	float verticalRotation;

	// Private methods
	void initRays(float windowWidth);

public:
	// Constructors
	Player(float windowWidth);

	// Getters
	std::vector<float> getRays();
	sf::Vector2f getPosition();
	float getRadius();
	float getMaxRayLength();
	float getHorizontalRotation();
	float getVerticalRotation();
	float getHorizontalFov();
	float getVerticalFov();

	// Setters
	void setPosition(float x, float y);
	void setRaySize(int index, float raySize);

	// Public methods
	void update();
	void render(std::shared_ptr<sf::RenderWindow> window, sf::View& view);
	sf::Vector2f getNextMove(std::string direction);
	void horizontallyRotate(float sens);
	void verticallyRotate(float angle);
};

