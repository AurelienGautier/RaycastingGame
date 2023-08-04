#include "header/State.h"

State::State(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states)
{
	this->window = gameWindow;
	this->currentStates = states;

    State::setDefaultView();
}

void State::setDefaultView()
{
    if(!State::defaultViewSet)
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

    this->window->setView(State::defaultView);

    sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
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

void State::deleteState()
{
    State::setDefaultView();
    
    this->currentStates->pop();
}