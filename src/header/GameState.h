#pragma once
#include "State.h"
#include "Player.h"
#include "Map.h"
#include <iostream> // temporaire

class GameState : public State
{
private:
	std::shared_ptr<Player> player;
	Map map;
	sf::Vector2i mousePosition;
	sf::View gameplayView;
	sf::View minimapView;

public:
	GameState(std::shared_ptr<sf::RenderWindow> gameWindow);

	void update();
	void updateInputs();
	void updateMouseInputs();

	void render();
	void render3d();

	bool canMove(int x, int y);
};

