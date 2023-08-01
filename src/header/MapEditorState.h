#pragma once

#include "State.h"
#include "Map.h"
#include "Button.h"

class MapEditorState : public State
{
private:
    Map map;
    sf::View interfaceView;
    sf::View mapView;

    Button exitButton;

    void updateKeyboardInputs();
    void updateMouse();

    void initInterface();
    void updateButtons();
    void updateInterface();

    void renderInterface();

public:
    MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);

    void update();

    void render();
};