#pragma once

#include "State.h"
#include "MapChooseState.h"
#include "MapEditorState.h"
#include "Button.h"

#include "NumberInput.h"
#include "Game.h"

class MainMenuState : public State
{
private:
    Button playButton;
    Button leaveButton;
    Button mapEditorButton;

    MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);
    static MainMenuState* instance;

public:
    static MainMenuState* getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);

    void update();
    void updateButtons();

    void render();
};