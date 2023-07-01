#include "header/GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> gameWindow) : State(gameWindow)
{
	this->player = std::make_shared<Player>(gameWindow->getSize().x);
	this->window->setMouseCursorVisible(false);
	this->mousePosition = sf::Mouse::getPosition(*this->window);

	this->gameplayView.setCenter(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2));
	this->gameplayView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->gameplayView.setViewport(sf::FloatRect(0, 0, 1, 1));

	this->minimapView.setCenter(sf::Vector2f(this->window->getSize().x / 8, this->window->getSize().y / 8));
	this->minimapView.setSize(sf::Vector2f(this->window->getSize().x / 4, this->window->getSize().y / 4));
	this->minimapView.setViewport(sf::FloatRect(0, 0, 0.25, 0.25));
	this->minimapView.zoom(2);
}

void GameState::update() 
{
	this->updateInputs();
	this->updateMouseInputs();
	this->map.updateCollision(this->player);
	this->player->update();
	this->map.updateFovContact(this->player);
}

void GameState::updateInputs()
{
	// movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->player->move("FORWARD");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move("RIGHT");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		this->player->move("LEFT");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move("BACK");
}

void GameState::updateMouseInputs()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	float rotationAngle = (float(mousePos.x) - float(this->mousePosition.x)) / 16;

	this->player->rotate(rotationAngle);

	/*if(mousePos.x != this->window->getSize().x / 2 || mousePos.y != this->window->getSize().y / 2)
	{
		sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
		mousePos.x = this->window->getSize().x / 2;
		mousePos.y = this->window->getSize().y / 2;
	}*/

	this->mousePosition = mousePos;
}

void GameState::render()
{
	this->render3d();

	this->map.render(this->window, this->minimapView);

	this->player->render(this->window, this->minimapView);
}

void GameState::render3d()
{
	this->window->setView(this->gameplayView);

	std::vector<sf::RectangleShape> rays = this->player->getRays();

	float projectionDistance = 32 / tan((this->player->getVerticalFov() / 2) * 3.14f / 180.0f);

	float screenWidth = this->window->getSize().x;
	float screenHeight = this->window->getSize().y;

	for (int i = 0; i < screenWidth; i++)
	{
		if (rays[i].getSize().x < this->player->getMaxRayLength())
		{
			float rayAngle = this->player->getFov() * (floor(screenWidth) / 2 - i) / (screenWidth - 1);
			float shapeHeight = screenHeight * projectionDistance / (rays[i].getSize().x * cos(rayAngle * 3.14f / 180.0f));

			sf::RectangleShape shape(sf::Vector2f(1, shapeHeight));
			shape.setFillColor(sf::Color(255 * (1 - rays[i].getSize().x / 1024), 0, 0));
			shape.setPosition(i, (screenHeight - shapeHeight) / 2);

			this->window->draw(shape);
		}
	}
}

bool GameState::canMove(int x, int y)
{
	bool canMove = true;

	return canMove;
}
