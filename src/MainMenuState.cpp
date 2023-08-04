#include "header/MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
    State(gameWindow, states),
    playButton(sf::Vector2f(200, 200), "Play", 32),
    mapEditorButton(sf::Vector2f(200, 300), "MapEditor", 32),
    leaveButton(sf::Vector2f(200, 400), "Quit", 32)
{
}

void MainMenuState::update()
{
    this->window->setMouseCursorVisible(true);

    this->updateButtons();
}

void MainMenuState::updateButtons()
{
    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->playButton.update();
    
    if(this->playButton.isClicked(mousePosition))
    {
        (*this->currentStates).push(std::make_unique<MapChooseState>(this->window, this->currentStates));
    }

    this->mapEditorButton.update();

    if(this->mapEditorButton.isClicked(mousePosition))
    {
        (*this->currentStates).push(std::make_unique<MapEditorState>(this->window, this->currentStates));
    }

    this->leaveButton.update();

    if(this->leaveButton.isClicked(mousePosition))
    {
        this->window->close();
    }
}

void MainMenuState::render()
{
    this->playButton.render(*this->window);
    this->mapEditorButton.render(*this->window);
    this->leaveButton.render(*this->window);
}