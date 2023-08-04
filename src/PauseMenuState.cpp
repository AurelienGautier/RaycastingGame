#include "header/PauseMenuState.h"

PauseMenuState::PauseMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
    State(gameWindow, states),
    isEscapePressed(true),
	resumeButton(sf::Vector2f(200, 200), "Resume", 32),
	goBackToMainMenu(sf::Vector2f(200, 300), "Leave to titlescreen", 32)
{
}

void PauseMenuState::update()
{
	this->window->setMouseCursorVisible(true);

	this->updateButtons();

    if(this->isKeyPressed(this->isEscapePressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
		this->deleteState();
    }
}

void PauseMenuState::updateButtons()
{
	sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	this->resumeButton.update();

	if(this->resumeButton.isClicked(mousePosition))
	{
		this->deleteState();
	}

	this->goBackToMainMenu.update();

	if(this->goBackToMainMenu.isClicked(mousePosition))
	{
		this->currentStates->pop();
		this->currentStates->pop();
		this->currentStates->pop();
	}
}

void PauseMenuState::render()
{
	this->resumeButton.render(*this->window);
	this->goBackToMainMenu.render(*this->window);
}