#pragma once

#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "MapEditorState.h"
#include "Game.h"

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

    MapChooseState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);
    static MapChooseState* instance;
    void setChooseReason(MapChooseReason mapChooseReason);

public:
    static MapChooseState* getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, MapChooseReason mapChooseReason);

    void update();
    void render();
};
