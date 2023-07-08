#pragma once
#include "State.h"
#include "Player.h"
#include "Map.h"
#include "Global.h"
#include <iostream> // temporaire

class GameState : public State
{
private:
	Player player;
	Map map;
	sf::View gameplayView;
	sf::View minimapView;
	int const cellSize3d = 32;

public:
	GameState(std::shared_ptr<sf::RenderWindow> gameWindow);

	void update();
	void updateKeyboardInputs();
	void updateMouseInputs();

	void render();
	void render3d();
};

