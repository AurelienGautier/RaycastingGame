#include "header/Player.h"
#include <iostream>

Player::Player(float windowWidth)
{
	this->radius = 8;

	this->hitbox.setRadius(this->radius);

	this->hitbox.setPosition(sf::Vector2f(32, 32));

	this->hitbox.setFillColor(sf::Color::Red);

	this->hitbox.setOrigin(this->getRadius(), this->getRadius());

	this->horizontalFov = 90.f;

	this->verticalFov = 60.f;

	this->initRays(windowWidth);

	this->verticalRotation = 0;
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
// Getters

std::vector<float> Player::getRays()
{
	return this->rays;
}


sf::Vector2f Player::getPosition()
{
	return this->hitbox.getPosition();
}


float Player::getRadius()
{
	return this->radius;
}


float Player::getMaxRayLength()
{
	return this->maxRayLength;
}


float Player::getHorizontalRotation()
{
	return this->hitbox.getRotation();
}


float Player::getVerticalRotation()
{
	return this->verticalRotation;
}


float Player::getHorizontalFov()
{
	return this->horizontalFov;
}


float Player::getVerticalFov()
{
	return this->verticalFov;
}

/*-------------------------------------------------------------------------------*/
// Setters
void Player::setPosition(float x, float y)
{
	this->hitbox.setPosition(x, y);
}

void Player::setRaySize(int index, float raySize)
{
	this->rays[index] = raySize;
}

/*-------------------------------------------------------------------------------*/
// Public methods

void Player::update()
{
	for (int i = 0; i < this->rays.size(); i++)
	{
		this->rays[i] = this->maxRayLength;
	}
}

/*---------------------------------------*/

void Player::render(std::shared_ptr<sf::RenderWindow> window, sf::View& view)
{
	window->setView(view);

	window->draw(this->hitbox);

	sf::VertexArray fovVisualization(sf::TriangleFan, 1 + this->rays.size());
	fovVisualization[0].position = this->getPosition();

	for (int i = 0; i < this->rays.size(); i++)
	{
		float angle = fmod((this->getHorizontalRotation() - this->horizontalFov / 2) + (i * this->horizontalFov / this->rays.size()), 360);

		fovVisualization[1 + i].position = sf::Vector2f(
			this->getPosition().x + rays[i] * Glb::cosine(angle),
			this->getPosition().y + rays[i] * Glb::sinus(angle));
	}

	window->draw(fovVisualization);
	view.setCenter(this->getPosition());
}

/*---------------------------------------*/

sf::Vector2f Player::getNextMove(std::string direction)
{
	sf::Vector2f move(0, 0);

	if (direction == "FORWARD")
	{
		move.x = Glb::cosine(this->getHorizontalRotation());
		move.y = Glb::sinus(this->getHorizontalRotation());
	}
	else if (direction == "RIGHT")

	{
		move.x = Glb::cosine(this->getHorizontalRotation() + 90);
		move.y = Glb::sinus(this->getHorizontalRotation() + 90);
	}
	else if (direction == "LEFT")
	{
		move.x = Glb::cosine(this->getHorizontalRotation() - 90);
		move.y = Glb::sinus(this->getHorizontalRotation() - 90);
	}
	else if (direction == "BACK")
	{
		move.x = -Glb::cosine(this->getHorizontalRotation());
		move.y = -Glb::sinus(this->getHorizontalRotation());
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

