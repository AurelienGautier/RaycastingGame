#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class State
{
private:

protected:
	std::shared_ptr<sf::RenderWindow> window;
	Game* game;
	bool isKeyPressed(bool& keyPressed, bool sfKeyPressed);
	
public:
	State(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);
	virtual ~State();

	virtual void update() = 0;
	virtual void render() = 0;
};
