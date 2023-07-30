#pragma once

#include "State.h"
#include "Map.h"

class MapEditorState : public State
{
private:
    Map map;
    sf::View view;

    void updateKeyboardInputs();

public:
    MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);

    void update();

    void render();
};