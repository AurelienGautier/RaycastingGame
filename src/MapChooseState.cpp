#include "header/MapChooseState.h"
#include <iostream>

MapChooseState::MapChooseState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
    State(gameWindow, states)
{
    this->getMapList();
}

void MapChooseState::getMapList()
{
    std::filesystem::directory_iterator dir("res/map");

    for(auto entry : dir) 
    {
        sf::Vector2f mapButtonPosition(this->window->getSize().x / 3, 0);

        if(this->mapButtonList.size() > 0)
        {
            mapButtonPosition.y = this->mapButtonList[this->mapButtonList.size() - 1].getPosition().y + 40;
        }

        Button button(mapButtonPosition, entry.path().filename().string(), 32);

        this->mapButtonList.push_back(button);
    }
}

void MapChooseState::update()
{
    for(int i = 0; i < this->mapButtonList.size(); i++)
    {
        this->mapButtonList[i].update();
    }
}

void MapChooseState::render()
{
    for(int i = 0; i < this->mapButtonList.size(); i++)
    {
        this->mapButtonList[i].render(*this->window);
    }
}
