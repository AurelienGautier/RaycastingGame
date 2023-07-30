#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

enum class States
{
	MAINMENUSTATE = 0,
	GAMESTATE,
	PAUSEMENUSTATE,
	MAPEDITORSTATE
};

class State
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::map<States, std::unique_ptr<State>>> currentStates;

	bool isKeyPressed(bool& keyPressed, bool sfKeyPressed);
public:
	State(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states);

	virtual void update() = 0;
	virtual void render() = 0;

	void changeState(States newState);
	
	static States currentState;
};

