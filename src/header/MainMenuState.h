#pragma once

#include "State.h"
#include "Button.h"

class MainMenuState : public State
{
private:
    Button playButton;
    Button leaveButton;

public:
    MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);

    void update();
    void updateButtons();

    void render();
};