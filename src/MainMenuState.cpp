#include "header/MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game) :
    State(gameWindow, game),
    playButton(sf::Vector2f(200, 200), "Play", 32),
    mapEditorButton(sf::Vector2f(200, 300), "MapEditor", 32),
    leaveButton(sf::Vector2f(200, 400), "Quit", 32)
{
}

/*-------------------------------------------------------------------------------*/

MainMenuState* MainMenuState::instance = nullptr;

MainMenuState* MainMenuState::getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game)
{
    if(instance == nullptr)
	{
		instance = new MainMenuState(gameWindow, game);
	}

	return instance;
}

/*-------------------------------------------------------------------------------*/

void MainMenuState::update()
{
    this->window->setMouseCursorVisible(true);

    this->updateButtons();
}

/*-------------------------------------------------------------------------------*/

void MainMenuState::updateButtons()
{
    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->playButton.update();
    
    if(this->playButton.isClicked(mousePosition))
    {
        this->game->setState(MapChooseState::getInstance(this->window, this->game, MapChooseReason::PLAY));
    }

    this->mapEditorButton.update();

    if(this->mapEditorButton.isClicked(mousePosition))
    {
        this->game->setState(MapChooseState::getInstance(this->window, this->game, MapChooseReason::EDIT));
    }

    this->leaveButton.update();

    if(this->leaveButton.isClicked(mousePosition))
    {
        this->window->close();
    }
}

/*-------------------------------------------------------------------------------*/

void MainMenuState::render()
{
    this->playButton.render(*this->window);
    this->mapEditorButton.render(*this->window);
    this->leaveButton.render(*this->window);
}

/*-------------------------------------------------------------------------------*/