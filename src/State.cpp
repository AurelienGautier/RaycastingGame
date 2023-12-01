#include "header/State.h"
#include "header/Game.h"

bool State::defaultViewSet = false;
sf::View State::defaultView;

/*-------------------------------------------------------------------------------*/

State::State(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game)
{
	this->window = gameWindow;
    this->game = game;

    if(!State::defaultViewSet)
    {
        this->initDefaultView();
    }

    State::setDefaultView();
}

/*-------------------------------------------------------------------------------*/

void State::initDefaultView()
{
    State::defaultView.setSize(
        this->window->getSize().x,
        this->window->getSize().y
    );

    State::defaultView.setCenter(
        this->window->getSize().x / 2,
        this->window->getSize().y / 2);

    State::defaultView.setViewport(sf::FloatRect(0, 0, 1, 1));

    State::defaultViewSet = true;
}

/*-------------------------------------------------------------------------------*/

void State::setDefaultView()
{
    this->window->setView(State::defaultView);

    sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
}

/*-------------------------------------------------------------------------------*/

bool State::isKeyPressed(bool& keyPressed, bool sfKeyPressed)
{
	if(keyPressed)
    {
        if(!sfKeyPressed)
        {
            keyPressed = false;
        }
    }
    else if(sfKeyPressed)
    {
        keyPressed = true;
        return true;
    }

    return false;
}

/*-------------------------------------------------------------------------------*/