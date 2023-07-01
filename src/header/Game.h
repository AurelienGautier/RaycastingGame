#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <memory>
#include "State.h"
#include "GameState.h"

class Game
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;
	std::shared_ptr<GameState> gameState;

public:
	Game();
	~Game();

	void initWindow();

	void run();

	void update();
	void updateEvents();

	void render();
};

