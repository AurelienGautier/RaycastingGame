#include "header/PauseMenuState.h"
#include <iostream>

PauseMenuState::PauseMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states) :
    State(gameWindow, states),
    isEscapePressed(true)
{
}

void PauseMenuState::update()
{
    if(this->isKeyPressed(this->isEscapePressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
		this->changeState(States::GAMESTATE);
    }
}

void PauseMenuState::render()
{

}