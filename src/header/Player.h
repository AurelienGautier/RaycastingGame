#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

#include "Tile.h"
#include "Global.h"

class Player
{
private:
	// Attributes
	sf::CircleShape hitbox;
	float radius;
	float verticalRotation;

	// Private methods
	void initHitbox(sf::Vector2f position);
public:
	// Constructors
	Player(sf::Vector2f position, int cellSize);
	void init(float x, float y);

	// Getters
	sf::Vector2f getPosition();
	float getRadius();
	float getHorizontalRotation();
	float getVerticalRotation();

	// Setters
	void setPosition(float x, float y);

	// Public methods
	void update();
	void render(sf::RenderWindow& window);
	sf::Vector2f getNextMove(Direction direction);
	void horizontallyRotate(float sens);
	void verticallyRotate(float angle);
};

