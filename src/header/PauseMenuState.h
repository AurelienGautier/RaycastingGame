#pragma once

#include "State.h"
#include "Button.h"
#include "Game.h"

class PauseMenuState : public State 
{
private:
    bool isEscapePressed;
    Button resumeButton;
    Button goBackToMainMenu;

    static PauseMenuState* instance;
    PauseMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);

public:
    static PauseMenuState* getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);

    void update();
    void updateButtons();

    void render();
};