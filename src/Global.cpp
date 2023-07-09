#include "header/Global.h"
#include <iostream>

float Global::degToRad(float angle)
{
    return angle / 180 * 3.14;
}

float Global::clamp(float value, float minValue, float maxValue)
{
    if(value < minValue) return minValue;
    if(value > maxValue) return maxValue;
    return value;
}

float Global::tangent(float angle)
{
    return tan(Global::degToRad(angle));
}

float Global::cosine(float angle)
{
    return cos(Global::degToRad(angle));
}

float Global::sinus(float angle)
{
    return sin(Global::degToRad(angle));
}