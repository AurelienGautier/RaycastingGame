#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class State
{
private:
	// For the default view
	static sf::View defaultView;
	static bool defaultViewSet;
	void initDefaultView();
	void setDefaultView();

protected:
	std::shared_ptr<sf::RenderWindow> window;
	Game* game;
	bool isKeyPressed(bool& keyPressed, bool sfKeyPressed);
	
public:
	State(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game);

	virtual void update() = 0;
	virtual void render() = 0;
};
