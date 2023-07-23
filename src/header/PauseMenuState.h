#pragma once

#include "State.h"

class PauseMenuState : public State 
{
private:
    bool isEscapePressed;

public:
    PauseMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);

    void update();

    void render();
};