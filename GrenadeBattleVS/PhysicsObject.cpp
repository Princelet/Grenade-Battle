#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
    : Object()
{
}

void PhysicsObject::Update(sf::Time frameTime)
{
    const float DRAG = 20.0f;
    sf::Vector2f lastFramePos = GetPosition();

    // EXPLICIT EULER (FORWARD EULER)

    SetPosition(GetPosition() + velocity * frameTime.asSeconds());
    velocity += acceleration * frameTime.asSeconds();

    // Drag Calculation
    velocity.x -= velocity.x * DRAG * frameTime.asSeconds();

    // Update Acceleration
    UpdateAcceleration();
}

void PhysicsObject::HandleCollision(Object& otherObj)
{
    sf::Vector2f depth = GetCollisionDepth(otherObj);
    sf::Vector2f newPos = GetPosition();

    if (abs(depth.x) < abs(depth.y))
    {
        // Move in x direction
        newPos.x += depth.x * 1.1f;
        velocity.x = 0;
        acceleration.x = 0;
    }
    else
    {
        // Move in y direction
        newPos.y += depth.y * 1.1f;
        velocity.y = 0;
        acceleration.y = 0;
    }

    SetPosition(newPos);
}

void PhysicsObject::UpdateAcceleration()
{
    const float ACCEL = 3000;
    const float GRAVITY = 1000;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = GRAVITY;
}