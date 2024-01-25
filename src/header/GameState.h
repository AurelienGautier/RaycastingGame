#pragma once

#include "State.h"
#include "Player.h"
#include "Map.h"
#include "Global.h"
#include "PauseMenuState.h"
#include "Game.h"
#include "Raycasting.h"

class GameState : public State
{
private:
	Map map;
	Player player;
	Raycasting raycasting;
	bool isEscapePressed;

	void updateKeyboardInputs();
	void updateMouseInputs();

	void render3dFloor();

	GameState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);
	static GameState* instance;

public:
	static GameState* getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);
	static GameState* getInstance();
	void loadMap(std::string mapName);
	
	~GameState();

	void update();

	void render();
};

