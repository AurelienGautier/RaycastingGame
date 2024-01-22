#include "header/Player.h"

Player::Player(sf::Vector2f position, int cellSize) :
	radius(cellSize / 2), 
	verticalRotation(0) 
{
	this->initHitbox(position);
}

/*-------------------------------------------------------------------------------*/
// Initialization methods

void Player::initHitbox(sf::Vector2f position)
{
	this->hitbox.setRadius(this->radius);

	this->hitbox.setPosition(position);

	this->hitbox.setFillColor(sf::Color::Red);

	this->hitbox.setOrigin(this->radius, this->radius);
}

/*-------------------------------------------------------------------------------*/
// Getters

sf::Vector2f Player::getPosition()
{
	return this->hitbox.getPosition();
}


float Player::getRadius()
{
	return this->radius;
}


float Player::getHorizontalRotation()
{
	return this->hitbox.getRotation();
}


float Player::getVerticalRotation()
{
	return this->verticalRotation;
}

/*-------------------------------------------------------------------------------*/
// Setters

void Player::setPosition(float x, float y)
{
	this->hitbox.setPosition(x, y);
}

/*-------------------------------------------------------------------------------*/
// Public methods

void Player::update()
{
}

/*---------------------------------------*/

void Player::render(sf::RenderWindow& window)
{
}

/*---------------------------------------*/

sf::Vector2f Player::getNextMove(Direction direction)
{
	sf::Vector2f move(0, 0);

	switch(direction)
	{
		case Direction::FORWARD:
			move.x = Glb::cosine(this->getHorizontalRotation());
			move.y = Glb::sinus(this->getHorizontalRotation());
			break;

		case Direction::LEFT:
			move.x = Glb::cosine(this->getHorizontalRotation() - 90);
			move.y = Glb::sinus(this->getHorizontalRotation() - 90);
			break;

		case Direction::BACK:
			move.x = -Glb::cosine(this->getHorizontalRotation());
			move.y = -Glb::sinus(this->getHorizontalRotation());
			break;

		case Direction::RIGHT:
			move.x = Glb::cosine(this->getHorizontalRotation() + 90);
			move.y = Glb::sinus(this->getHorizontalRotation() + 90);
			break;
	}

	return move;
}

/*---------------------------------------*/

void Player::horizontallyRotate(float sens)
{
	this->hitbox.rotate(sens);
}

/*---------------------------------------*/

void Player::verticallyRotate(float angle)
{
	this->verticalRotation = Glb::clamp(this->verticalRotation + angle, -89, 89);
}

/*-------------------------------------------------------------------------------*/