#include "header/State.h"

States State::currentState = States::MAINMENUSTATE;

State::State(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states)
{
	this->window = gameWindow;
	this->currentStates = states;

    if(!State::defaultViewSet)
    {
        State::setDefaultView();

        State::defaultViewSet = true;
    }
}

void State::setDefaultView()
{
    State::defaultView.setSize(
        this->window->getSize().x,
        this->window->getSize().y
    );

    State::defaultView.setCenter(
        this->window->getSize().x / 2,
        this->window->getSize().y / 2);

    State::defaultView.setViewport(sf::FloatRect(0, 0, 1, 1));
}

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

void State::changeState(States newState)
{
    this->window->setView(State::defaultView);

    State::setDefaultView();

    sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);

    State::currentState = newState;
}