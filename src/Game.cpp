#include "header/Game.h"

Game::Game()
{
    this->initWindow();
    this->initStates();
}

/*-------------------------------------------------------------------------------*/

Game::~Game()
{
    delete this->currentState;
}

/*-------------------------------------------------------------------------------*/

void Game::setState(State* state)
{
    sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
    this->currentState = state;
}

/*-------------------------------------------------------------------------------*/

void Game::initWindow()
{
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Window");
    this->window->setFramerateLimit(120);
}

/*-------------------------------------------------------------------------------*/

void Game::initStates()
{
    this->currentState = MainMenuState::getInstance(this->window, this);
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

    this->currentState->update();
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

    this->currentState->render();

    this->window->display();
}

/*-------------------------------------------------------------------------------*/