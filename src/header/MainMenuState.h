#pragma once

#include "State.h"

class MainMenuState : public State
{
private:


public:
    MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);

    void update();

    void render();
};