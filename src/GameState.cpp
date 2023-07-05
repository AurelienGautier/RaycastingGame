#include "header/GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> gameWindow) : State(gameWindow)
{
	this->player = std::make_shared<Player>(gameWindow->getSize().x);
	this->window->setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
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
	this->player->update();
	this->map.updateFovContact(this->player);
}

void GameState::updateInputs()
{
	// movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->map.movePlayer(this->player, "FORWARD");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->map.movePlayer(this->player, "RIGHT");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		this->map.movePlayer(this->player, "LEFT");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->map.movePlayer(this->player, "BACK");
}

void GameState::updateMouseInputs()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

	sf::Vector2f windowCenter(
		this->window->getSize().x / 2, this->window->getSize().y / 2);

	float horizontalRotation = this->player->getFov() * (mousePos.x - windowCenter.x) / this->window->getSize().x;
	float verticalRotation = this->player->getVerticalFov() * (windowCenter.y - mousePos.y) / this->window->getSize().y;

	this->player->rotate(horizontalRotation);
	this->player->setVerticalRotation(this->player->getVerticalRotation() + verticalRotation);

	sf::Mouse::setPosition(sf::Vector2i(windowCenter.x, windowCenter.y), *this->window);
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

	std::vector<float> rays = this->player->getRays();

	float projectionDistance = 32 / tan((this->player->getVerticalFov() / 2) * 3.14f / 180.0f);

	float screenWidth = this->window->getSize().x;
	float screenHeight = this->window->getSize().y;

	float floorLevel = round(screenHeight / 2 * (1 + tan(this->player->getVerticalRotation() * 3.14f / 180.0f) / tan(this->player->getVerticalFov() / 2  * 3.14f / 180.0f)));

	for (int i = 0; i < screenWidth; i++)
	{
		if (rays[i] < this->player->getMaxRayLength())
		{
			float rayAngle = this->player->getFov() * (floor(screenWidth) / 2 - i) / (screenWidth - 1);
			float shapeHeight = screenHeight * projectionDistance / (rays[i] * cos(rayAngle * 3.14f / 180.0f));

			sf::RectangleShape shape(sf::Vector2f(1, shapeHeight));
			shape.setFillColor(sf::Color(255 * (1 - rays[i] / 1024), 0, 0));
			shape.setPosition(i, (floorLevel - shapeHeight) / 2);

			this->window->draw(shape);
		}
	}
}

bool GameState::canMove(int x, int y)
{
	bool canMove = true;

	return canMove;
}
