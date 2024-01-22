#pragma once

#include "Player.h"
#include "Map.h"
#include "Global.h"

class Raycasting
{
private:
    void updateFovContact(Player& player);
	void defineRay(Player& player, int ray, Map& map);
	sf::Vector2i getDeltaFactor(float angle);
	sf::Vector2f getDelta(sf::Vector2f cellPos, sf::Vector2i deltaFactor, sf::Vector2f startPoint, Map& map);
	sf::Vector2f getCellPos(sf::Vector2f startPoint, sf::Vector2i deltaFactor, Map& map);

public:
    Raycasting();
    ~Raycasting();

    void update(Player& player, Map& map);
    void render(sf::RenderWindow& window, Player& player, Map& map);
};
