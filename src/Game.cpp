#include "header/Game.h"

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
    this->currentStates = std::make_shared<std::stack<std::unique_ptr<State>>>();

    this->currentStates->push(std::make_unique<MainMenuState>(this->window, this->currentStates));
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

    (*this->currentStates).top()->update();
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

    (*this->currentStates).top()->render();

    this->window->display();
}

/*-------------------------------------------------------------------------------*/