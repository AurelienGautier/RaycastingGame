#pragma once

#include "Player.h"
#include "Map.h"
#include "Global.h"

class Raycasting
{
private:
    

public:
    Raycasting();
    ~Raycasting();

    void update(Player& player);
    void render(sf::RenderWindow& window);
};