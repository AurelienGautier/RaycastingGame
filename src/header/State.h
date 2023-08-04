#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

class State
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::stack<std::unique_ptr<State>>> currentStates;

	// For the default view
	sf::View defaultView;
	bool defaultViewSet = false;
	void setDefaultView();

	bool isKeyPressed(bool& keyPressed, bool sfKeyPressed);
public:
	State(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);

	virtual void update() = 0;
	virtual void render() = 0;

	// To change the current state of the game
	void deleteState();
};

