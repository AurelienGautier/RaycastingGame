#pragma once

#include "State.h"
#include "Player.h"
#include "Map.h"
#include "Global.h"
#include "PauseMenuState.h"

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
public:
	GameState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::string mapName);

	void update();

	void render();
};

