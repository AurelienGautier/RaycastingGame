#include "header/PauseMenuState.h"

PauseMenuState::PauseMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states) :
    State(gameWindow, states),
    isEscapePressed(false)
{
}

void PauseMenuState::update()
{
    if(this->isKeyPressed(this->isEscapePressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		State::currentState = States::GAMESTATE;
}

void PauseMenuState::render()
{

}