#pragma once

#include "Player.h"
#include "Map.h"
#include "Global.h"

enum class HitType 
{
	HORIZONTAL = 0,
	VERTICAL
};

struct Ray
{
	float length;
	sf::Vector2f hitPoint;
	HitType hitType;;
};

class Raycasting
{
private:
    std::vector<Ray> rays;
	float maxRayLength;
    float horizontalFov;
	float verticalFov;

    void updateFovContact(Player& player);
	void defineRay(Player& player, int ray, Map& map);
	sf::Vector2i getDeltaFactor(float angle);
	sf::Vector2f getDelta(sf::Vector2f cellPos, sf::Vector2i deltaFactor, sf::Vector2f startPoint, Map& map);
	sf::Vector2f getCellPos(sf::Vector2f startPoint, sf::Vector2i deltaFactor, Map& map);
    void initRays(float windowWidth);
	void updateRay(int index, float raySize, sf::Vector2f hitPoint, HitType HitType);
	float calculateRayAngle(int rayIndex, Player& player);

public:
    Raycasting(float windowWidth);
    ~Raycasting();

    void update(Player& player, Map& map);
    void render(sf::RenderWindow& window, Player& player, Map& map);

    float getHorizontalFov() { return this->horizontalFov; }
    float getVerticalFov() { return this->verticalFov; }
};
