#pragma once

#include "State.h"
#include "Player.h"
#include "Map.h"
#include "Global.h"
#include "PauseMenuState.h"
#include "Game.h"

class GameState : public State
{
private:
	Map map;
	Player player;
	sf::View gameplayView;
	sf::View minimapView;
	bool isEscapePressed;

	void updateKeyboardInputs();
	void updateMouseInputs();

	void render3d();
	void render3dFloor();

	GameState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName);
	static GameState* instance;

public:
	static GameState* getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName);
	static GameState* getInstance();

	void update();

	void render();
};

