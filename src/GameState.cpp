#include "header/GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::string mapName) : 
	State(gameWindow, states),
	player(gameWindow->getSize().x),
	map("res/map/" + mapName),
	isEscapePressed(false)
{
	sf::Vector2f windowCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);

	sf::Mouse::setPosition(sf::Vector2i(windowCenter.x, windowCenter.y), *this->window);

	this->gameplayView.setCenter(sf::Vector2f(windowCenter.x, windowCenter.y));
	this->gameplayView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->gameplayView.setViewport(sf::FloatRect(0, 0, 1, 1));

	this->minimapView.setCenter(sf::Vector2f(this->window->getSize().x / 8, this->window->getSize().y / 8));
	this->minimapView.setSize(sf::Vector2f(this->window->getSize().x / 4, this->window->getSize().y / 4));
	this->minimapView.setViewport(sf::FloatRect(0, 0, 0.25, 0.25));
	this->minimapView.zoom(2);
}

/*-------------------------------------------------------------------------------*/

void GameState::update() 
{
	this->window->setMouseCursorVisible(false);

	this->updateKeyboardInputs();
	this->updateMouseInputs();
	this->player.update();
	this->map.update(this->player);
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
		(*this->currentStates).push(std::make_unique<PauseMenuState>(this->window, this->currentStates));
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

	this->map.render(*this->window, this->minimapView);

	this->player.render(*this->window, this->minimapView);
}

/*-------------------------------------------------------------------------------*/

void GameState::render3d()
{
	this->window->setView(this->gameplayView);

	std::vector<float> rays = this->player.getRays();

	float projectionDistance = this->cellSize3d / Glb::tangent(this->player.getVerticalFov() / 2);

	sf::Vector2f screenSize(this->window->getSize().x, this->window->getSize().y);

	float floorLevel = screenSize.y / 2 * (1 + Glb::tangent(this->player.getVerticalRotation()) / Glb::tangent(this->player.getVerticalFov() / 2));

	for (int i = 0; i < screenSize.x; i++)
	{
		if (rays[i] < this->player.getMaxRayLength())
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
			float shapeHeight = screenSize.y * projectionDistance / (rays[i] * Glb::cosine(rayAngle));

			int shapePosX = currentColumn;
			int shapePosY = floorLevel - shapeHeight / 2;

			sf::RectangleShape shape(sf::Vector2f(shapeWidth, shapeHeight));
			shape.setFillColor(sf::Color(255 * (1 - rays[i] / 1024), 0, 0));
			shape.setPosition(shapePosX, shapePosY);

			this->window->draw(shape);
		}
	}
}

/*-------------------------------------------------------------------------------*/