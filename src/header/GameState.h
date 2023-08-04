#pragma once

#include "State.h"
#include "Player.h"
#include "Map.h"
#include "Global.h"
#include "PauseMenuState.h"

class GameState : public State
{
private:
	Player player;
	Map map;
	sf::View gameplayView;
	sf::View minimapView;
	int const cellSize3d = 32;
	bool isEscapePressed;

	void updateKeyboardInputs();
	void updateMouseInputs();

	void render3d();
public:
	GameState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);

	void update();

	void render();
};

