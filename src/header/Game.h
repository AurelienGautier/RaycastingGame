#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <memory>

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"

class Game
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;
	std::shared_ptr<std::map<States, std::unique_ptr<State>>> currentStates;

public:
	Game();
	~Game();

	void initWindow();
	void initStates();

	void run();

	void update();
	void updateEvents();

	void render();
};

