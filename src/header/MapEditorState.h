#pragma once

#include "State.h"

class MapEditorState : public State
{
private:

public:
    MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);
};