#include "header/GameState.h"
#include <iostream>

GameState::GameState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName) : 
	State(gameWindow, game),
	map("res/map/" + mapName),
	player(gameWindow->getSize().x, sf::Vector2f(2 * this->map.getCellsize(), 2 * this->map.getCellsize()), this->map.getCellsize()),
	raycasting(),
	isEscapePressed(false)
{
	sf::Vector2f windowCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);

	this->gameplayView.setCenter(sf::Vector2f(windowCenter.x, windowCenter.y));
	this->gameplayView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->gameplayView.setViewport(sf::FloatRect(0, 0, 1, 1));

	this->minimapView.setCenter(sf::Vector2f(this->window->getSize().x / 8, this->window->getSize().y / 8));
	this->minimapView.setSize(sf::Vector2f(this->window->getSize().x / 4, this->window->getSize().y / 4));
	this->minimapView.setViewport(sf::FloatRect(0, 0, 0.25, 0.25));
	this->minimapView.zoom(4);
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

void GameState::update() 
{
	this->window->setMouseCursorVisible(false);

	this->updateKeyboardInputs();
	this->updateMouseInputs();
	this->player.update();
	this->map.update(this->player);
	this->raycasting.update(this->player);
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

	float horizontalRotation = this->player.getHorizontalFov() * (mousePos.x - windowCenter.x) / this->window->getSize().x;
	float verticalRotation = this->player.getVerticalFov() * (windowCenter.y - mousePos.y) / this->window->getSize().y;

	this->player.horizontallyRotate(horizontalRotation);
	this->player.verticallyRotate(verticalRotation);

	sf::Mouse::setPosition(sf::Vector2i(windowCenter.x, windowCenter.y), *this->window);
}

/*-------------------------------------------------------------------------------*/

void GameState::render()
{
	this->render3d();
	this->raycasting.render(*this->window);

	this->map.render(*this->window, this->minimapView);

	this->player.render(*this->window, this->minimapView);

}

/*-------------------------------------------------------------------------------*/

void GameState::render3d()
{
	this->window->setView(this->gameplayView);

	std::vector<Ray> rays = this->player.getRays();

	float projectionDistance = this->map.getCellsize() / Glb::tangent(this->player.getVerticalFov() / 2);

	sf::Vector2f screenSize(this->window->getSize().x, this->window->getSize().y);

	float floorLevel = screenSize.y / 2 * (1 + Glb::tangent(this->player.getVerticalRotation()) / Glb::tangent(this->player.getVerticalFov() / 2));

	// Displaying the sky
	sf::RectangleShape skyShape(sf::Vector2f(screenSize.x, screenSize.y));
	skyShape.setFillColor(sf::Color(0, 120, 255));
	skyShape.setPosition(0, 0);
	this->window->draw(skyShape);

	// Displaying the floor
	sf::RectangleShape floorShape(sf::Vector2f(screenSize.x, screenSize.y - floorLevel));
	floorShape.setFillColor(sf::Color(0, 255, 0));
	floorShape.setPosition(0, floorLevel);
	this->window->draw(floorShape);

	// Displaying the walls
	for (int i = 0; i < screenSize.x; i++)
	{
		if (rays[i].length < this->player.getMaxRayLength())
		{
			float rayAngle = this->player.getHorizontalFov() * (floor(screenSize.x) / 2 - i) / (screenSize.x - 1);
			float rayProjectionPosition = Glb::tangent(rayAngle) / 2 / Glb::tangent(this->player.getHorizontalFov() / 2);

			int currentColumn = round(screenSize.x * (0.5f - rayProjectionPosition));
			int nextColumn = screenSize.x;

			if(i < screenSize.x - 1)
			{
				float nextRayAngle = this->player.getHorizontalFov() * (floor(screenSize.x) / 2 - 1 - i) / (screenSize.x - 1);
				rayProjectionPosition = Glb::tangent(nextRayAngle) / 2 / Glb::tangent(this->player.getHorizontalFov() / 2);
				nextColumn = round(screenSize.x * (0.5f - rayProjectionPosition));
			}

			float shapeWidth = std::max(1, nextColumn - currentColumn);
			float shapeHeight = screenSize.y * projectionDistance / (rays[i].length * Glb::cosine(rayAngle));

			int shapePosX = currentColumn;
			int shapePosY = floorLevel - shapeHeight / 2;

			sf::Sprite shape;
			shape.setTexture(Tile::getTextures()[0]);

			int texturePart = 0;

			if(rays[i].hitType == HitType::HORIZONTAL)
			{
				texturePart = rays[i].hitPoint.y - floor(rays[i].hitPoint.y / this->map.getCellsize()) * this->map.getCellsize();
			}
			else
			{
				texturePart = ceil(rays[i].hitPoint.x / this->map.getCellsize()) * this->map.getCellsize() - rays[i].hitPoint.x;
			}

			float part = Tile::getTextures()[0].getSize().x / this->map.getCellsize();

			shape.setPosition(shapePosX, shapePosY);

			shape.setTextureRect(sf::IntRect(texturePart * part, 0, part, Tile::getTextures()[0].getSize().y));

			shape.setScale(shapeWidth / part, (shapeHeight / this->map.getCellsize()) / part);

			this->window->draw(shape);
		}
	}
}

/*-------------------------------------------------------------------------------*/