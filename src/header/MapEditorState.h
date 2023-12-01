#pragma once

#include "State.h"
#include "Map.h"
#include "Button.h"
#include "NumberInput.h"
#include "Game.h"

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

    MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName);
    static MapEditorState* instance;

public:
    static MapEditorState* getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName);

    ~MapEditorState();

    void update();

    void render();
};