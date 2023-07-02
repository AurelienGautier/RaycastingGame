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

	sf::VertexArray fovVisualization(sf::TriangleFan, 1 + this->rays.size());
	fovVisualization[0].position = this->hitbox.getPosition();

	for (int i = 0; i < this->rays.size(); i++)
	{
		float angle = (this->hitbox.getRotation() - this->fov / 2) + (i * this->fov / this->rays.size());
		if (angle < 0) angle += 360;
		if (angle > 360) angle -= 360;

		fovVisualization[1 + i].position = sf::Vector2f(
			this->hitbox.getPosition().x + rays[i] * cos(angle * 3.14f / 180.0f),
			this->hitbox.getPosition().y + rays[i] * sin(angle * 3.14f / 180.0f));
	}

	window->draw(fovVisualization);

	view.setCenter(this->hitbox.getPosition());
}

/*-------------------------------------------------------------------------------*/

void Player::update()
{
	for (int i = 0; i < this->rays.size(); i++)
	{
		this->rays[i] = this->maxRayLength;
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
		this->rays.push_back(this->maxRayLength);
	}
}

/*-------------------------------------------------------------------------------*/

std::vector<float> Player::getRays()
{
	return this->rays;
}

void Player::setRaySize(int index, float raySize)
{
	this->rays[index] = raySize;
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