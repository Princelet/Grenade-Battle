#pragma once
#include "PhysicsObject.h"

class Player :
    public PhysicsObject
{
public:
    Player();

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void SetP1(bool isP1);

private:
    void UpdateAcceleration();
    sf::Vector2f GetPipPosition(float pipTime);
    std::vector<sf::Sprite> pips;

    bool p1;
};