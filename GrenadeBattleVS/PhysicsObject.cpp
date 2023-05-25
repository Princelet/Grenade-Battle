#include "PhysicsObject.h"

enum class PhysicsType
{
    FORWARD_EULER,
    BACKWARD_EULER,
    SYMPLECTIC_EULER
};

PhysicsObject::PhysicsObject()
    : Object()
{
}

void PhysicsObject::Update(sf::Time frameTime)
{
    const float DRAG = 20.0f;
    sf::Vector2f lastFramePos = GetPosition();

    // Practical Task - Physics Alternatives
    const PhysicsType physics = PhysicsType::FORWARD_EULER;

    switch (physics)
    {
    case PhysicsType::FORWARD_EULER:
    {
        // EXPLICIT EULER (FORWARD EULER)

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());
        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity.x -= velocity.x * DRAG * frameTime.asSeconds();

        // Update Acceleration
        UpdateAcceleration();

        break;
    }
    case PhysicsType::BACKWARD_EULER:
    {
        // IMPLICIT EULER (BACKWARD EULER)

        // Update Acceleration
        UpdateAcceleration();

        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity.x -= velocity.x * DRAG;

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());

        break;
    }
    case PhysicsType::SYMPLECTIC_EULER:
    {
        // SEMI-IMPLICIT EULER (SYMPLECTIC EULER)

        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity.x -= velocity.x * DRAG;

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());

        // Update Acceleration
        UpdateAcceleration();

        break;
    }
    }
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