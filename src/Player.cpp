#include "header/Player.h"

Player::Player(float windowWidth) :
	radius(8), 
	maxRayLength(400),
	horizontalFov(90.f),
	verticalFov(60.f),
	verticalRotation(0) 
{
	this->initHitbox();

	this->initRays(windowWidth);
}

/*-------------------------------------------------------------------------------*/
// Initialization methods

void Player::initHitbox()
{
	this->hitbox.setRadius(this->radius);

	this->hitbox.setPosition(sf::Vector2f(32, 32));

	this->hitbox.setFillColor(sf::Color::Red);

	this->hitbox.setOrigin(this->radius, this->radius);
}

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

void Player::render(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);

	window.draw(this->hitbox);

	sf::VertexArray fovVisualization(sf::TriangleFan, 1 + this->rays.size());
	fovVisualization[0].position = this->getPosition();

	for (int i = 0; i < this->rays.size(); i++)
	{
		float angle = this->calculateRayAngle(i);

		fovVisualization[1 + i].position = sf::Vector2f(
			this->getPosition().x + rays[i] * Glb::cosine(angle),
			this->getPosition().y + rays[i] * Glb::sinus(angle));
	}

	window.draw(fovVisualization);
	view.setCenter(this->getPosition());
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

float Player::calculateRayAngle(int rayIndex)
{
	float playerFovStart = this->getHorizontalRotation() - this->horizontalFov / 2;
	float rayPerDegree = this->horizontalFov / this->rays.size();

	float angle = playerFovStart + rayPerDegree * rayIndex;

	if(angle < 0) angle += 360;
	else if(angle >= 360) angle -= 360;

	return angle;
}

/*-------------------------------------------------------------------------------*/