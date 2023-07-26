#include "header/Global.h"

float Glb::degToRad(float angle)
{
    return angle / 180 * 3.14;
}

float Glb::clamp(float value, float minValue, float maxValue)
{
    if(value < minValue) return minValue;
    if(value > maxValue) return maxValue;
    return value;
}

float Glb::tangent(float angle)
{
    return tan(Glb::degToRad(angle));
}

float Glb::cosine(float angle)
{
    return cos(Glb::degToRad(angle));
}

float Glb::sinus(float angle)
{
    return sin(Glb::degToRad(angle));
}