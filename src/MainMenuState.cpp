#include "header/MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states) :
    State(gameWindow, states),
    playButton(sf::Vector2f(200, 200), "Play", 32)
{
}

void MainMenuState::update()
{
    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->playButton.update();
    
    if(this->playButton.isClicked(mousePosition))
    {
        this->changeState(States::GAMESTATE);
    }
}

void MainMenuState::render()
{
    this->playButton.render(this->window);
}