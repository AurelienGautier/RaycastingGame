#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.h"
#include "Tile.h"
#include "Global.h"

class Map
{
private:
	std::vector<std::vector<Tile>> cells;
	const int cellSize = 16;

	bool canPlayerMove(sf::Vector2f playerPos, sf::Vector2f playerMove);

	float getRaySize(Player& player, int ray);
	sf::Vector2i getDeltaFactor(float angle);
	sf::Vector2f getDelta(sf::Vector2f cellPos, sf::Vector2i deltaFactor, sf::Vector2f startPoint);
	sf::Vector2f getCellPos(sf::Vector2f startPoint, sf::Vector2i deltaFactor);
	bool isWall(Tile cell);

public:
	Map();

	void update(Player& player);
	void movePlayer(Player& player, Direction direction);
	void render(std::shared_ptr<sf::RenderWindow> window, sf::View& view);

	void convertMap(std::vector<std::vector<int>> intMap);
	void updateFovContact(Player& player);
};

