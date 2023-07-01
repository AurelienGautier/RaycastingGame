#include "header/Player.h"
#include <iostream>

Player::Player(float windowWidth)
{
	this->radius = 8;

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

sf::Vector2f Player::move(std::string direction)
{
	sf::Vector2f move(0, 0);

	if (direction == "FORWARD")
	{
		move.x = cos((this->hitbox.getRotation()) * 3.14f / 180.0f);
		move.y = sin((this->hitbox.getRotation()) * 3.14f / 180.0f);
	}
	else if (direction == "RIGHT")
	{
		move.x = cos((this->hitbox.getRotation() + 90) * 3.14f / 180.0f);
		move.y = sin((this->hitbox.getRotation() + 90) * 3.14f / 180.0f);
	}
	else if (direction == "LEFT")
	{
		move.x = cos((this->hitbox.getRotation() - 90) * 3.14f / 180.0f);
		move.y = sin((this->hitbox.getRotation() - 90) * 3.14f / 180.0f);
	}
	else if (direction == "BACK")
	{
		move.x = -cos((this->hitbox.getRotation()) * 3.14f / 180.0f);
		move.y = -sin((this->hitbox.getRotation()) * 3.14f / 180.0f);
	}

	return move;
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

void Player::setPosition(float x, float y)
{
	this->hitbox.setPosition(x, y);
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

/*-------------------------------------------------------------------------------*/