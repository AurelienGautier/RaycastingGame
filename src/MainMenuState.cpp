#include "header/MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states) :
    State(gameWindow, states)
{

}

void MainMenuState::update()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

    }
}

void MainMenuState::render()
{

}