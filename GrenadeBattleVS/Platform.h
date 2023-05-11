#pragma once
#include "Object.h"

class Player;

class Platform :
    public Object
{
public:
    Platform(sf::Vector2f newPosition);
    ~Platform();
};