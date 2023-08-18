#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

#include "Tile.h"
#include "Global.h"

enum class HitType 
{
	HORIZONTAL = 0,
	VERTICAL
};

struct Ray
{
	float length;
	sf::Vector2f hitPoint;
	HitType hitType;;
};

class Player
{
private:
	// Attributes
	sf::CircleShape hitbox;
	float radius;
	std::vector<Ray> rays;
	float horizontalFov;
	float verticalFov;
	float maxRayLength;
	float verticalRotation;

	// Private methods
	void initHitbox(sf::Vector2f position);
	void initRays(float windowWidth);

public:
	// Constructors
	Player(float windowWidth, sf::Vector2f position, int cellSize);

	// Getters
	std::vector<Ray> getRays();
	sf::Vector2f getPosition();
	float getRadius();
	float getMaxRayLength();
	float getHorizontalRotation();
	float getVerticalRotation();
	float getHorizontalFov();
	float getVerticalFov();

	// Setters
	void setPosition(float x, float y);
	void updateRay(int index, float raySize, sf::Vector2f hitPoint, HitType HitType);

	// Public methods
	void update();
	void render(sf::RenderWindow& window, sf::View& view);
	sf::Vector2f getNextMove(Direction direction);
	void horizontallyRotate(float sens);
	void verticallyRotate(float angle);
	float calculateRayAngle(int rayIndex);
};

