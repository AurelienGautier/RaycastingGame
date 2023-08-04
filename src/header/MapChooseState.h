#pragma once

#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "MapEditorState.h"

#include <filesystem>

enum class MapChooseReason
{
    PLAY = 0,
    EDIT
};

class MapChooseState : public State
{
private:
    std::vector<Button> mapButtonList;
    MapChooseReason mapChooseReason; 

    // Functions
    void getMapList();

public:
    MapChooseState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, MapChooseReason mapChooseReason);
    void update();
    void render();
};
