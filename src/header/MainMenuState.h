#pragma once

#include "State.h"
#include "Button.h"
#include <array>

class MainMenuState : public State
{
private:
    Button playButton;
    Button leaveButton;
    Button mapEditorButton;

public:
    MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);

    void update();
    void updateButtons();

    void render();
};