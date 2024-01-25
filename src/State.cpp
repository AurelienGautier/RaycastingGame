#include "header/State.h"
#include "header/Game.h"

/*-------------------------------------------------------------------------------*/

State::State(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game)
{
	this->window = gameWindow;
    this->game = game;
}

State::~State()
{
    this->game = nullptr;
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