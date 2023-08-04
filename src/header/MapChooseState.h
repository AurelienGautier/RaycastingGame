#pragma once

#include "State.h"
#include "Button.h"
#include "GameState.h"

#include <filesystem>

class MapChooseState : public State
{
private:
    std::vector<Button> mapButtonList;

    // Functions
    void getMapList();

public:
    MapChooseState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
    void update();
    void render();
};
