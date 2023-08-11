#pragma once

#include "State.h"
#include "MapChooseState.h"
#include "MapEditorState.h"
#include "Button.h"

#include "NumberInput.h"

class MainMenuState : public State
{
private:
    Button playButton;
    Button leaveButton;
    Button mapEditorButton;

public:
    MainMenuState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);

    void update();
    void updateButtons();

    void render();
};