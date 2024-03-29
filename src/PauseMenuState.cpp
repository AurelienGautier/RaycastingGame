#include "header/PauseMenuState.h"

PauseMenuState::PauseMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game) :
    State(gameWindow, game),
    isEscapePressed(true),
	resumeButton(sf::Vector2f(200, 200), "Resume", 32),
	goBackToMainMenu(sf::Vector2f(200, 300), "Leave to titlescreen", 32)
{
}

/*-------------------------------------------------------------------------------*/

PauseMenuState* PauseMenuState::instance = nullptr;

PauseMenuState* PauseMenuState::getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game)
{
	if(instance == nullptr)
	{
		instance = new PauseMenuState(gameWindow, game);
	}

	return instance;
}

/*-------------------------------------------------------------------------------*/

void PauseMenuState::update()
{
	this->window->setMouseCursorVisible(true);


    if(this->isKeyPressed(this->isEscapePressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
		this->game->setState(GameState::getInstance());
    }

	this->updateButtons();
}

/*-------------------------------------------------------------------------------*/

void PauseMenuState::updateButtons()
{
	sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	this->resumeButton.update();

	if(this->resumeButton.isClicked(mousePosition))
	{
		sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
		this->game->setState(GameState::getInstance());
		this->isEscapePressed = true;
	}

	this->goBackToMainMenu.update();

	if(this->goBackToMainMenu.isClicked(mousePosition))
	{
		this->game->setState(MainMenuState::getInstance(this->window, this->game));
		this->isEscapePressed = true;
	}
}

/*-------------------------------------------------------------------------------*/

void PauseMenuState::render()
{
	this->resumeButton.render(*this->window);
	this->goBackToMainMenu.render(*this->window);
}

/*-------------------------------------------------------------------------------*/