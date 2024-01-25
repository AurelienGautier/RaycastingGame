#include "header/MapChooseState.h"

MapChooseState::MapChooseState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game) :
    State(gameWindow, game)
{
    this->getMapList();
}

/*-------------------------------------------------------------------------------*/

MapChooseState* MapChooseState::instance = nullptr;

MapChooseState* MapChooseState::getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, MapChooseReason mapChooseReason)
{
    if(instance == nullptr)
	{
		instance = new MapChooseState(gameWindow, game);
	}

    instance->setChooseReason(mapChooseReason);

	return instance;
}

/*-------------------------------------------------------------------------------*/

void MapChooseState::setChooseReason(MapChooseReason mapChooseReason)
{
    this->mapChooseReason = mapChooseReason;
}

/*-------------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------------*/

void MapChooseState::update()
{
    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    for(int i = 0; i < this->mapButtonList.size(); i++)
    {
        this->mapButtonList[i].update();

        if(this->mapButtonList[i].isClicked(mousePosition))
        {
            sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
            
            if(this->mapChooseReason == MapChooseReason::PLAY)
            {
                this->game->setState(GameState::getInstance(this->window, this->game, this->mapButtonList[i].getText()));
            }
            else if(this->mapChooseReason == MapChooseReason::EDIT)
            {
                this->game->setState(MapEditorState::getInstance(this->window, this->game, this->mapButtonList[i].getText()));
            }
        }
    }
}

/*-------------------------------------------------------------------------------*/

void MapChooseState::render()
{
    for(int i = 0; i < this->mapButtonList.size(); i++)
    {
        this->mapButtonList[i].render(*this->window);
    }
}

/*-------------------------------------------------------------------------------*/
