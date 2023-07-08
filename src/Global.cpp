#include "header/Global.h"

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