#pragma once

#include "State.h"
#include "Map.h"
#include "Button.h"
#include "NumberInput.h"

class MapEditorState : public State
{
private:
    Map map;
    sf::View interfaceView;
    sf::View mapView;

    Button* exitButton;
    Button* saveButton;
    Button* changeSizeButton;

    void updateKeyboardInputs();
    void updateMouse();

    void initInterface();
    void updateButtons();
    void updateInterface();

    void renderInterface();

public:
    MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::string mapName);
    ~MapEditorState();

    void update();

    void render();
};