#pragma once
#include "PhysicsObject.h"

class Player;

class Grenade :
    public PhysicsObject
{
public:
    Grenade();

    void Update(sf::Time frameTime) override;
    void HandleCollision(Object& otherObj) override;

    void SetVelocity(sf::Vector2f newVel);

    int GetFuseTimer();
    int GetExplodeTimer();

    void DecreaseFuseTimer();
    void DecreaseExplodeTimer();

    void Explode();

private:
    int fuseTimer;
    int explodeTimer;
};