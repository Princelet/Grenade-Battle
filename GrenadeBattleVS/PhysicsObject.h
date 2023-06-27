#pragma once
#include "Object.h"
class PhysicsObject :
    public Object
{
public:
    PhysicsObject();

    void Update(sf::Time frameTime) override;

    void HandleCollision(Object& otherObj) override;

protected:
    virtual void UpdateAcceleration();

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool hasDrag;
};