#include "header/Player.h"
#include <iostream>

Player::Player(float windowWidth)
{
	this->radius = 16;

	this->hitbox.setRadius(this->radius);

	this->hitbox.setPosition(sf::Vector2f(32, 32));

	this->hitbox.setFillColor(sf::Color::Red);

	this->hitbox.setOrigin(this->hitbox.getRadius(), this->hitbox.getRadius());

	this->speed = 1;

	this->fov = 90.f;

	this->verticalFov = 58.75f;

	this->initRays(windowWidth);
}

/*-------------------------------------------------------------------------------*/

void Player::render(std::shared_ptr<sf::RenderWindow> window, sf::View& view)
{
	window->setView(view);

	window->draw(this->hitbox);

	for (int i = 0; i < this->rays.size(); i++)
	{
		window->draw(this->rays[i]);
	}

	view.setCenter(this->hitbox.getPosition());
}

/*-------------------------------------------------------------------------------*/

void Player::update()
{
	for (int i = 0; i < this->rays.size(); i++)
	{
		this->rays[i].setPosition(sf::Vector2f(this->hitbox.getPosition().x, this->hitbox.getPosition().y));
		this->rays[i].setSize(sf::Vector2f(this->maxRayLength, 1));
	}
}

/*-------------------------------------------------------------------------------*/

void Player::move(std::string direction)
{

	float xMove = 0;
	float yMove = 0;

	if (direction == "FORWARD")
	{
		xMove = cos((this->hitbox.getRotation()) * 3.14f / 180.0f) / 1.5;
		yMove = sin((this->hitbox.getRotation()) * 3.14f / 180.0f) / 1.5;
	}
	else if (direction == "RIGHT")
	{
		xMove = cos((this->hitbox.getRotation() + 90) * 3.14f / 180.0f);
		yMove = sin((this->hitbox.getRotation() + 90) * 3.14f / 180.0f);
	}
	else if (direction == "LEFT")
	{
		xMove = cos((this->hitbox.getRotation() - 90) * 3.14f / 180.0f);
		yMove = sin((this->hitbox.getRotation() - 90) * 3.14f / 180.0f);
	}
	else if (direction == "BACK")
	{
		xMove = -cos((this->hitbox.getRotation()) * 3.14f / 180.0f);
		yMove = -sin((this->hitbox.getRotation()) * 3.14f / 180.0f);
	}

	this->hitbox.setPosition(
		this->hitbox.getPosition().x + xMove,
		this->hitbox.getPosition().y + yMove);
}

/*-------------------------------------------------------------------------------*/

void Player::rotate(float sens)
{
	this->hitbox.rotate(sens);

	for (int i = 0; i < this->rays.size(); i++)
	{
		this->rays[i].rotate(sens);
	}
}

/*-------------------------------------------------------------------------------*/

float Player::getSpeed()
{
	return this->speed;
}

/*-------------------------------------------------------------------------------*/

void Player::setRadius(float radius)
{
	this->radius = radius;
}

float Player::getRadius()
{
	return this->radius;
}

/*-------------------------------------------------------------------------------*/

sf::CircleShape Player::getHitbox()
{
	return this->hitbox;
}

/*-------------------------------------------------------------------------------*/

sf::Vector2f Player::getPosition()
{
	return this->hitbox.getPosition();
}

/*-------------------------------------------------------------------------------*/

sf::FloatRect Player::getNextPos(int x, int y)
{
	sf::FloatRect nextPosition(
		this->hitbox.getPosition().x + x * this->speed,
		this->hitbox.getPosition().y + y * this->speed,
		this->radius, this->radius);

	return nextPosition;
}

/*-------------------------------------------------------------------------------*/

void Player::initRays(float windowWidth)
{
	for (float i = 0; i <= windowWidth; i++)
	{
		sf::RectangleShape newRay;

		float angle = (this->hitbox.getRotation() - this->fov / 2) + (i * this->fov / windowWidth);

		newRay.setSize(sf::Vector2f(this->maxRayLength, 1));
		newRay.setRotation(angle);
		newRay.setPosition(sf::Vector2f(this->hitbox.getPosition().x, this->hitbox.getPosition().y));

		this->rays.push_back(newRay);
	}
}

/*-------------------------------------------------------------------------------*/

std::vector<sf::RectangleShape> Player::getRays()
{
	return this->rays;
}

void Player::setRay(int index, sf::RectangleShape ray)
{
	this->rays[index] = ray;
}

void Player::setRaySize(int index, float raySize)
{
	this->rays[index].setSize(sf::Vector2f(raySize, 1));
}

/*-------------------------------------------------------------------------------*/

float Player::getMaxRayLength()
{
	return this->maxRayLength;
}

float Player::getFov()
{
	return this->fov;
}

float Player::getVerticalFov()
{
	return this->verticalFov;
}
