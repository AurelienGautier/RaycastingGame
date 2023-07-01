#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class State
{
protected:
	std::shared_ptr<sf::RenderWindow> window;

public:
	State(std::shared_ptr<sf::RenderWindow> gameWindow);

	virtual void update() = 0;
	virtual void render() = 0;
};

