#pragma once
#include "PhysicsObject.h"
class Grenade :
    public PhysicsObject
{
public:
    Grenade();

    void HandleCollision(Object& otherObj) override;
};

