#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.h"
#include "Tile.h"

class Map
{
private:
	std::vector<std::vector<Tile>> cells;
	const int cellSize = 16;

	sf::Vector2f getDeltaFactor(float angle);

public:
	Map();

	void update();
	void updateCollision(std::shared_ptr<Player> player);
	void render(std::shared_ptr<sf::RenderWindow> window, sf::View& view);

	void convertMap(std::vector<std::vector<int>> intMap);
	void updateFovContact(std::shared_ptr<Player> player);
};

