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
	sf::Vector2f getPlayerNewPos(sf::Vector2f playerPos, sf::Vector2f playerMove);

public:
	Map();

	void update();
	void movePlayer(std::shared_ptr<Player> player, std::string direction);
	void render(std::shared_ptr<sf::RenderWindow> window, sf::View& view);

	void convertMap(std::vector<std::vector<int>> intMap);
	void updateFovContact(std::shared_ptr<Player> player);
};

