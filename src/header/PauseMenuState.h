#pragma once

#include "State.h"
#include "Button.h"

class PauseMenuState : public State 
{
private:
    bool isEscapePressed;
    Button resumeButton;
    Button goBackToMainMenu;

public:
    PauseMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);

    void update();
    void updateButtons();

    void render();
};