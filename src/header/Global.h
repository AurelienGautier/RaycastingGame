#pragma once

#include <cmath>

enum class Direction 
{
    FORWARD = 0,
    LEFT,
    BACK,
    RIGHT
};

class Glb
{
public:
    static float degToRad(float angle);
    static float clamp(float value, float minValue, float maxValue);
    static float tangent(float angle);
    static float cosine(float angle);
    static float sinus(float angle);
};