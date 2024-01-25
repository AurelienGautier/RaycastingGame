#include "header/GameState.h"
#include <iostream>

GameState::GameState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName) : 
	State(gameWindow, game),
	map("res/map/" + mapName),
	player(sf::Vector2f(2 * this->map.getCellsize(), 2 * this->map.getCellsize()), this->map.getCellsize()),
	raycasting(gameWindow->getSize().x),
	isEscapePressed(false)
{
	sf::Vector2f windowCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
}

/*-------------------------------------------------------------------------------*/

GameState::~GameState()
{
	delete this->instance;
}

/*-------------------------------------------------------------------------------*/

GameState* GameState::instance = nullptr;

GameState* GameState::getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName)
{
	if(instance == nullptr)
	{
		instance = new GameState(gameWindow, game, mapName);
	}

	instance->isEscapePressed = false;

	return instance;
}

/*-------------------------------------------------------------------------------*/

GameState* GameState::getInstance()
{
	return instance;
}

/*-------------------------------------------------------------------------------*/

void GameState::loadMap(std::string mapName)
{
	this->map.loadMap("res/map/" + mapName);
	this->player.setPosition(2 * this->map.getCellsize(), 2 * this->map.getCellsize());
}

void GameState::update() 
{
	this->window->setMouseCursorVisible(false);

	this->updateKeyboardInputs();
	this->updateMouseInputs();
	this->player.update();
	this->map.update(this->player);
	this->raycasting.update(this->player, this->map);
}

/*-------------------------------------------------------------------------------*/

void GameState::updateKeyboardInputs()
{
	// movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->map.movePlayer(this->player, Direction::FORWARD);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->map.movePlayer(this->player, Direction::RIGHT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		this->map.movePlayer(this->player, Direction::LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->map.movePlayer(this->player, Direction::BACK);

	// pause
	if(this->isKeyPressed(this->isEscapePressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
	{
		this->game->setState(PauseMenuState::getInstance(this->window, this->game));
	}
}

/*-------------------------------------------------------------------------------*/

void GameState::updateMouseInputs()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

	sf::Vector2f windowCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);

	float horizontalRotation = this->raycasting.getHorizontalFov() * (mousePos.x - windowCenter.x) / this->window->getSize().x;
	float verticalRotation = this->raycasting.getVerticalFov() * (windowCenter.y - mousePos.y) / this->window->getSize().y;

	this->player.horizontallyRotate(horizontalRotation);
	this->player.verticallyRotate(verticalRotation);

	sf::Mouse::setPosition(sf::Vector2i(windowCenter.x, windowCenter.y), *this->window);
}

/*-------------------------------------------------------------------------------*/

void GameState::render()
{
	this->raycasting.render(*this->window, this->player, this->map);
}

/*-------------------------------------------------------------------------------*/