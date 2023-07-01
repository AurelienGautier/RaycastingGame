#include "header/Game.h"
#include <iostream>

Game::Game()
{
    this->initWindow();
    this->gameState = std::make_shared<GameState>(this->window);
}

/*-------------------------------------------------------------------------------*/

Game::~Game()
{
}

/*-------------------------------------------------------------------------------*/

void Game::initWindow()
{
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Window");
    this->window->setFramerateLimit(60);
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

    this->gameState->update();
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

    this->gameState->render();

    this->window->display();
}

/*-------------------------------------------------------------------------------*/