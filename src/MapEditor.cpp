#include "header/MapEditorState.h"

MapEditorState::MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states) :
    State(gameWindow, states)
{
}

void MapEditorState::update()
{

}

void MapEditorState::render()
{
    
}