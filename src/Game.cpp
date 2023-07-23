#include "header/Game.h"
#include <iostream>

Game::Game()
{
    this->initWindow();
    this->initStates();
}

/*-------------------------------------------------------------------------------*/

Game::~Game()
{
}

/*-------------------------------------------------------------------------------*/

void Game::initWindow()
{
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Window");
    this->window->setFramerateLimit(120);
}

/*-------------------------------------------------------------------------------*/

void Game::initStates()
{
    this->currentStates = std::make_shared<std::map<States, std::unique_ptr<State>>>();

    State::currentState = States::GAMESTATE;

    (*this->currentStates)[States::MAINMENUSTATE] = std::make_unique<MainMenuState>(this->window, this->currentStates);
    (*this->currentStates)[States::GAMESTATE] = std::make_unique<GameState>(this->window, this->currentStates);
}

/*-------------------------------------------------------------------------------*/

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}

/*-------------------------------------------------------------------------------*/

void Game::update()
{
    this->updateEvents();

    (*this->currentStates)[State::currentState]->update();

    // this->gameState->update();
}

/*-------------------------------------------------------------------------------*/

void Game::updateEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

/*-------------------------------------------------------------------------------*/

void Game::render()
{
    this->window->clear();

    (*this->currentStates)[State::currentState]->render();

    // this->gameState->render();

    this->window->display();
}

/*-------------------------------------------------------------------------------*/