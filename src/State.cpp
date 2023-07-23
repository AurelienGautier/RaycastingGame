#include "header/State.h"
#include <iostream>

States State::currentState = States::MAINMENUSTATE;

State::State(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states)
{
	this->window = gameWindow;
	this->currentStates = states;
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